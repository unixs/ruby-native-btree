#ifndef _NATIVE_BTREE_

#define NATIVE_BTREE "NativeBtree"
#define NATIVE_BTREE_CLASS "Btree"


#if defined(__cplusplus)
extern "C" {
#endif

extern VALUE btree_class;
extern VALUE btree_module;
extern VALUE btree_class_from;

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

VALUE
btree_cmp(VALUE self, VALUE tree2);

VALUE
btree_equal(VALUE self, VALUE tree2);

#if defined(__cplusplus)
}
#endif

#endif // _NATIVE_BTREE_
