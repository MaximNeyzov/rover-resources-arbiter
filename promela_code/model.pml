c_decl{ #include "Core.c" };

// use "./pan -r" for debug.

// Core inputs:
c_decl{
   Mes mes = FREE;
   bool pi = false;
   bool pj = false;
   bool highPrior = false;
};

// Core outputs:
c_decl{
   I ind = i;
   iOut iout = empty;
};

// Components of the model state vector:
c_track "&mes" "sizeof(char)" "Matched";
c_track "&ind" "sizeof(char)" "Matched";
c_track "&highPrior" "sizeof(char)" "Matched";
c_track "&q" "sizeof(char)" "Matched"; // "q" defined in "Core.c"
c_track "&iout" "sizeof(char)" "Matched";

// Распечатать информацию для отладки:
bool print_info = true;

active proctype model() {
   do
   :: atomic {
      if
      :: c_code{ mes = REQ;  };
      :: c_code{ mes = FREE; };
      fi;
      if
      :: c_code{ pi = false; };
      :: c_code{ pi = true;  };
      fi;
      if
      :: c_code{ pj = false; };
      :: c_code{ pj = true;  };
      fi;
      if
      :: c_code{ highPrior = false; };
      :: c_code{ highPrior = true;  };
      fi;
      c_code {
         ind = getIndex(pi, pj);
         iout = iter(mes, pi, pj, highPrior);
         if (now.print_info) {
            print_input(mes, pi, pj, highPrior);
            print_result(q, iout, ind);
         }
      };
   }
   od
}

// Определения:

#define grants c_expr{ (iout == grant_i) || (iout == grant_j) }
#define granti c_expr{ iout == grant_i }
#define grantj c_expr{ iout == grant_j }
#define freei c_expr{ (mes == FREE) && (ind == i) }
#define freej c_expr{ (mes == FREE) && (ind == j) }
#define Freed c_expr{ q == freed }
#define req c_expr{ mes == REQ }
#define reqj c_expr{ (mes == REQ) && (ind == j) }
#define busyi c_expr{ q == busy_i }
#define highPrior c_expr{ highPrior == true }

// Свойства:

/*
f1,f2: Взаимоисключающий доступ процессов к ресурсу.
Всегда, если выдано разрешение использовать ресурс,
то разрешений больше не выдается до тех пор,
пока ресурс не будет освобожден процессом, который им владеет.
f1: G( granti -> X(!grants W freei) ) // valid
f2: G( grantj -> X(!grants W freej) ) // valid
Option - Safety: Invalid Endstates
*/
// never { /* !f1 = !G( granti -> X(!grants W freei) ) */
// T0_init:
//   if
//   :: (!(granti)) -> goto T0_init
//   :: (granti) -> goto T0_S2
//   fi;
// T0_S2:
//   if
//   :: ((!(freei)) && (!(!grants))) -> goto accept_all
//   :: ((freei) && (!(granti))) -> goto T0_init
//   :: (((freei) && (granti)) || ((!(freei)) && (!grants))) -> goto T0_S2
//   fi;
// accept_all:
//   skip
// }

// never { /* !f2 = !G( grantj -> X(!grants W freej) ) */
// T0_init:
//   if
//   :: (!(grantj)) -> goto T0_init
//   :: (grantj) -> goto T0_S2
//   fi;
// T0_S2:
//   if
//   :: ((!(freej)) && (!(!grants))) -> goto accept_all
//   :: ((freej) && (!(grantj))) -> goto T0_init
//   :: (((freej) && (grantj)) || ((!(freej)) && (!grants))) -> goto T0_S2
//   fi;
// accept_all:
//   skip
// }


/*
f3: Доступность свободного ресурса.
Всегда, запрос свободного ресурса сопровождается разрешением на его использование.
f3: G( Freed && X(req) -> X(granti) ) // valid
Option - Safety: Invalid Endstates
*/
// never { /* !f3 = !G( Freed && X(req) -> X(granti) ) */
// T0_init:
//   if
//   :: (!(Freed)) -> goto T0_init
//   :: (Freed) -> goto T0_S2
//   fi;
// T0_S2:
//   if
//   :: ((!(granti)) && (req)) -> goto accept_all
//   :: (((granti) && (!(Freed))) || ((!(Freed)) && (!(req)))) -> goto T0_init
//   :: (((granti) && (Freed)) || ((Freed) && (!(req)))) -> goto T0_S2
//   fi;
// accept_all:
//   skip
// }


/*
f4: Доступность ресурса для высокоприоритетного процесса.
Всегда, если высокоприоритетный процесс запрашивает занятый ресурс,
то он неизбежно его получит в будущем.
G( busyi && X(reqj && highPrior) -> XF(grantj) )
Option - Liveness: Acceptance Cycles
Условия: 
1) процесс i, захвативший ресурс, обязательно его освободит в будущем
- GF(freei)
2) высокоприоритетный процесс не отказывается от ресурса
- G(!freej)
Итог:
GF(freei) && G(!freej) -> G( busyi && X(reqj && highPrior) -> XF(grantj) )
*/
never { /* !f4 = !(GF(freei) && G(!freej) -> G( busyi && X(reqj && highPrior) -> XF(grantj) )) */
T0_init:
	do
	:: ((!freej) && (freei) && (busyi)) -> goto accept_S86
	:: ((!freej) && (busyi)) -> goto T0_S86
	:: ((!freej)) -> goto T0_init
	od;
accept_S62:
	do
	:: ((!freej) && ! ((grantj))) -> goto T0_S62
	od;
accept_S86:
	do
	:: ((!freej) && ! ((grantj)) && (reqj && highPrior)) -> goto T0_S62
	od;
T0_S62:
	do
	:: ((!freej) && ! ((grantj)) && (freei)) -> goto accept_S62
	:: ((!freej) && ! ((grantj))) -> goto T0_S62
	od;
T0_S86:
	do
	:: ((!freej) && ! ((grantj)) && (freei) && (reqj && highPrior)) -> goto accept_S62
	:: ((!freej) && ! ((grantj)) && (reqj && highPrior)) -> goto T0_S62
	od;
}