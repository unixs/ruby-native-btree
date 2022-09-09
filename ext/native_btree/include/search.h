#include <common.h>

typedef struct {
  VALUE block;
  RBTree *tree;
} RBTreeSearchData;


VALUE
rbtree_filter(VALUE self);
