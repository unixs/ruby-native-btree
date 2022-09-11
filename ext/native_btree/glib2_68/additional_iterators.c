#include <native_btree.h>
#include <iterators.h>

static void
rbtree_gtree_foreach(GTreeNode *node, RBTreeStepFunction step_func, GTraverseFunc callback, gpointer data)
{
  while (node) {
    callback(
      g_tree_node_key(node),
      g_tree_node_value(node),
      data
    );

    node = step_func(node);
  }
}


static int
rbtree_traverse_insert(gpointer key, gpointer value, gpointer tree)
{
  g_tree_insert(tree, key, value);

  return FALSE;
}


VALUE
rbtree_select_before(VALUE self, VALUE target)
{
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE new_tree = rbtree_clone_wrap(rbtree);

  EXTRACT_RBTREE(new_tree, new_rbtree);

  GTreeNode *target_node = g_tree_upper_bound(
    rbtree->gtree,
    (gconstpointer) target
  );

  target_node = g_tree_node_previous(target_node);

  if (!target_node) {
    return new_tree;
  }

  rbtree_gtree_foreach(
    target_node,
    g_tree_node_previous,
    rbtree_traverse_insert,
    (gpointer) new_rbtree->gtree
  );

  return new_tree;
}


VALUE
rbtree_select_after(VALUE self, VALUE target)
{
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE new_tree = rbtree_clone_wrap(rbtree);
  EXTRACT_RBTREE(new_tree, new_rbtree);

  GTreeNode *target_node = g_tree_lower_bound(
    rbtree->gtree,
    (gconstpointer) target
  );

  if (!target_node) {
    return new_tree;
  }

  rbtree_gtree_foreach(
    target_node,
    g_tree_node_next,
    rbtree_traverse_insert,
    (gpointer) new_rbtree->gtree
  );

  return new_tree;
}
