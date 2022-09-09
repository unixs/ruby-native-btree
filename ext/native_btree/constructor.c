#include <comparator.h>
#include <rbtree_type.h>

VALUE
rbtree_initialize(VALUE self)
{
  EXTRACT_RBTREE_SELF(rbtree);

  rbtree->gtree = g_tree_new_with_data(
    rbtree_native_comparator,
    rbtree
  );

  rb_need_block();
  rbtree->comparator = rb_block_proc();

  return self;
}
