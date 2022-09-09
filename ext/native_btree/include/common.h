#include <ruby.h>
#include <glib.h>
#include <rbtree_type.h>


#ifndef _NATIVE_BTREE_COMMON_
#define _NATIVE_BTREE_COMMON_

#define EXTRACT_RBTREE(from, to)                                               \
  RBTree *to;                                                                  \
  TypedData_Get_Struct(from, RBTree, &rbtree_type, to)

#define EXTRACT_RBTREE_SELF(to) EXTRACT_RBTREE(self, to)

extern VALUE native_btree_class;
extern VALUE native_btree_module;

#endif //_NATIVE_BTREE_COMMON_
