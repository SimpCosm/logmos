cmake_minimum_required (VERSION 2.8)
project (logmos)

# default install prefix is CMAKE_INSTALL_PREFIX: /usr/local
set(RUNTIME_DIR bin)
set(LIBRARY_DIR lib)
set(INCLUDE_DIR include)
set(DOC_DIR "share/doc/${CPACK_PACKAGE_NAME}")
set(DATA_DIR share/${CPACK_PACKAGE_NAME})

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
#add_subdirectory(example)

