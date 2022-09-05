#include <iterators.h>

static gboolean
foraech_callbac(gpointer a, gpointer b, gpointer data)
{
  VALUE key = (VALUE) a;
  VALUE value = (VALUE) b;
  VALUE block = (VALUE) data;

  rb_funcall(block, rb_intern("call"), 2, value, key);

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
