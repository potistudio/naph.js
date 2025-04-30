cmake_minimum_required(VERSION 4.0)


project (naph CXX)
set(CMAKE_CXX_STANDARD 17)
message (project name is set as: ${PROJECT_NAME})

set (PROJECT_VERSION "0.1")
message (project version is set as: &{PROJECT_VERSION})

add_compile_definitions(
	JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED
	JUCE_PLUGINHOST_VST3
	JUCE_STANDALONE_APPLICATION
	JUCE_WINDOWS
)


################ Compiling ################
file(GLOB SOURCE_FILES "src/*.cc")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
###########################################


################ Including ################
# Include N-API headers
target_include_directories(${PROJECT_NAME} PRIVATE "node_modules/node-addon-api")

# Include cmake-js headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})

# Include JUCE headers
target_include_directories(${PROJECT_NAME} PRIVATE "lib/thirdparty/juce/modules")
target_include_directories(${PROJECT_NAME} PRIVATE "lib/thirdparty/juce/modules/juce_audio_processors/format_types/VST3_SDK")
###########################################


################ Linking ##################
# Link CMake.js library (x64)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB})

# Link JUCE library (x64)
target_link_libraries(${PROJECT_NAME} PRIVATE "../lib/thirdparty/juce")
###########################################
