require "mkmf"

local_include = %w(
  $(srcdir)/include
);

ldflags = cppflags = nil

pkg_config "glib-2.0"
dir_config 'glib', cppflags, ldflags

abort "Can't find the glib.h header"  unless find_header 'glib.h'
abort "Can't find the glib libary'"   unless find_library 'glib-2.0', 'g_tree_new_full'
abort "g_tree_insert() not found"     unless have_func 'g_tree_insert'
abort "g_tree_replace() not found"    unless have_func 'g_tree_replace'
abort "g_tree_nnodes() not found"     unless have_func 'g_tree_nnodes'
abort "g_tree_lookup() not found"     unless have_func 'g_tree_lookup'
abort "g_tree_foreach() not found"    unless have_func 'g_tree_foreach'
abort "g_tree_search() not found"     unless have_func 'g_tree_search'
abort "g_tree_destroy() not found"    unless have_func 'g_tree_destroy'
abort "g_tree_height() not found"     unless have_func 'g_tree_height'

$VPATH.concat %w(
  $(srcdir)/include
)

$INCFLAGS << local_include.map{|dir| " -I#{dir}" }.join("")
CONFIG["debugflags"] = "-ggdb3"
CONFIG["optflags"] = "-O0"

$CXXFLAGS += "-O0 -ggdb3 -pipe"

create_header
create_makefile "native_btree/native_btree"
