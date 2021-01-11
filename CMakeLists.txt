cmake_minimum_required(VERSION 3.16)
project (Soccer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread ")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Soccer_SOURCE_DIR}/cmake")
set(APP_TARGET Soccer)




file(GLOB core_src
    "src/*/*.cpp"
)

add_executable(${APP_TARGET}
	main.cpp
    ${core_src}
)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
target_include_directories(
    ${APP_TARGET}
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
find_package(spdlog REQUIRED)


target_link_libraries(${APP_TARGET} ${SPDLOG_LIBRARIES}  ${EnTT_LIBRARIES})
target_link_libraries(${APP_TARGET} ${LUA_LIBRARIES})

target_compile_features(${APP_TARGET}
    PRIVATE
    cxx_std_17
)