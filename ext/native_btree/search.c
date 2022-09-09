#include <search.h>

VALUE rbtree_class;

gboolean
foreach_callback(gpointer a, gpointer b, gpointer data)
{
  RBTreeSearchData *context = (RBTreeSearchData *) data;

  VALUE compare_result = rb_funcall(
    context->block,
    rb_intern("call"),
    2,
    (VALUE) b,
    (VALUE) a
  );

  if (RTEST(compare_result)) {
    g_tree_insert(context->tree->gtree, a, b);
  }

  return FALSE;
}

VALUE
rbtree_filter(VALUE self)
{
  rb_need_block();
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE block = rb_block_proc();

  VALUE new_tree = rb_funcall_with_block(
    rbtree_class,
    rb_intern("new"),
    0,
    NULL,
    rbtree->comparator
  );

  EXTRACT_RBTREE(new_tree, new_rbtree);

  RBTreeSearchData data = {
    block,
    new_rbtree
  };

  g_tree_foreach(rbtree->gtree, foreach_callback, &data);

  return new_tree;
}
