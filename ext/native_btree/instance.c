#include <common.h>

#ifdef HAS_GTREE_NODE
  #include <compare_trees.h>
#else
  #include <utils.h>
  #include <iterators.h>
#endif

#ifndef HAS_GTREE_REMOVE_ALL

static gboolean
rbtree_remove_node(gpointer key, gpointer val, gpointer data) {
  RBTree *rbtree = (RBTree *) data;

  g_tree_remove(rbtree->gtree, key);

  return FALSE;
}

#endif


#ifndef HAS_GTREE_NODE

static gint
rbtree_first_cb(gpointer a, gpointer b, gpointer data)
{
  RBTreeSearchContext *context = (RBTreeSearchContext *) data;

  context->something = (gconstpointer) b;
  context->counter = 0;

  return TRUE;
}


static gint
rbtree_last_cb(gpointer a, gpointer b, gpointer data)
{
  RBTreeSearchContext *context = (RBTreeSearchContext *) data;

  context->something = (gconstpointer) b;
  context->counter += 1;

  return FALSE;
}


static gint
legacy_compare_visitor(gpointer a, gpointer b, gpointer data)
{
  RBTreeSearchContext *context = (RBTreeSearchContext *) data;

  GPtrArray *flat_tree = (GPtrArray *) context->something;
  VALUE key = (VALUE) a;
  VALUE val = (VALUE) b;
  VALUE is_eq = Qfalse;

  VALUE key2 = (VALUE) g_ptr_array_index(flat_tree, context->counter);
  VALUE val2 = (VALUE) g_ptr_array_index(flat_tree, context->counter + 1);

  is_eq = rb_funcall(key, rb_intern("=="), 1, key2);

  if (!RTEST(is_eq)) {
    context->flags = 1;
    return TRUE;
  }

  is_eq = rb_funcall(val, rb_intern("=="), 1, val2);

  if (!RTEST(is_eq)) {
    context->flags = 1;
    return TRUE;
  }

  (context->counter) += 2;

  return FALSE;
}


static inline gboolean
legacy_rbtree_compare(const RBTree *a, const RBTree *b)
{
  gboolean result = TRUE;

  GPtrArray *second = rbtree_to_ptr_array(b);

  // assumes that the size of arrays is same (checked before)

  RBTreeSearchContext context = {
    Qnil,
    NULL,
    0,
    0,
    (gconstpointer) second
  };

  g_tree_foreach(a->gtree, legacy_compare_visitor, &context);

  if (context.flags) {
    result = FALSE;
  }

  g_ptr_array_free(second, TRUE);

  return result;
}

#endif

/**
 * Adds key/value pair in to tree.
 *
 * Key/value will be replaced if key already exists.
 *
 * @param key [Object]
 * @param value [Object]
 * @return [Btree] self
 */
VALUE
rbtree_set(VALUE self, VALUE key, VALUE value)
{
  EXTRACT_RBTREE_SELF(rbtree);

  g_tree_replace(rbtree->gtree, (gpointer) key, (gpointer) value);

  return self;
}

/**
 * Gets value by key from tree.
 *
 * * Returns +nil+ if key does not exist.
 *
 * @param key [Object]
 * @return [Object] result
 */
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

/**
 * Deletes key/value pair from tree.
 *
 * * Returns value if key exists
 * * Returns +nil+ if key does not exists
 * * Returns result of block if block was given
 *
 * @param key [Object] Key
 * @return [Object] result
 */
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
      return rb_yield(key);
    }

    return Qnil;
  }
}

/**
 * Returns tree height
 *
 * @return [Integer] maximum nodes in path from root to leaf
 */
VALUE
rbtree_height(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint size = g_tree_height(rbtree->gtree);
  VALUE result = INT2NUM(size);

  return result;
}

/**
 * Returns number of nodes
 *
 * @return [Integer] number of nodes
 */
VALUE
rbtree_size(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint size = g_tree_nnodes(rbtree->gtree);
  VALUE result = INT2NUM(size);

  return result;
}

/**
 * Remove all nodes from tree.
 *
 * @return [Btree] self
 */
VALUE
rbtree_clear(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  #ifdef HAS_GTREE_REMOVE_ALL
    g_tree_remove_all(rbtree->gtree);
  #else
    g_tree_foreach(rbtree->gtree, rbtree_remove_node, (gpointer) rbtree);
  #endif

  return self;
}


/**
 * Checks that the given key is in the tree.
 *
 * @param key [Object]
 * @return [Boolean] result
 */
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

/**
 * Checks that self tree is empty.
 *
 * @return [Boolean] result
 */
VALUE
rbtree_is_empty(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  gint size = g_tree_nnodes(rbtree->gtree);

  return size > 0 ? Qfalse : Qtrue;
}

/**
 * Checks if two trees are equal.
 *
 * Compares with +==+ method all keys and values from trees by order.
 *
 * * Returns +false+ if number of keys are not equal.
 * * Returns +false+ if one keys or one values pair are not equal.
 * * Returns +true+ if all keys and values are equal.
 *
 * @param second [Btree]
 * @return [Boolean] result
 */
VALUE
rbtree_equal(VALUE self, VALUE second)
{
  EXTRACT_RBTREE_SELF(rbtree);
  EXTRACT_RBTREE(second, rbtree2);

  gint self_size = g_tree_nnodes(rbtree->gtree);
  gint second_size = g_tree_nnodes(rbtree2->gtree);

  VALUE result = Qfalse;

  if (self_size != second_size) {
    goto ret;
  }

  if (self_size == 0) {
    result = Qtrue;
    goto ret;
  }

#ifdef HAS_GTREE_NODE
  if (rbtree_compare_trees(rbtree, rbtree2)) {
    result = Qtrue;
  }
#else
  if (legacy_rbtree_compare(rbtree, rbtree2)) {
    result = Qtrue;
  }
#endif

  ret:
  return result;
}

/**
 * Returns value from smallest key
 *
 * @return [Object] result
 */
VALUE
rbtree_first(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

#ifdef HAS_GTREE_NODE
  GTreeNode *node = g_tree_node_first(rbtree->gtree);

  if (!node) {
    return Qnil;
  }

  return (VALUE) g_tree_node_value(node);
#else
  RBTreeSearchContext context = {
    Qnil,
    NULL,
    1,
    0,
    NULL
  };

  g_tree_foreach(rbtree->gtree, rbtree_first_cb, &context);

  if (context.counter) {
    return Qnil;
  }

  return (VALUE) context.something;
#endif
}

/**
 * Returns value from largest key
 *
 * @return [Object] result
 */
VALUE
rbtree_last(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

#ifdef HAS_GTREE_NODE
  GTreeNode *node = g_tree_node_last(rbtree->gtree);

  if (!node) {
    return Qnil;
  }

  return (VALUE) g_tree_node_value(node);
#else
  RBTreeSearchContext context = {
    Qnil,
    NULL,
    0,
    0,
    NULL
  };

  g_tree_foreach(rbtree->gtree, rbtree_last_cb, &context);

  if (!context.counter) {
    return Qnil;
  }

  return (VALUE) context.something;
#endif
}
