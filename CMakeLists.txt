cmake_minimum_required (VERSION 3.0)

project (pokemaze VERSION 1.0.0)

LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/lib )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set (CMAKE_DEBUG_POSTFIX "_d")

find_package(OpenGL REQUIRED)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_SRC_FILES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_subdirectory(lib/consolex)

if(WIN32)
  set(COMMON_LIBS ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -lcomctl32 -lgdi32 -lopengl32 -lwinmm -pthread -lole32 -lstdc++ -lglut32 -limm32")
elseif (UNIX)
  set(COMMON_LIBS ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} rt ${CMAKE_DL_LIBS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
  set(COMMON_LIBS)
endif()

set(COMMON_HEADERS 
  lib/KHR/khrplatform.h
)

set(EXTRA_LIBS 
	consolex_src
  tinyfiledialogs
  scheduler_src
  obj_loader
)

set(COMMON_LIBS ${COMMON_LIBS} ${EXTRA_LIBS})

add_library(consolex_src
	lib/consolex/src/wniemiec/io/cpp/Consolex.cpp
	lib/consolex/src/wniemiec/io/cpp/HistoryConsolex.cpp
	lib/consolex/src/wniemiec/io/cpp/InputConsolex.cpp
	lib/consolex/src/wniemiec/io/cpp/LoggerConsolex.cpp
	lib/consolex/src/wniemiec/io/cpp/LogLevel.cpp
	lib/consolex/src/wniemiec/io/cpp/LogMessage.cpp
	lib/consolex/src/wniemiec/io/cpp/OutputConsolex.cpp
)

add_library(tinyfiledialogs
  lib/tinyfiledialogs/tinyfiledialogs.c
)

add_library(scheduler_src
  lib/scheduler/src/wniemiec/task/cpp/Scheduler.cpp
)

add_library(obj_loader
  lib/obj_loader/glad.c
  lib/obj_loader/stb_image.cpp
  lib/obj_loader/tiny_obj_loader.cpp
)

set(RUN_DIR ${PROJECT_SOURCE_DIR}/bin)

include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/lib/
	${PROJECT_SOURCE_DIR}/lib/glfw/include
	${PROJECT_SOURCE_DIR}/lib/consolex/include
	${PROJECT_SOURCE_DIR}/lib/KHR
  ${PROJECT_SOURCE_DIR}/lib/scheduler/include
)

set(SRC_FILES
  src/pokemaze/util/algebra/Matrices.cpp
  src/pokemaze/util/algebra/Bezier.cpp
  src/pokemaze/util/io/IOUtils.cpp
  src/pokemaze/App.cpp
  src/pokemaze/PokeMaze.cpp
  src/pokemaze/engine/Renderer.cpp
  src/pokemaze/engine/Engine.cpp
  src/pokemaze/controllers/ErrorController.cpp
  src/pokemaze/controllers/KeyboardController.cpp
  src/pokemaze/controllers/MouseController.cpp
  src/pokemaze/engine/player/WavPlayer.cpp
  src/pokemaze/engine/projection/OrthographicProjection.cpp
  src/pokemaze/engine/projection/PerspectiveProjection.cpp
  src/pokemaze/engine/projection/Projection.cpp
  src/pokemaze/engine/text/TextRender.cpp
  src/pokemaze/engine/Display.cpp
  src/pokemaze/models/camera/Camera.cpp
  src/pokemaze/models/camera/FreeCamera.cpp
  src/pokemaze/models/camera/FixedCamera.cpp
  src/pokemaze/models/camera/LookAtCamera.cpp
  src/pokemaze/models/BoundingBox.cpp
  src/pokemaze/models/Point.cpp
  src/pokemaze/models/Sphere.cpp
  src/pokemaze/models/SceneObject.cpp
  src/pokemaze/engine/Collisions.cpp
  src/pokemaze/levels/Level.cpp
  src/pokemaze/levels/Level1.cpp
  src/pokemaze/levels/LevelFactory.cpp
  src/pokemaze/models/characters/AshKetchum.cpp
  src/pokemaze/models/characters/Charizard.cpp
  src/pokemaze/models/characters/Pikachu.cpp
  src/pokemaze/models/objects/Pokeball.cpp
  src/pokemaze/models/objects/Tree.cpp
  src/pokemaze/models/objects/Wall.cpp
  src/pokemaze/models/scene/Floor.cpp
  src/pokemaze/models/scene/Garage.cpp
  src/pokemaze/models/scene/Sky.cpp
)

  add_executable(${PROJECT_NAME} ${COMMON_HEADERS} ${SRC_FILES})
  set_property(TARGET ${PROJECT_NAME} PROPERTY DEBUG_POSTFIX _d)

if(WIN32)
  target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS} comctl32.lib sfml-audio)
elseif(UNIX)
  target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS} sfml-audio)
endif()


ADD_CUSTOM_TARGET(clean-all
	COMMAND  rm -rf CMakeFiles; rm -rf CMakeCache.txt; rm -rf cmake_install.cmake; rm -rf bin;
)

ADD_CUSTOM_TARGET(debug ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Debug ${PROJECT_SOURCE_DIR})
ADD_CUSTOM_TARGET(release ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Release ${PROJECT_SOURCE_DIR})