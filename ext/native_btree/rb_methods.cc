#include <ruby.h>
#include <glib.h>

#include "native_btree.h"
#include "btree.h"


extern "C" {

static void
btree_free(BTree *btree)
{
  delete btree;
}

static void
btree_mark(gpointer obj)
{
  ((BTree *) obj)->mark();
}

static VALUE
btree_enum_size(VALUE tree, VALUE args, VALUE eobj)
{
  return btree_size(tree);
}


VALUE
btree_new(VALUE klass)
{
  rb_need_block();

  VALUE comparator = rb_block_lambda();

  BTree *tree = new BTree(comparator);

  VALUE instance = Data_Wrap_Struct(klass, btree_mark, btree_free, tree);

  return instance;
}

VALUE
btree_init(VALUE self)
{
  return self;
}

VALUE
btree_size(VALUE self)
{
  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  VALUE result = INT2NUM(tree->size());

  return result;
}

VALUE
btree_height(VALUE self)
{
  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  VALUE result = INT2NUM(tree->height());

  return result;
}


VALUE
btree_set(VALUE self, VALUE key, VALUE value)
{
  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  tree->set(key, value);

  return Qnil;
}

VALUE
btree_get(VALUE self, VALUE key)
{
  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  return tree->get(key);
}

VALUE
btree_delete(VALUE self, VALUE key)
{
  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  bool result = tree->del(key);

  return result ? Qtrue : Qfalse;
}

VALUE
btree_clear(VALUE self)
{
  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  tree->clear();

  return Qnil;
}

VALUE
btree_has(VALUE self, VALUE key)
{
  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  bool result = tree->has(key);

  return result ? Qtrue : Qfalse;
}

VALUE
btree_each(VALUE self)
{
  RETURN_SIZED_ENUMERATOR(self, 0, 0, btree_enum_size);

  VALUE block = rb_block_lambda();

  BTree *tree;
  Data_Get_Struct(self, BTree, tree);

  tree->each(block);

  return Qnil;
}


}
