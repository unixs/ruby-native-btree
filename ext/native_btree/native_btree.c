#include <native_btree.h>

VALUE btree_class;
VALUE btree_module;

void
Init_native_btree()
{
  btree_module = rb_define_module("NativeBTree");
  btree_class = rb_define_class_under(btree_module, "BTree", rb_cObject);

  rb_define_singleton_method(btree_class, "new", btree_new, 0);
  // rb_define_method(btree_class, "initialize", btree_init, 0);
  rb_define_method(btree_class, "size", btree_size, 0);
  rb_define_method(btree_class, "height", btree_height, 0);
  rb_define_method(btree_class, "set", btree_set, 2);
  rb_define_alias(btree_class, "[]=", "set");
  rb_define_method(btree_class, "get", btree_get, 1);
  rb_define_alias(btree_class, "[]", "get");
  rb_define_method(btree_class, "delete", btree_delete, 1);
  rb_define_method(btree_class, "clear", btree_clear, 0);
  rb_define_method(btree_class, "has", btree_has, 1);
  rb_define_method(btree_class, "each", btree_each, 0);
}

