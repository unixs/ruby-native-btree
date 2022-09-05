#include <comparator.h>

gint
rbtree_native_comparator(gconstpointer a, gconstpointer b, gpointer data)
{
  RBTree *rbtree = (RBTree *) data;

  VALUE result = rb_funcall(rbtree->comparator, rb_intern("call"), 2, (VALUE) a, (VALUE) b);

  gint compare_result = NUM2INT(result);

  return compare_result;
}
