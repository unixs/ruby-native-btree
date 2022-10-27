#ifndef _NATIVE_BTREE_

#include <ruby.h>

VALUE
rbtree_initialize(int argc, VALUE *argv, VALUE self);

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
rbtree_each_key(VALUE self);

VALUE
rbtree_each_value(VALUE self);

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

VALUE
rbtree_is_empty(VALUE self);

VALUE
rbtree_select_before(VALUE self, VALUE target);

VALUE
rbtree_select_after(VALUE self, VALUE target);

VALUE
rbtree_select_between(VALUE self, VALUE from, VALUE to);

VALUE
rbtree_flatten(VALUE self);

VALUE
rbtree_delete_if(VALUE self);

VALUE
rbtree_has_key(VALUE self, VALUE key);

VALUE
rbtree_has_value(VALUE self, VALUE value);

VALUE
rbtree_eql(VALUE self, VALUE tree);

VALUE
rbtree_keys(VALUE self);

VALUE
rbtree_values(VALUE self);

VALUE
rbtree_equal(VALUE self, VALUE btree);

VALUE
rbtree_reverse_each(VALUE self);

VALUE
rbtree_first(VALUE self);

VALUE
rbtree_last(VALUE self);

VALUE
rbtree_to_s(VALUE self);

#endif // _NATIVE_BTREE_
