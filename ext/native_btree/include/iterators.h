#include <common.h>

typedef struct {
  const VALUE block;
  const RBTree *tree;
  gconstpointer something;
} RBTreeSearchData;

typedef GTreeNode *(RBTreeStepFunction) (GTreeNode *node);
