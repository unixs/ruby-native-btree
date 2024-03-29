#include <iterators.h>


static gboolean
filter_callback(gpointer a, gpointer b, gpointer data)
{
  RBTreeSearchContext *context = (RBTreeSearchContext *) data;

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
  RBTreeSearchContext *context = (RBTreeSearchContext *) data;
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

/**
 * Filters btree by block call
 *
 * If block returns true, key/value will include in result tree
 *
 * @return [Btree] result
 */
VALUE
rbtree_filter(VALUE self)
{
  rb_need_block();
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE block = rb_block_proc();

  VALUE new_tree = rbtree_clone_wrap(rbtree);

  EXTRACT_RBTREE(new_tree, new_rbtree);

  RBTreeSearchContext data = {
    block,
    new_rbtree,
    0,
    0,
    NULL
  };

  g_tree_foreach(rbtree->gtree, filter_callback, &data);

  return new_tree;
}

/**
 * Filters btree by block call
 *
 * Same as #filter but returns changed self.
 *
 * @return [Btree] result
 */
VALUE
rbtree_filter_bang(VALUE self)
{
  rb_need_block();
  EXTRACT_RBTREE_SELF(rbtree);

  VALUE block = rb_block_proc();

  GPtrArray *to_remove = g_ptr_array_new();

  RBTreeSearchContext data = {
    block,
    NULL,
    0,
    0,
    (gconstpointer) to_remove
  };

  g_tree_foreach(rbtree->gtree, filter_bang_callback, &data);

  for (size_t i = 0; i < to_remove->len; i++) {
    g_tree_remove(rbtree->gtree, g_ptr_array_index(to_remove, i));
  }

  g_ptr_array_free(to_remove, TRUE);

  return self;
}
