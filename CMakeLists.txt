cmake_minimum_required(VERSION 3.10)
project(code_analyse)

include_directories(/home/whj/rose_install/include/rose)
include_directories(/home/whj/boost/1.61.0/include)
include_directories(./include)

aux_source_directory(./src SRC_DIR)
aux_source_directory(./include INC_DIR)

set(CMAKE_CXX_STANDARD 11)

link_directories(/home/whj/rose_install/lib)
link_directories(/home/whj/boost/1.61.0/lib)

link_libraries(rose boost_system)

add_executable(my_le ${SRC_DIR} ${INC_DIR})
