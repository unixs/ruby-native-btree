#include <ruby.h>
#include <glib.h>

#include "native_btree.h"
#include "btree.h"


extern "C" {

class BTreeEQCtxt {
  public:
    VALUE eq = Qtrue;
    BTree *tree2 = nullptr;
};

static void
btree_free(BTree *btree)
{
  delete btree;
}

static void
btree_mark(gpointer obj)
{
  reinterpret_cast<BTree *>(obj)->mark();
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

// TODO: Need implementation
VALUE
btree_cmp(VALUE self, VALUE tree2)
{
  return Qnil;
}

static gboolean
eql_comparator(gpointer k, gpointer v, gpointer data)
{
  VALUE key = reinterpret_cast<VALUE>(k);
  VALUE val = reinterpret_cast<VALUE>(v);
  BTreeEQCtxt *context = reinterpret_cast<BTreeEQCtxt *>(data);

  VALUE val2 = context->tree2->get(key);

  // key not found
  if (NIL_P(val2)) {
    context->eq = Qfalse;

    return TRUE;
  }

  // values !eql
  if (!rb_eql(val, val2)) {
    context->eq = Qfalse;

    return TRUE;
  }

  return FALSE;
}

static VALUE//      obj         arg        recur
recursive_eql(VALUE tree, VALUE tree2, int recur)
{
  if (recur)
    return Qtrue; /* Subtle! */

  BTree *t, *t2;
  Data_Get_Struct(tree, BTree, t);
  Data_Get_Struct(tree2, BTree, t2);

  BTreeEQCtxt context;
  // context.eq == Qtrue;

  context.tree2 = t2;

  t->each(eql_comparator, reinterpret_cast<gpointer>(&context));

  return context.eq;
}

VALUE
btree_equal(VALUE self, VALUE tree2)
{
  BTree *t, *t2;
  Data_Get_Struct(self, BTree, t);
  Data_Get_Struct(tree2, BTree, t2);

  if (self == tree2)
    return Qtrue;

  if (CLASS_OF(tree2) != btree_class)
    return Qfalse;

  if (t->size() != t2->size() || t->height() != t2->height())
    return Qfalse;

  if (t->size() == 0)
    return Qtrue;
  //                              func           obj   paired arg
  return rb_exec_recursive_paired(recursive_eql, self, tree2, tree2);
}

}
