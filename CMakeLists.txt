cmake_minimum_required (VERSION 3.8)
project ("rocket_game" VERSION 0.0.1 LANGUAGES CXX)

set(GAME_SOURCES
    src/main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(SFML_USE_STATIC_STD_LIBS "Use static libraries" ON)
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(BOX2D_BUILD_UNIT_TESTS "Build the Box2D unit tests" OFF)
option(BOX2D_BUILD_TESTBED "Build the Box2D testbed" OFF)
option(BOX2D_USER_SETTINGS "Override Box2D settings with b2UserSettings.h" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git)
FetchContent_Declare(imgui-sfml GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git GIT_TAG 2.6.x)
FetchContent_Declare(box2d GIT_REPOSITORY https://github.com/erincatto/box2d.git GIT_TAG main)
FetchContent_Declare(entt GIT_REPOSITORY https://github.com/skypjack/entt.git GIT_TAG v3.8.x)
FetchContent_Declare(ReactPhysics3D GIT_REPOSITORY https://github.com/DanielChappuis/reactphysics3d.git GIT_TAG master)
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(box2d)
FetchContent_MakeAvailable(entt)
FetchContent_MakeAvailable(ReactPhysics3D)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
FetchContent_MakeAvailable(imgui-sfml)

if(WIN32)
    set(SFML_LIBS sfml-graphics sfml-window sfml-audio sfml-network sfml-main sfml-system)
elseif(LINUX)
    set(SFML_LIBS sfml-graphics sfml-window sfml-audio sfml-network sfml-system)
endif()

add_executable(${PROJECT_NAME} ${GAME_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS} ImGui-SFML::ImGui-SFML EnTT::EnTT box2d ReactPhysics3D::reactphysics3d -static)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy Assets"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
        VERBATIM)
        
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()