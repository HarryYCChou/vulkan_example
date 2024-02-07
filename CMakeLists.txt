cmake_minimum_required(VERSION 3.12)
project(VulkanExample LANGUAGES CXX VERSION 0.0.1)

# main source code
set(SOURCE_MAIN src/vulkan_example/main.cc)

# find the required libraries
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

# main excutable
add_executable(vulkan_example ${SOURCE_MAIN})

# include header folder
target_include_directories(vulkan_example PRIVATE ${CMAKE_SOURCE_DIR}/include)

# external libraries
target_link_libraries(vulkan_example PRIVATE glfw)
target_link_libraries(vulkan_example PRIVATE Vulkan::Vulkan)
#add_subdirectory(external)
#target_link_libraries(main PRIVATE external)