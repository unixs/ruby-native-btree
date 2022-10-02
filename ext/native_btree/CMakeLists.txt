set(EXT_NAME "native_btree")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${EXT_NAME})

message(STATUS "Find ext deps.")

pkg_check_modules(GLIB2 REQUIRED glib-2.0)

include_directories(include ${GLIB2_INCLUDE_DIRS})

list(APPEND CMAKE_REQUIRED_LIBRARIES ${GLIB2_LDFLAGS})
list(APPEND CMAKE_REQUIRED_INCLUDES ${GLIB2_INCLUDE_DIRS})
check_symbol_exists(g_tree_remove_all "glib.h" HAS_GTREE_REMOVE_ALL)
check_symbol_exists(g_tree_lookup_node "glib.h" HAS_GTREE_NODE)

if(HAS_GTREE_REMOVE_ALL)
	add_compile_definitions(HAS_GTREE_REMOVE_ALL)
endif()

if(HAS_GTREE_NODE)
	add_compile_definitions(HAS_GTREE_NODE)
	add_subdirectory("glib2_68")
else()
	message(WARNING
		"Available GLib is not support direct node access.
		Version < 2.68.
		Additional iterators will not compile.
		Comparison operator (==) will consume extra mem for to_h conversion\
		under the hood")
endif()

add_library(${EXT_NAME}
	SHARED
	native_btree.c)

add_library(rbtree_type OBJECT rbtree_type.c)
add_library(constructor OBJECT constructor.c)
add_library(instance OBJECT instance.c)
add_library(comparator OBJECT comparator.c)
add_library(iterators OBJECT iterators.c)
add_library(conversion OBJECT conversion.c)
add_library(search OBJECT search.c)
add_library(glib_module OBJECT glib_module.c)


set(LIB_OBJECTS)
list(APPEND LIB_OBJECTS
	$<TARGET_OBJECTS:conversion>
	$<TARGET_OBJECTS:iterators>
	$<TARGET_OBJECTS:comparator>
	$<TARGET_OBJECTS:instance>
	$<TARGET_OBJECTS:constructor>
	$<TARGET_OBJECTS:rbtree_type>
	$<TARGET_OBJECTS:search>
	$<TARGET_OBJECTS:glib_module>)

if(HAS_GTREE_NODE)
	list(APPEND LIB_OBJECTS $<TARGET_OBJECTS:additional_iterators>)
	list(APPEND LIB_OBJECTS $<TARGET_OBJECTS:compare_trees>)
endif()

add_library(native_btree_interface
	STATIC
	${LIB_OBJECTS})

target_link_libraries(${EXT_NAME}
	PRIVATE
	native_btree_interface
	${GLIB2_LDFLAGS})
