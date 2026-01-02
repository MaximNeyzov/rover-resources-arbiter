#include "core.cpp"

// Значения индексов:
struct V {
   int i = 0;
   int j = 0;
   int k = 0;
};

const int EMPTY = -1; // No response.

// Выход арбитра:
struct Out {
   int grant = EMPTY;     // Процесс, получивший разрешение.
   int deny = EMPTY;      // Процесс, получивший отказ.
   int rescind = EMPTY;   // Процесс, получивший сигнал расторжения.

   void reset() {
      grant = EMPTY;
      deny = EMPTY;
      rescind = EMPTY;
   }
};

// Приоритеты процессов {1 - low, 2 - high}.
const int prior[10] = { 1, 1, 2, 1, 1, 1, 1, 1, 1, 2 };

class OneResArbiter {
private:
   ArbiterCore core;
   V val; // Index values.
   Out out;

private:
   bool inRange(int proc) {
      return (proc >= 0) && (proc < sizeof(prior));
   }

   bool get_pi(int proc) {
      return (proc == val.i);
   }

   bool get_pj(int proc) {
      return (proc == val.j);
   }
 
   void indUpd(int proc, I ind) {
      if (ind == i) { val.i = proc; }
      if (ind == j) { val.j = proc; }
      if (ind == k) { val.k = proc; }
   }

   bool hp() {
      return (prior[val.j] > prior[val.i]);
   }

   void convert(iOut iout) {
      out.reset();
      if (iout == grant_i) { out.grant = val.i; }
      if (iout == grant_j) { out.grant = val.j; }
      if (iout == deny_i)  { out.deny  = val.i; }
      if (iout == deny_j)  { out.deny  = val.j; }
      if (iout == deny_k)  { out.deny  = val.k; }
      if (iout == rescind_i) { out.rescind = val.i; }
   }

   void iter(Mes mes, int proc) {
      bool pi = get_pi(proc);
      bool pj = get_pj(proc);
      I ind = core.getIndex(pi, pj);
      indUpd(proc, ind);
      bool highPrior = hp();
      iOut iout = core.iter(mes, pi, pj, highPrior);
      convert(iout);
      print_info(); // for debug.
   }

public:
   OneResArbiter() {}

   // Запрос ресурса процессом.
   void req(int proc) {
      if (inRange(proc)) { iter(REQ, proc); }
   }

   // Освобождение ресурса процессом.
   void free(int proc) {
      if (inRange(proc)) { iter(FREE, proc); }
   }

   // Процесс, получивший грант.
   int getGrantProc() { return out.grant; }

   // Процесс, получивший отказ.
   int getDenyProc() { return out.deny; }

   // Процесс, получивший отмену владения ресурсом.
   int getRescindProc() { return out.rescind; }

   // Владелец ресурса.
   int owner() {
      Q q = core.getAtmState();
      switch (q) {
         case Q::busy_i:
         case Q::wait_j:
         case Q::cancel_j: return val.i;
         case Q::busy_j: return val.j;
         case Q::freed:
         default: return EMPTY;
      }
   }

   // Процесс, ожидающий ресурс.
   int waiting() {
      Q q = core.getAtmState();
      if (q == Q::wait_j) return val.j;
      else return EMPTY;
   }

// for debug:
private:
   void print_info() {
      std::cout << "[i==" << val.i << "]  ";
      std::cout << "[j==" << val.j << "]  ";
      std::cout << "[k==" << val.k << "]\n";
      std::cout << "[grant==" << out.grant << "]  ";
      std::cout << "[deny==" << out.deny << "]  ";
      std::cout << "[rescind==" << out.rescind << "]\n\n";
   }
};