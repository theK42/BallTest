cmake_minimum_required(VERSION 3.10)

#set the project name
project(BallTest)

add_executable(BallTestOpenGL WIN32 
BallLuaBinding.h
BallLuaBinding.cpp
BallTestOpenGL.h
BallTestOpenGL.cpp
Resource.h
SimpleBall.h
SimpleBall.cpp
SimpleBox.h
SimpleBox.cpp
SpriteFactory.h
SpriteFactory.cpp
stdafx.h
stdafx.cpp
targetver.h
basic.vertex.glsl
circlecolor.fragment.glsl
textured.fragment.glsl
smile.png
script.lua
BallTestOpenGL.ico
small.ico
BallTestOpeNGL.rc
)

target_link_libraries(BallTestOpenGL PRIVATE KEngineCore KEngine2D KEngineBox2D KEngineOpenGL)

