#include <rbtree_type.h>

const rb_data_type_t rbtree_type;


static void
rbtree_type_free(gpointer data)
{
  RBTree *rbtree = (RBTree *) data;

  if (rbtree->gtree) {
    g_tree_destroy(rbtree->gtree);
  }

  g_free(data);
}


static gboolean
rbtree_mark_callback(gpointer key, gpointer value, gpointer data)
{
  rb_gc_mark((VALUE) key);
  rb_gc_mark((VALUE) value);

  return FALSE;
}


static void
rbtree_type_mark(gpointer data)
{
  RBTree *rbtree = (RBTree *) data;

  if (!NIL_P(rbtree->comparator)) {
    rb_gc_mark(rbtree->comparator);
  }

  g_tree_foreach(rbtree->gtree, rbtree_mark_callback, NULL);
}

/*

https://github.com/GNOME/glib/blob/main/glib/gtree.c#L80

struct _GTree
{
  GTreeNode *root;
  GCompareDataFunc key_compare;
  GDestroyNotify key_destroy_func;
  GDestroyNotify value_destroy_func;
  gpointer key_compare_data;
  guint nnodes;
  gint ref_count;
};

struct _GTreeNode
{
  gpointer key;
  gpointer value;
  GTreeNode *left;
  GTreeNode *right;
  gint8 balance;
  guint8 left_child;
  guint8 right_child;
};
*/

static size_t
rbtree_type_size(gconstpointer data)
{
  RBTree *rbtree = (RBTree *) data;

  gint gtree_size = g_tree_nnodes(rbtree->gtree);

  // struct _GTreeNode
  size_t node_size = sizeof(gpointer) * 4 +
                     sizeof(gint8) +
                     sizeof(guint8) * 2;

  // struct _GTree
  size_t gtree_root_size = sizeof(gpointer) * 5 +
                           sizeof(gint8) +
                           sizeof(guint8) * 2;

  return sizeof(RBTree) + node_size * gtree_size + gtree_root_size;
}


const rb_data_type_t rbtree_type = {
  .wrap_struct_name = RBTREE_NATIVE_TYPE_NAME,
  .function = {
    .dmark = rbtree_type_mark,
    .dfree = rbtree_type_free,
    .dsize = rbtree_type_size,
  },
  .data = NULL,
  .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};


VALUE
rbtree_alloc(VALUE self)
{
  RBTree *rbtree = g_new(RBTree, 1);

  rbtree->gtree = NULL;
  rbtree->comparator = Qnil;
  rbtree->flags = 0;

  return TypedData_Wrap_Struct(self, &rbtree_type, rbtree);
}


VALUE
rbtree_clone_wrap(const RBTree *orig)
{
  const VALUE rflags = USHORT2NUM(orig->flags);

  VALUE new_tree = rb_funcall_with_block(
    native_btree_class,
    rb_intern("new"),
    orig->flags ? 1 : 0,
    orig->flags ? &rflags : NULL,
    orig->comparator
  );

  return new_tree;
}
