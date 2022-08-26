set(EXT_NAME "native_btree")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${EXT_NAME})

include_directories(include)

pkg_check_modules(GLIB2 REQUIRED glib-2.0)

# include_directories(include ${GLIB2_INCLUDE_DIRS})
add_library(${EXT_NAME}
	SHARED
	native_btree.c)

#set_target_properties(${EXT_NAME} PROPERTIES BUNDLE TRUE)


#target_link_libraries(${EXT_NAME}
#	PRIVATE
#	${GLIB2_LDFLAGS})

