#include <common.h>


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


VALUE
rbtree_each(VALUE self)
{
  rb_need_block();
  VALUE block = rb_block_proc();

  EXTRACT_RBTREE_SELF(rbtree);

  g_tree_foreach(rbtree->gtree, foraech_callbac, (gpointer) block);

  return self;
}


VALUE
rbtree_each_key(VALUE self)
{
  rb_need_block();
  VALUE block = rb_block_proc();

  EXTRACT_RBTREE_SELF(rbtree);

  g_tree_foreach(rbtree->gtree, foraech_key_callbac, (gpointer) block);

  return self;
}


VALUE
rbtree_each_value(VALUE self)
{
  rb_need_block();
  VALUE block = rb_block_proc();

  EXTRACT_RBTREE_SELF(rbtree);

  g_tree_foreach(rbtree->gtree, foraech_value_callbac, (gpointer) block);

  return self;
}
