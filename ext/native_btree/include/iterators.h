#include <common.h>

typedef struct {
  VALUE block;
  RBTree *tree;
  gconstpointer something;
} RBTreeSearchData;
