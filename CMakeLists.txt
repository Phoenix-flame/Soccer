cmake_minimum_required(VERSION 3.16)
project (Soccer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread ")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Soccer_SOURCE_DIR}/cmake")
set(APP_TARGET Soccer)


file(GLOB core_src
    "src/*/*.cpp"
)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
set(GLOB PROTOBUF_MODELS_INCLUDES "")
set(GLOB PROTOBUF_MODELS_SOURCES "")
file(GLOB PROTOBUF_DEFINITION_FILES ${PROJECT_SOURCE_DIR}/protobuf/*.proto)
foreach(file ${PROTOBUF_DEFINITION_FILES})
    set(proto_files "${proto_files} ${file}")
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${file})
    
    set(PROTOBUF_MODELS_INCLUDES "${PROTOBUF_MODELS_INCLUDES} ${PROTO_HDRS}")
    set(PROTOBUF_MODELS_SOURCES "${PROTOBUF_MODELS_SOURCES} ${PROTO_SRCS}")
    list(APPEND core_src ${PROTO_SRCS})
endforeach()
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
file(COPY scripts DESTINATION .)
find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
find_package(spdlog REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(${APP_TARGET} Eigen3::Eigen)
target_link_libraries(${APP_TARGET} ${SPDLOG_LIBRARIES})
target_link_libraries(${APP_TARGET} ${LUA_LIBRARIES})
target_link_libraries(${APP_TARGET} ${Protobuf_LIBRARIES})
target_compile_features(${APP_TARGET}
    PRIVATE
    cxx_std_17
)


