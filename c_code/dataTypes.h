// Сообщения.
typedef enum {
   REQ,
   FREE
} Mes;

// Индексы процессов:
typedef enum {
   i, j, k
} I;

// Индексные сообщения.
typedef enum {
   req_i,
   req_j,
   req_k,
   free_i,
   free_j,
   free_k
} iMes;

// Состояния автомата.
typedef enum {
   freed,      // Ресурс свободен.
   busy_i,     // Ресурс занят процессом i.
   wait_j,     // Ожидание освобождения ресурса процессом j.
   busy_j,     // Ресурс занят процессом j.
   cancel_j    // Отказ от ресурса процессом j.
} Q;

// Индексные выходы автомата.
typedef enum {
   grant_i,
   grant_j,
   deny_i,
   deny_j,
   deny_k,
   rescind_i,
   empty
} iOut;

// Булевы значения:
typedef enum {
   false = 0,
   true = 1
} bool;