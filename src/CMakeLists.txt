set(SOURCES logger.cc)

add_library(logmos STATIC ${SOURCES})
install(TARGETS logmos DESTINATION ${LIBRARY_DIR})
