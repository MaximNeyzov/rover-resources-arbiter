#include "OneResArbiter.cpp"

const int NUMRES = 10; // Количество ресурсов.

// Арбитр ресурсов.
class Arbiter {
private:
   OneResArbiter arb[NUMRES];

   bool inRange(int res) {
      return ((res >= 0) && (res < NUMRES));
   }

public:
   // Запрос ресурса процессом.
   void req(int proc, int res) {
      if (inRange(res)) arb[res].req(proc);
   }

   // Освобождение ресурса процессом.
   void free(int proc, int res) {
      if (inRange(res)) arb[res].free(proc);
   }

   // Процесс, получивший разрешение ресурса.
   int getGrantProc(int res) {
      if (inRange(res)) return arb[res].getGrantProc();
      else return EMPTY;
   }

   // Процесс, получивший отказ ресурса.
   int getDenyProc(int res) {
      if (inRange(res)) return arb[res].getDenyProc();
      else return EMPTY;
   }

   // Процесс, получивший сигнал возврата ресурса.
   int getRescindProc(int res) {
      if (inRange(res)) return arb[res].getRescindProc();
      else return EMPTY;
   }

   // Владелец ресурса.
   int owner(int res) {
      if (inRange(res)) return arb[res].owner();
      else return EMPTY;
   }

   // Процесс, ожидающий ресурс.
   int waiting(int res) {
      if (inRange(res)) return arb[res].waiting();
      else return EMPTY;
   }

};