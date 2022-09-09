#include <common.h>

typedef struct {
  VALUE block;
  RBTree *tree;
  gconstpointer something;
} RBTreeSearchData;


VALUE
rbtree_filter(VALUE self);

VALUE
rbtree_filter_bang(VALUE self);
