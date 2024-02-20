cmake_minimum_required(VERSION 3.12)
project(VulkanExample LANGUAGES CXX VERSION 0.0.1)

# main source code
set(SOURCE_MAIN src/vulkan_example/main.cc
                src/app/app_hello.cc
                src/engine/de_window.cc
                src/engine/de_engine.cc
                src/engine/de_pipeline.cc
)

# find the required libraries
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

# main excutable
add_executable(vulkan_example ${SOURCE_MAIN})

# include header folder
target_include_directories(vulkan_example PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(vulkan_example PRIVATE ${CMAKE_SOURCE_DIR}/external)

# external libraries
add_subdirectory(external)
target_link_libraries(vulkan_example PRIVATE glfw)
target_link_libraries(vulkan_example PRIVATE Vulkan::Vulkan)
target_link_libraries(vulkan_example PRIVATE libimgui)
