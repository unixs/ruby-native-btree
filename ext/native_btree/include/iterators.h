#include <common.h>

typedef struct {
  const VALUE block;
  const RBTree *tree;
  gconstpointer something;
} RBTreeSearchData;

#ifdef HAS_GTREE_NODE

typedef GTreeNode *(RBTreeStepFunction) (GTreeNode *node);

#endif
