#include <common.h>

#ifndef HAS_GTREE_NODE
  #include <utils.h>
#endif

static gboolean
foraech_callbac(gpointer a, gpointer b, gpointer data)
{
  VALUE key = (VALUE) a;
  VALUE value = (VALUE) b;
  VALUE block = (VALUE) data;

  rb_funcall(block, rb_intern("call"), 2, value, key);

  return FALSE;
}


static gboolean
foraech_key_callbac(gpointer a, gpointer b, gpointer data)
{
  VALUE key = (VALUE) a;
  VALUE block = (VALUE) data;

  rb_funcall(block, rb_intern("call"), 1, key);

  return FALSE;
}


static gboolean
foraech_value_callbac(gpointer a, gpointer b, gpointer data)
{
  VALUE value = (VALUE) b;
  VALUE block = (VALUE) data;

  rb_funcall(block, rb_intern("call"), 1, value);

  return FALSE;
}


static VALUE
rbtree_enum_length(VALUE rbtree, VALUE args, VALUE eobj)
{
  return rbtree_size(rbtree);
}


VALUE
rbtree_each(VALUE self)
{
  RETURN_SIZED_ENUMERATOR(self, 0, 0, rbtree_enum_length);

  EXTRACT_RBTREE_SELF(rbtree);

  VALUE block = rb_block_proc();

  g_tree_foreach(rbtree->gtree, foraech_callbac, (gpointer) block);

  return self;
}


VALUE
rbtree_each_key(VALUE self)
{
  RETURN_SIZED_ENUMERATOR(self, 0, 0, rbtree_enum_length);

  EXTRACT_RBTREE_SELF(rbtree);

  VALUE block = rb_block_proc();

  g_tree_foreach(rbtree->gtree, foraech_key_callbac, (gpointer) block);

  return self;
}


VALUE
rbtree_each_value(VALUE self)
{
  RETURN_SIZED_ENUMERATOR(self, 0, 0, rbtree_enum_length);

  EXTRACT_RBTREE_SELF(rbtree);

  VALUE block = rb_block_proc();

  g_tree_foreach(rbtree->gtree, foraech_value_callbac, (gpointer) block);

  return self;
}


VALUE
rbtree_reverse_each(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  RETURN_SIZED_ENUMERATOR(self, 0, 0, rbtree_enum_length);

#ifdef HAS_GTREE_NODE
  GTreeNode *current = g_tree_node_last(rbtree->gtree);

  VALUE key, val;
  while (current) {
    key = (VALUE) g_tree_node_key(current);
    val = (VALUE) g_tree_node_value(current);

    rb_yield_values(2, val, key);

    current = g_tree_node_previous(current);
  }
#else
  GPtrArray *buff = rbtree_to_ptr_array(rbtree);

  VALUE key, val;
  for (glong i = buff->len - 1; i > 0; i--) {
    val = (VALUE) g_ptr_array_index(buff, i);
    key = (VALUE) g_ptr_array_index(buff, --i);

    rb_yield_values(2, val, key);
  }

  g_ptr_array_free(buff, TRUE);
#endif

  return self;
}
