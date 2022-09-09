#include <common.h>

static gboolean
rbtree_to_h_callback(gpointer key, gpointer value, gpointer data)
{
  VALUE hash = (VALUE) data;

  rb_hash_aset(hash, (VALUE) key, (VALUE) value);

  return FALSE;
}


static gboolean
rbtree_to_a_callback(gpointer key, gpointer value, gpointer data)
{
  VALUE array = (VALUE) data;
  VALUE array2 = rb_ary_new2(2);

  rb_ary_push(array2, (VALUE) key);
  rb_ary_push(array2, (VALUE) value);

  rb_ary_push(array, array2);

  return FALSE;
}


VALUE
rbtree_to_h(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE hash = rb_hash_new();

  g_tree_foreach(rbtree->gtree, rbtree_to_h_callback, (gpointer) hash);

  return hash;
}


VALUE
rbtree_to_a(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint tree_size = g_tree_nnodes(rbtree->gtree);

  VALUE array = rb_ary_new2(tree_size);

  g_tree_foreach(rbtree->gtree, rbtree_to_a_callback, (gpointer) array);

  return array;
}
