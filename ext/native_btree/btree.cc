#include "btree.h"

BTree::BTree(VALUE comnparator)
{
  this->comparator = comnparator;
  this->tree = g_tree_new_with_data(BTree::nativeComparator, this);
}

BTree::~BTree()
{
  g_tree_destroy(this->tree);
}

void
BTree::mark()
{
  rb_gc_mark(this->comparator);
  this->markMyRValues();
}

void
BTree::markMyRValues()
{
  g_tree_foreach(this->tree, BTree::markRValue, NULL);
}

gint
BTree::markRValue(gpointer k, gpointer v, gpointer not_used)
{
  const VALUE key = reinterpret_cast<VALUE>(k);
  const VALUE value = reinterpret_cast<VALUE>(v);

  rb_gc_mark(key);
  rb_gc_mark(value);

  return false;
}

gint
BTree::nativeComparator(gconstpointer a, gconstpointer b, gpointer data)
{
  const BTree *tree = static_cast<BTree *>(data);
  const VALUE keyA = reinterpret_cast<VALUE>(a);
  const VALUE keyB = reinterpret_cast<VALUE>(b);

  VALUE ruby_result = rb_funcall(tree->comparator, rb_intern("call"), 2, keyA, keyB);

  return NUM2INT(ruby_result);
}

gint
BTree::size()
{
  return g_tree_nnodes(this->tree);
}

gint
BTree::height()
{
  return g_tree_height(this->tree);
}

void
BTree::set(VALUE key, VALUE value)
{
  g_tree_replace(this->tree, (gpointer) key, (gpointer) value);
}

VALUE
BTree::get(VALUE key)
{
  gpointer result = g_tree_lookup(this->tree, reinterpret_cast<gconstpointer>(key));

  if (!result) {
    return Qnil;
  }

  return reinterpret_cast<VALUE>(result);
}

bool
BTree::del(VALUE key)
{
  return g_tree_remove(this->tree, reinterpret_cast<gconstpointer>(key));
}

void
BTree::clear()
{
  g_tree_unref(this->tree);
  this->tree = g_tree_new_with_data(BTree::nativeComparator, this);
}

bool
BTree::has(VALUE key)
{
  bool result = g_tree_lookup(this->tree, reinterpret_cast<gconstpointer>(key));

  if (!result) {
    return true;
  }

  return false;
}

gboolean
BTree::traverseFunc(gpointer k, gpointer v, gpointer b)
{
  const VALUE key = reinterpret_cast<VALUE>(k);
  const VALUE value = reinterpret_cast<VALUE>(v);
  const VALUE block = reinterpret_cast<VALUE>(b);

  rb_funcall(block, rb_intern("call"), 2, key, value);

  return FALSE;
}

void
BTree::each(VALUE block)
{
  g_tree_foreach(this->tree, BTree::traverseFunc, reinterpret_cast<gpointer>(block));
}
