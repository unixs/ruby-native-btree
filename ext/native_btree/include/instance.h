#include <common.h>

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
