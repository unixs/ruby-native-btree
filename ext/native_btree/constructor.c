#include <comparator.h>
#include <rbtree_type.h>
#include <stdbool.h>

inline static void
init_rbtree(RBTree *rbtree, gushort flags)
{
  bool flag_int_comparator = flags & RBTREE_FLAG_INT_COMPARATOR;
  VALUE comparator = Qnil;
  // NOTE: Possible segfault
  GCompareDataFunc native_comparator = NULL;

  if (flag_int_comparator) {
    native_comparator = rbtree_int_comparator;
  }
  else {
    rb_need_block();
    comparator = rb_block_proc();
    native_comparator = rbtree_native_comparator;
  }

  rbtree->gtree = g_tree_new_with_data(
    native_comparator,
    rbtree
  );
  rbtree->comparator = comparator;
  rbtree->flags = flags;
}

/**
 * Constructor
 *
 * Accepts block as "comparator" function.
 * This function will recive two keys for comparison.
 *
 * @return [Btree] new instance
 */
VALUE
rbtree_initialize(int argc, VALUE* argv, VALUE self)
{
  rb_check_arity(argc, 0, 1);

  EXTRACT_RBTREE_SELF(rbtree);

  gushort flags = 0;

  if (argc > 0) {
    flags = NUM2USHORT(argv[0]);
  }

  init_rbtree((RBTree *) rbtree, flags);

  return self;
}
