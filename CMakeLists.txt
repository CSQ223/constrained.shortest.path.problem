cmake_minimum_required(VERSION 3.0)

project(cmake.demo
        VERSION 1.0)

# 设置编译类型
set(CMAKE_BUILD_TYPE "Debug")
# 设置仓库位置 绝对路径
set(REPO_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/repository")

# 输出cmake调试信息
option(CMAKE_DEBUG "Add debug information" ON)
option(INSTALL_DEP "Install dependencies to target directory" ON)
option(IGNORE_MSVC_VERSION "ignore MSVC version" ON)
  
# 添加脚手架
add_subdirectory("cmake.utils")
# 添加第三方库
add_subdirectory("third_party")

init_env()

# 添加项目文件
add_project("network")

# 添加tests
add_project("tests")

# 添加tests
add_project("example")
