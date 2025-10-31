cmake_minimum_required(VERSION 2.8)

# Project Name
PROJECT(engine)

if (NOT APPLE)
	if (WIN32)
		set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
		include_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
		link_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
	else(WIN32)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(WIN32)
endif(NOT APPLE)

if (NOT WIN32)
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	find_package(DevIL REQUIRED)
	link_libraries(${IL_LIBRARIES} )
	include_directories(ยง{IL_INCLUDE_DIR})
endif(NOT WIN32)	
	
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

add_executable(${PROJECT_NAME} src/main.cpp src/parser.cpp include/parser.hpp src/xml_data.cpp include/xml_data.hpp src/point.cpp include/point.hpp src/tinyxml2.cpp include/tinyxml2.hpp src/cam_settings.cpp include/cam_settings.hpp src/group.cpp include/group.hpp src/rotate.cpp include/rotate.hpp src/scale.cpp include/scale.hpp src/translate.cpp include/translate.hpp src/color.cpp include/color.hpp src/VBO.cpp include/VBO.hpp src/model.cpp include/model.hpp include/light.hpp src/light_directional.cpp include/light_directional.hpp src/light_point.cpp include/light_point.hpp src/light_spotlight.cpp include/light_spotlight)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glut32 glew32 DevIL)
	file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY ${TOOLKITS_FOLDER}/devil/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR})
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else(WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif (WIN32)