#include <native_btree.h>

VALUE rbtree_class;
VALUE rbtree_module;


void
Init_native_btree()
{
  rbtree_module = rb_define_module(NATIVE_BTREE_MODULE);
  rbtree_class = rb_define_class_under(rbtree_module, NATIVE_BTREE_CLASS, rb_cObject);

  rb_define_alloc_func(rbtree_class, rbtree_alloc);
  rb_define_method(rbtree_class, "initialize", rbtree_initialize, 0);

  rb_define_method(rbtree_class, "[]=", rbtree_set, 2);
  rb_define_alias(rbtree_class, "set", "[]=");
  rb_define_method(rbtree_class, "[]", rbtree_get, 1);
  rb_define_alias(rbtree_class, "get", "[]");
  rb_define_method(rbtree_class, "delete", rbtree_delete, 1);
  rb_define_method(rbtree_class, "each", rbtree_each, 0);
  rb_define_method(rbtree_class, "size", rbtree_size, 0);
  rb_define_method(rbtree_class, "height", rbtree_height, 0);
  rb_define_method(rbtree_class, "clear", rbtree_clear, 0);
  rb_define_method(rbtree_class, "include?", rbtree_is_include, 1);
  rb_define_method(rbtree_class, "to_h", rbtree_to_h, 0);
  rb_define_method(rbtree_class, "to_a", rbtree_to_a, 0);
  rb_define_method(rbtree_class, "filter", rbtree_filter, 0);
}
