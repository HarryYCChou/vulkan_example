# ImGui
# setup root directory
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
# add source files
set(SOURCES ${IMGUI_DIR}/imgui.cpp
            ${IMGUI_DIR}/imgui_demo.cpp
            ${IMGUI_DIR}/imgui_draw.cpp
            ${IMGUI_DIR}/imgui_tables.cpp
            ${IMGUI_DIR}/imgui_widgets.cpp
            ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
            ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp)
# create a library
add_library(libimgui OBJECT ${SOURCES})
# include header folder
target_include_directories(libimgui PUBLIC ${IMGUI_DIR})
