#include <common.h>

#ifndef _NATIVE_BTREE_ITERATORS_
#define _NATIVE_BTREE_ITERATORS_

typedef struct {
  const VALUE block;
  const RBTree *tree;
  glong counter;
  gushort flags;
  gconstpointer something;
} RBTreeSearchContext;

#ifdef HAS_GTREE_NODE

typedef GTreeNode *(RBTreeStepFunction) (GTreeNode *node);

#endif

#endif // _NATIVE_BTREE_ITERATORS_
