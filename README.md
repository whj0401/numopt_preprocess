# numopt_preprocess
preprocess of numopt, it generates the pth file.

# configure manually
modify 'src/common.cpp'
'/home/whj/numopt_preprocess' is my program directory, change it to yours
const std::string klee_output_dir = "/home/whj/numopt_preprocess/klee_output/";

modify CMakeList.txt
'/home/whj/rose_install' is my rose_install directory, change it to yours
'/home/whj/boost/1.61.0' is my boost directory, change it to yours
include_directories(/home/whj/rose_install/include/rose)
include_directories(/home/whj/boost/1.61.0/include)

link_directories(/home/whj/rose_install/lib)
link_directories(/home/whj/boost/1.61.0/lib)

modify run_le.sh
'/home/whj/iRRAM' is my iRRAM directory, change it to yours
iRRAM_HOME=/home/whj/iRRAM

modify klee_output/run_klee.sh
'/home/whj/myself_klee/klee' is my klee directory, change it to yours
KLEE_DIR=/home/whj/myself_klee/klee
klee see [here](https://github.com/whj0401/klee)
