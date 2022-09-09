#include <search.h>

VALUE rbtree_class;

static gboolean
filter_callback(gpointer a, gpointer b, gpointer data)
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

static gboolean
filter_bang_callback(gpointer a, gpointer b, gpointer data)
{
  RBTreeSearchData *context = (RBTreeSearchData *) data;
  GPtrArray *to_remove = (GPtrArray *) context->something;

  VALUE compare_result = rb_funcall(
    context->block,
    rb_intern("call"),
    2,
    (VALUE) b,
    (VALUE) a
  );

  if (!RTEST(compare_result)) {
    // Add to remove
    g_ptr_array_add(to_remove, a);
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
    new_rbtree,
    NULL
  };

  g_tree_foreach(rbtree->gtree, filter_callback, &data);

  return new_tree;
}

VALUE
rbtree_filter_bang(VALUE self)
{
  rb_need_block();
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE block = rb_block_proc();

  GPtrArray *to_remove = g_ptr_array_new();

  RBTreeSearchData data = {
    block,
    NULL,
    (gconstpointer) to_remove
  };

  g_tree_foreach(rbtree->gtree, filter_bang_callback, &data);

  for (size_t i = 0; i < to_remove->len; i++) {
    g_tree_remove(rbtree->gtree, g_ptr_array_index(to_remove, i));
  }

  g_ptr_array_free(to_remove, TRUE);

  return self;
}
