cmake_minimum_required(VERSION 3.30)
project(CGame)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(deps/glfw)

set(IMGUI_FILES
	deps/imgui/imgui.cpp
	deps/imgui/imgui_draw.cpp
	deps/imgui/imgui_widgets.cpp
	deps/imgui/imgui_tables.cpp
	deps/imgui/imgui_demo.cpp
	deps/imgui/backends/imgui_impl_glfw.cpp
	deps/imgui/backends/imgui_impl_opengl3.cpp
)

set(SOURCE_FILES
	deps/glad/src/glad.c	# glad source 
	${IMGUI_FILES}			# imgui source
#########################################
    src/main.cpp
)

set(INCLUDE_DIRS
	src/
	deps/glad/include/
	deps/imgui/
	deps/imgui/backends/
)

add_executable(main ${SOURCE_FILES})
target_include_directories(main PRIVATE ${INCLUDE_DIRS})
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE "-O0")

set(LIBS
	glfw
	GL
)

target_link_libraries(main PRIVATE ${LIBS})
