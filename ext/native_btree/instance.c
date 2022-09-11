#include <common.h>


#ifndef HAVE_GTREE_REMOVE_ALL

static gboolean
rbtree_remove_node(gpointer key, gpointer val, gpointer data) {
  RBTree *rbtree = (RBTree *) data;

  g_tree_remove(rbtree->gtree, key);

  return FALSE;
}

#endif


VALUE
rbtree_set(VALUE self, VALUE key, VALUE value)
{
  EXTRACT_RBTREE_SELF(rbtree);

  g_tree_replace(rbtree->gtree, (gpointer) key, (gpointer) value);

  return self;
}


VALUE
rbtree_get(VALUE self, VALUE key)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gpointer found = g_tree_lookup(rbtree->gtree, (gpointer) key);

  if (found == NULL) {
    return Qnil;
  }

  VALUE result = (VALUE) found;

  return result;
}


VALUE
rbtree_delete(VALUE self, VALUE key)
{
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE found_key, found_value;
  gboolean found = g_tree_lookup_extended(
    rbtree->gtree,
    (gconstpointer) key,
    (gpointer *) &found_key,
    (gpointer *) &found_value
  );

  if (found) {
    g_tree_remove(rbtree->gtree, (gconstpointer) key);

    return found_value;
  }
  else {
    if (rb_block_given_p()) {
      VALUE block = rb_block_proc();

      return rb_funcall(block, rb_intern("call"), 1, key);
    }

    return Qnil;
  }
}


VALUE
rbtree_height(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint size = g_tree_height(rbtree->gtree);
  VALUE result = INT2NUM(size);

  return result;
}


VALUE
rbtree_size(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint size = g_tree_nnodes(rbtree->gtree);
  VALUE result = INT2NUM(size);

  return result;
}


VALUE
rbtree_clear(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  #ifdef HAVE_GTREE_REMOVE_ALL
    g_tree_remove_all(rbtree->gtree);
  #else
    g_tree_foreach(rbtree->gtree, rbtree_remove_node, (gpointer) rbtree);
  #endif

  return self;
}


VALUE
rbtree_is_include(VALUE self, VALUE key)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gpointer exists = g_tree_lookup(rbtree->gtree, (gconstpointer) key);

  if (exists == NULL) {
    return Qfalse;
  }

  return Qtrue;
}


VALUE
rbtree_is_empty(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint size = g_tree_nnodes(rbtree->gtree);

  return size > 0 ? Qfalse : Qtrue;
}
