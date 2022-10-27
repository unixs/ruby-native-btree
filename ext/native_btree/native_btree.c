#include <native_btree.h>
#include <rbtree_type.h>
#include <glib_module.h>

#define NATIVE_BTREE_MODULE "NativeBtree"
#define NATIVE_BTREE_CLASS "Btree"
#define NATIVE_BTREE_CONST_INT_COMPARATOR "INT_COMPARATOR"


VALUE native_btree_class;
VALUE native_btree_module;

void
Init_native_btree()
{
  native_btree_module = rb_define_module(NATIVE_BTREE_MODULE);
  native_btree_class = rb_define_class_under(
    native_btree_module,
    NATIVE_BTREE_CLASS,
    rb_cObject
  );

  VALUE int_comparator = USHORT2NUM(RBTREE_FLAG_INT_COMPARATOR);
  OBJ_FREEZE(int_comparator);
  rb_define_const(
    native_btree_class,
    NATIVE_BTREE_CONST_INT_COMPARATOR,
    int_comparator
  );

  rbtree_attach_module_glib();

  // rb_include_module(native_btree_class, rb_mEnumerable);

  rb_define_alloc_func(native_btree_class, rbtree_alloc);
  rb_define_method(native_btree_class, "initialize", rbtree_initialize, -1);

  rb_define_method(native_btree_class, "[]=", rbtree_set, 2);
  rb_define_alias(native_btree_class, "set", "[]=");
  rb_define_method(native_btree_class, "[]", rbtree_get, 1);
  rb_define_alias(native_btree_class, "get", "[]");
  rb_define_method(native_btree_class, "delete", rbtree_delete, 1);
  rb_define_method(native_btree_class, "each", rbtree_each, 0);
  rb_define_method(native_btree_class, "each_key", rbtree_each_key, 0);
  rb_define_method(native_btree_class, "each_value", rbtree_each_value, 0);
  rb_define_method(native_btree_class, "size", rbtree_size, 0);
  rb_define_method(native_btree_class, "height", rbtree_height, 0);
  rb_define_method(native_btree_class, "clear", rbtree_clear, 0);
  rb_define_method(native_btree_class, "include?", rbtree_is_include, 1);
  rb_define_method(native_btree_class, "to_h", rbtree_to_h, 0);
  rb_define_method(native_btree_class, "to_a", rbtree_to_a, 0);
  rb_define_method(native_btree_class, "to_proc", rbtree_to_proc, 0);
  rb_define_method(native_btree_class, "filter", rbtree_filter, 0);
  rb_define_alias(native_btree_class, "select", "filter");
  rb_define_method(native_btree_class, "filter!", rbtree_filter_bang, 0);
  rb_define_alias(native_btree_class, "select!", "filter!");
  rb_define_method(native_btree_class, "empty?", rbtree_is_empty, 0);
  rb_define_method(native_btree_class, "==", rbtree_equal, 1);
  rb_define_method(native_btree_class, "reverse_each", rbtree_reverse_each, 0);
  rb_define_method(native_btree_class, "first", rbtree_first, 0);
  rb_define_alias(native_btree_class, "min", "first");
  rb_define_method(native_btree_class, "last", rbtree_last, 0);
  rb_define_alias(native_btree_class, "max", "last");
  rb_define_method(native_btree_class, "delete_if", rbtree_delete_if, 0);
  rb_define_method(native_btree_class, "to_s", rbtree_to_s, 0);
  rb_define_alias(native_btree_class, "inspect", "to_s");

#ifdef HAS_GTREE_NODE
  rb_define_method(native_btree_class, "select_before", rbtree_select_before, 1);
  rb_define_method(native_btree_class, "select_after", rbtree_select_after, 1);
#endif
}
