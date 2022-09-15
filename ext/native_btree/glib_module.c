#include <stdbool.h>
#include <common.h>
#include <glib_module.h>

#define NATIVE_BTREE_GLIB_SUBMODULE "Glib"
#define GLIB_MODULE_MAJOR_VERSION "MAJOR_VERSION"
#define GLIB_MODULE_MINOR_VERSION "MINOR_VERSION"
#define GLIB_MODULE_MICRO_VERSION "MICRO_VERSION"

VALUE rbtree_glib_module;

void
rbtree_attach_module_glib()
{
  static bool initialized = FALSE;

  if (initialized) {
    return;
  }

  rbtree_glib_module = rb_define_module_under(
    native_btree_module,
    NATIVE_BTREE_GLIB_SUBMODULE
  );

  rb_define_const(
    rbtree_glib_module,
    GLIB_MODULE_MAJOR_VERSION,
    INT2NUM(GLIB_MAJOR_VERSION)
  );

  rb_define_const(
    rbtree_glib_module,
    GLIB_MODULE_MINOR_VERSION,
    INT2NUM(GLIB_MINOR_VERSION)
  );

  rb_define_const(
    rbtree_glib_module,
    GLIB_MODULE_MICRO_VERSION,
    INT2NUM(GLIB_MICRO_VERSION)
  );

  initialized = TRUE;
}
