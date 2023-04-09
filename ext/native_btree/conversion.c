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

/**
 * Converts tree to Hash
 *
 * @return [Hash] result
 */
VALUE
rbtree_to_h(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE hash = rb_hash_new();

  g_tree_foreach(rbtree->gtree, rbtree_to_h_callback, (gpointer) hash);

  return hash;
}

/**
 * Converts tree to array
 *
 * Coverts tree to array of arrays with key and value
 *
 * @return [Array] result
 */
VALUE
rbtree_to_a(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint tree_size = g_tree_nnodes(rbtree->gtree);

  VALUE array = rb_ary_new2(tree_size);

  g_tree_foreach(rbtree->gtree, rbtree_to_a_callback, (gpointer) array);

  return array;
}


static VALUE
to_proc_proc(RB_BLOCK_CALL_FUNC_ARGLIST(key, callback_arg))
{
  rb_check_arity(argc, 1, 1);
  EXTRACT_RBTREE(callback_arg, rbtree);

  VALUE value = (VALUE) g_tree_lookup(rbtree->gtree, (gconstpointer) key);

  if (!value) {
    return Qnil;
  }

  return value;
}

/**
 * Returns a Proc object that maps a key to its value
 *
 * @return [Proc] block
 */
VALUE
rbtree_to_proc(VALUE self)
{
  return rb_proc_new(to_proc_proc, self);
}

/**
 * Converts tree to string.
 *
 * Under hood will convert tree to Hash.
 *
 * @return [String] result
 */
VALUE
rbtree_to_s(VALUE self)
{
  VALUE h = rbtree_to_h(self);

  VALUE str = rb_sprintf("#<NativeBtree::Btree:%"PRIsVALUE">", h);

  return str;
}
