#include <native_btree.h>
#include <rbtree_type.h>

#define NATIVE_BTREE_MODULE "NativeBtree"
#define NATIVE_BTREE_CLASS "Btree"


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

  // rb_include_module(native_btree_class, rb_mEnumerable);

  rb_define_alloc_func(native_btree_class, rbtree_alloc);
  rb_define_method(native_btree_class, "initialize", rbtree_initialize, 0);

  rb_define_method(native_btree_class, "[]=", rbtree_set, 2);
  rb_define_alias(native_btree_class, "set", "[]=");
  rb_define_method(native_btree_class, "[]", rbtree_get, 1);
  rb_define_alias(native_btree_class, "get", "[]");
  rb_define_method(native_btree_class, "delete", rbtree_delete, 1);
  rb_define_method(native_btree_class, "each", rbtree_each, 0);
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
}
