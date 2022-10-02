#include <compare_trees.h>

static inline gboolean
rbtree_compare_trees_nodes(GTreeNode *a, GTreeNode *b)
{
  gboolean result = TRUE;

  VALUE key_a = (VALUE) g_tree_node_key(a);
  VALUE val_a = (VALUE) g_tree_node_value(a);
  VALUE key_b = (VALUE) g_tree_node_key(b);
  VALUE val_b = (VALUE) g_tree_node_value(b);

  VALUE key_result = rb_funcall(key_a, rb_intern("=="), 1, key_b);

  if (!RTEST(key_result)) {
    return FALSE;
  }

  VALUE val_result = rb_funcall(val_a, rb_intern("=="), 1, val_b);

  if (!RTEST(val_result)) {
    return FALSE;
  }

  return result;
}


gboolean
rbtree_compare_trees(const RBTree *a, const RBTree *b)
{
  // NOTE: Assume that the number of nodes is same (already checked)

  GTreeNode *a_node = g_tree_node_first(a->gtree);
  GTreeNode *b_node = g_tree_node_first(b->gtree);

  gboolean result = FALSE;

  while (a_node && b_node) {
    result = rbtree_compare_trees_nodes(a_node, b_node);

    if (!result) {
      break;
    }

    a_node = g_tree_node_next(a_node);
    b_node = g_tree_node_next(b_node);
  }

  return result;
}
