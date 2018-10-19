cmake_minimum_required(VERSION 2.8)

project(RelativityPhysics)


## Qt library
#find_package(Qt5Widgets)
#find_package(Qt5OpenGL)
#set(CMAKE_AUTOMOC ON)

# OpenGL & GLEW library
set(QT_USE_QTOPENGL TRUE)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


set(SOURCE  main.cpp
            freeglut/freeglut_xinput.c
            freeglut/freeglut_window.c
            freeglut/freeglut_videoresize.c
            freeglut/freeglut_teapot.c
            freeglut/freeglut_structure.c
            freeglut/freeglut_stroke_roman.c
            freeglut/freeglut_stroke_mono_roman.c
            freeglut/freeglut_state.c
            freeglut/freeglut_spaceball.c
            freeglut/freeglut_overlay.c
            freeglut/freeglut_misc.c
            freeglut/freeglut_menu.c
            freeglut/freeglut_main.c
            freeglut/freeglut_joystick.c
            freeglut/freeglut_input_devices.c
            freeglut/freeglut_init.c
            freeglut/freeglut_glutfont_definitions.c
            freeglut/freeglut_geometry.c
            freeglut/freeglut_gamemode.c
            freeglut/freeglut_font_data.c
            freeglut/freeglut_font.c
            freeglut/freeglut_ext.c
            freeglut/freeglut_display.c
            freeglut/freeglut_cursor.c
            freeglut/freeglut_callbacks.c
            IParticle.cpp
            IParticleSystem.cpp)

set(HEADER  IRelativity.h
            IParticle.h
            IParticleSystem.h
            IMathematics.h
            IMath/IAlgebra.h
            IMath/IComplex.h
            IMath/IFunc.h
            IMath/ILine3D.h
            IMath/ILineSegment3D.h
            IMath/ILorentzVector.h
            IMath/IMaths.h
            IMath/IMatrix2x2.h
            IMath/IMatrix3x3.h
            IMath/IMatrix4x4.h
            IMath/IOctonion.h
            IMath/IPlane.h
            IMath/IQuaternion.h
            IMath/IRay.h
            IMath/IReal.h
            IMath/IScalarType.h
            IMath/ISpherical.h
            IMath/ITransform.h
            IMath/IVector.h
            IMath/IVector2D.h
            IMath/IVector3D.h
            IMath/IVector4D.h
            IMath/IVectorType.h)


add_executable(${PROJECT_NAME} ${SOURCE} ${HEADER})

#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#qt5_use_modules(RelativityPhysics Widgets OpenGL)
target_link_libraries(RelativityPhysics ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

set(OPENGL_LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

target_compile_options( RelativityPhysics PUBLIC -std=c++11 -fpermissive -w -Wall )

target_link_libraries( RelativityPhysics ${OpenCV_LIBS}  -lX11 )

