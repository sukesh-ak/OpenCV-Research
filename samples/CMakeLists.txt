
IF ( WIN32 )
	ADD_COMPILE_DEFINITIONS ( _USE_MATH_DEFINES )
	ADD_COMPILE_OPTIONS ( /wd4244 ) # conversion between types
ENDIF ()

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)

FILE ( GLOB MJPEG_APPS *.cpp)
LIST ( SORT MJPEG_APPS		)

# Make executables for each .cpp file with the same name
FOREACH ( filename IN LISTS MJPEG_APPS )
	CMAKE_PATH				( GET filename STEM stem )
	ADD_EXECUTABLE			( ${stem} ${filename} )
	TARGET_LINK_LIBRARIES	( ${stem} PRIVATE ${OpenCV_LIBS} ${OPENGL_INCLUDE_DIRS})
ENDFOREACH ()
