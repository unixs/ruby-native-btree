#ifndef _NATIVE_BTREE_

#include <ruby.h>

VALUE
rbtree_initialize(VALUE self);

VALUE
rbtree_set(VALUE self, VALUE key, VALUE value);

VALUE
rbtree_get(VALUE self, VALUE key);

VALUE
rbtree_delete(VALUE self, VALUE key);

VALUE
rbtree_size(VALUE self);

VALUE
rbtree_height(VALUE self);

VALUE
rbtree_clear(VALUE self);

VALUE
rbtree_is_include(VALUE self, VALUE key);

VALUE
rbtree_each(VALUE self);

VALUE
rbtree_to_h(VALUE self);

VALUE
rbtree_to_a(VALUE self);

VALUE
rbtree_to_proc(VALUE self);

VALUE
rbtree_filter(VALUE self);

VALUE
rbtree_filter_bang(VALUE self);

#endif // _NATIVE_BTREE_
