#include <iostream>
#include "Arbiter.cpp"

using namespace std;

Arbiter arb;

void prinrData(int res) {
   cout
   << "[res: " << res << "]" << endl
   << "[grant: "   << arb.getGrantProc(res)   << "]  "
   << "[deny: "    << arb.getDenyProc(res)    << "]  "
   << "[rescind: " << arb.getRescindProc(res) << "]  "
   << "[owner: "   << arb.owner(res)   << "]  "
   << "[waiting: " << arb.waiting(res) << "]  " << endl;
   cout << endl;
}

void req(int proc, int res) {
   cout << "req(" << proc << "," << res << ")" << endl;
   arb.req(proc, res);
   prinrData(res);
}

void free(int proc, int res) {
   cout << "free(" << proc << "," << res << ")" << endl;
   arb.free(proc, res);
   prinrData(res);
}

void test1() {
   req(1, 3);
   req(2, 3);
   free(1, 3);
}

int main() {
   test1();
   return 0;
}