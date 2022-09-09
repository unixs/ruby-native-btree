#include <ruby.h>
#include <glib.h>

#ifndef _NATIVE_BTREE_COMMON_
#define _NATIVE_BTREE_COMMON_

#include <rbtree_type.h>

#define NATIVE_BTREE_MODULE "NativeBtree"
#define NATIVE_BTREE_CLASS "Btree"

#define EXTRACT_RBTREE(from, to)                                               \
  RBTree *to;                                                                  \
  TypedData_Get_Struct(from, RBTree, &rbtree_type, to)

#define EXTRACT_RBTREE_SELF(to) EXTRACT_RBTREE(self, to)

extern VALUE rbtree_class;
extern VALUE rbtree_module;

#endif //_NATIVE_BTREE_COMMON_
