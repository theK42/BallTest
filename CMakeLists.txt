cmake_minimum_required(VERSION 3.10)

#set the project name
project(BallTest)

add_subdirectory(KEngineCore)
add_subdirectory(KEngine2D)
add_subdirectory(KEngineBox2D)
add_subdirectory(KEngineOpenGL)
add_subdirectory(BallTestOpenGL)


add_subdirectory(KEngineVulkan)
add_subdirectory(BallTestVulkan)