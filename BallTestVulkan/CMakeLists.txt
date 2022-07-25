cmake_minimum_required(VERSION 3.10)

#set the project name
project(BallTest)

add_executable(BallTestVulkan WIN32 
BallLuaBinding.h
BallLuaBinding.cpp
BallTestVulkan.h
BallTestVulkan.cpp
Resource.h
SimpleBall.h
SimpleBall.cpp
SimpleBox.h
SimpleBox.cpp
SpriteFactory.h
SpriteFactory.cpp
targetver.h
smile.png
script.lua
BallTestVulkan.ico
small.ico
BallTestVulkan.rc
basic.vert
circlecolor.frag
textured.frag
basic.vert.spv
circlecolor.frag.spv
textured.frag.spv
)

target_link_libraries(BallTestVulkan PRIVATE KEngineCore KEngine2D KEngineBox2D KEngineVulkan)

find_package(Vulkan COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)



add_custom_command(
	OUTPUT basic.vert.spv
	DEPENDS basic.vert		
	COMMAND ${glslc_executable} basic.vert -o basic.vert.spv
)
add_custom_command(
	OUTPUT circlecolor.frag.spv
	DEPENDS circlecolor.frag		
	COMMAND ${glslc_executable} circlecolor.frag -o circlecolor.frag.spv
)
add_custom_command(
	OUTPUT textured.frag.spv
	DEPENDS textured.frag		
	COMMAND ${glslc_executable} textured.frag -o textured.frag.spv
)


#compile_shader(basic.vert)
#compile_shader(circlecolor.frag)
#compile_shader(textured.frag)