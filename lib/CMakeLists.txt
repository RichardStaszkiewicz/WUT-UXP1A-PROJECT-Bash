add_library(shell_lib STATIC ${SRC})

# Z jakich plików źródłowych ma się składać
target_include_directories(shell_lib PUBLIC BEFORE ${CMAKE_SOURCE_DIR}/include)
