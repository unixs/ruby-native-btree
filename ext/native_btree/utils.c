#include <utils.h>


static gint
to_ptr_array_cb(gpointer a, gpointer b, gpointer data)
{
  GPtrArray *buff = (GPtrArray *) data;

  g_ptr_array_add(buff, a);
  g_ptr_array_add(buff, b);

  return FALSE;
}


GPtrArray*
rbtree_to_ptr_array(const RBTree *rbtree)
{
  gint tree_size = g_tree_nnodes(rbtree->gtree);

  GPtrArray *buff = g_ptr_array_sized_new(tree_size * 2);

  g_tree_foreach(rbtree->gtree, to_ptr_array_cb, (gpointer) buff);

  return buff;
}
