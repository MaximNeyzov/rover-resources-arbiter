// Arbiter Core.
#include "dataTypes.h"

// private:
Q q = freed;

// private:
iMes indMes(I ind, Mes mes) {
   switch (ind) {
      case i:
         if (mes == REQ)  { return req_i;  }
         if (mes == FREE) { return free_i; }
      case j:
         if (mes == REQ)  { return req_j;  }
         if (mes == FREE) { return free_j; }
      case k:
         if (mes == REQ)  { return req_k;  }
         if (mes == FREE) { return free_k; }
   }
}

// private:
iOut atmIter(iMes imes, bool highPrior) {
   switch (q) {
      case freed:
         if (imes == req_i) {
            q = busy_i;
            return grant_i;
         }
         return empty;
      case busy_i:
         if (imes == free_i) {
            q = freed;
            return empty;
         } else
         if (imes == req_j && highPrior) {
            q = wait_j;
            return rescind_i;
         } else
         if (imes == req_j && !highPrior) {
            return deny_j;
         }
         return empty;
      case wait_j:
         if (imes == free_i) {
            q = busy_j;
            return grant_j;
         } else
         if (imes == free_j) {
            q = cancel_j;
            return empty;
         } else
         if (imes == req_k) {
            return deny_k;
         }
         return empty;
      case busy_j:
         if (imes == free_j) {
            q = freed;
            return empty;
         } else
         if (imes == req_i) {
            return deny_i;
         } else
         if (imes == req_k) {
            return deny_k;
         }
         return empty;
      case cancel_j:
         if (imes == free_i) {
            q = freed;
            return empty;
         } else
         if (imes == req_j) {
            q = wait_j;
            return empty;
         } else
         if (imes == req_k) {
            return deny_k;
         }
         return empty;
      default: return empty;
   }
}

// public:
I getIndex(bool pi, bool pj) {
   if ((q == freed) || pi) {
      return i;
   } else
   if ((q == busy_i) && !pi || pj) {
      return j;
   } else { return k; }
}

// public:
iOut iter(Mes mes, bool pi, bool pj, bool highPrior) {
   I ind = getIndex(pi, pj);
   iMes imes = indMes(ind, mes);
   iOut iout = atmIter(imes, highPrior);
   return iout;
}

// for debug:
char* getStateName(Q q) {
   switch (q) {
      case freed:    return "freed";
      case busy_i:   return "busy_i";
      case wait_j:   return "wait_j";
      case busy_j:   return "busy_j";
      case cancel_j: return "cancel_j";
      default:       return "error";
   }
}

// for debug:
char* getOutName(iOut iout) {
   switch (iout) {
      case grant_i:   return "grant_i";
      case grant_j:   return "grant_j";
      case deny_i:    return "deny_i";
      case deny_j:    return "deny_j";
      case deny_k:    return "deny_k";
      case rescind_i: return "rescind_i";
      case empty:     return "empty";
      default:        return "error";
   }
}

// for debug:
char* getIndexName(I ind) {
   switch (ind) {
      case i: return "i";
      case j: return "j";
      case k: return "k";
      default: return "error";
   }
}

// for debug:
char* getIMesName(iMes imes) {
   switch (imes) {
      case req_i:  return "req_i";
      case req_j:  return "req_j";
      case req_k:  return "req_k";
      case free_i: return "free_i";
      case free_j: return "free_j";
      case free_k: return "free_k";
      default:     return "error";
   }
}

// for debug:
void print_input(Mes mes, bool pi, bool pj, bool highPrior) {
   printf("INPUT:  ");
   if (mes == REQ) { printf("[mes==req]  "); }
   if (mes == FREE) { printf("[mes==free]  "); }
   printf("[pi==%d]  [pj==%d]  [highPrior==%d]\n", pi, pj, highPrior);
}

// for debug:
void print_result(Q q, iOut iout, I ind) {
   printf("RESULT:  ");
   printf("[q==%s]  ", getStateName(q));
   printf("[iout==%s]  ", getOutName(iout));
   printf("[ind==%s]\n", getIndexName(ind));
}