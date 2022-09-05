set(EXT_NAME "native_btree")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${EXT_NAME})

message(STATUS "Find ext deps.")

pkg_check_modules(GLIB2 REQUIRED glib-2.0)

include_directories(include ${GLIB2_INCLUDE_DIRS})

add_library(rbtree_type OBJECT rbtree_type.c)
add_library(constructor OBJECT constructor.c)
add_library(instance OBJECT instance.c)
add_library(comparator OBJECT comparator.c)
add_library(iterators OBJECT iterators.c)

add_library(${EXT_NAME}
	SHARED
	native_btree.c)

target_link_libraries(${EXT_NAME}
	PRIVATE
	iterators
	rbtree_type
	constructor
	instance
	comparator
	${GLIB2_LDFLAGS})
	#set_target_properties(${EXT_NAME} PROPERTIES BUNDLE TRUE)
