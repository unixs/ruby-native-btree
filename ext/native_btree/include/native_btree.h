#ifndef _NATIVE_BTREE_
#include <ruby.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern VALUE btree_class;
extern VALUE btree_module;

VALUE
btree_new(VALUE klass);

VALUE
btree_init(VALUE self);

VALUE
btree_size(VALUE self);

VALUE
btree_height(VALUE self);

VALUE
btree_set(VALUE self, VALUE key, VALUE value);

VALUE
btree_get(VALUE self, VALUE key);

VALUE
btree_delete(VALUE self, VALUE key);

VALUE
btree_clear(VALUE self);

VALUE
btree_has(VALUE self, VALUE key);

VALUE
btree_each(VALUE self);

#if defined(__cplusplus)
}
#endif

#endif // _NATIVE_BTREE_
