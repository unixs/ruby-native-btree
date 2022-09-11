#ifndef _RBTREE_TYPE_
#define _RBTREE_TYPE_

#include <common.h>

#define RBTREE_NATIVE_TYPE_NAME "native_btree"
#define RBTREE_FLAG_INT_COMPARATOR 0b10000000

extern const rb_data_type_t rbtree_type;

typedef struct _RBTree RBTree;

VALUE
rbtree_alloc(VALUE self);

VALUE
rbtree_clone_wrap(const RBTree *orig);

/**
 * Internal native instance
 */
struct _RBTree
{
  GTree *gtree;
  VALUE comparator;
  gushort flags;
};

#endif //_RBTREE_TYPE_
