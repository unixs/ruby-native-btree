#include <ruby.h>

VALUE btree_class;
VALUE btree_module;
VALUE btree_class_from;

VALUE
btree_from(VALUE klass);

VALUE
btree_from(VALUE klass)
{
  VALUE result = INT2NUM(10);

  return result;
}

void
Init_native_btree()
{
  btree_module = rb_define_module("NativeBtree");
  btree_class = rb_define_class_under(btree_module, "BTree", rb_cObject);
  rb_define_singleton_method(btree_class, "from", btree_from, 0);
}

