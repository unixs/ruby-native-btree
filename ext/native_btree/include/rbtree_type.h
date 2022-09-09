#ifndef _RBTREE_TYPE_
#define _RBTREE_TYPE_

#include <common.h>

#define RBTREE_NATIVE_TYPE_NAME "native_btree"

extern const rb_data_type_t rbtree_type;

VALUE
rbtree_alloc(VALUE self);

/**
 * Internal native instance
 */
typedef struct _RBTree
{
  GTree *gtree;
  VALUE comparator;
} RBTree;

#endif //_RBTREE_TYPE_
