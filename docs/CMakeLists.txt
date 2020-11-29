find_package(Doxygen)

if(DOXYGEN_FOUND STREQUAL "NO")
  message(STATUS "Doxygen not found. Please get a copy http://www.doxygen.org")
endif()

# prepare doxygen configuration file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# add doxygen as target
add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  # POST_BUILD
  # COMMAND ${CMAKE_COMMAND} -E copy_if_different
  # "${CMAKE_CURRENT_SOURCE_DIR}/navtree.js" ${CMAKE_CURRENT_BINARY_DIR}/html/navtree.js
  # COMMAND ${CMAKE_COMMAND} -E copy_if_different
  # "${CMAKE_CURRENT_SOURCE_DIR}/navtreeindex0.js" ${CMAKE_CURRENT_BINARY_DIR}/html/navtreeindex0.js
  )

# add docs as custom target
add_custom_target(docs doxygen
# POST_BUILD
COMMAND jekyll build -s "${CMAKE_CURRENT_SOURCE_DIR}/jekyll/" -d "${CMAKE_CURRENT_BINARY_DIR}/jekyll/"
COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_BINARY_DIR}/jekyll/" "${CMAKE_CURRENT_BINARY_DIR}/html/"
)

# cleanup $build/html on "make clean"
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES html)
