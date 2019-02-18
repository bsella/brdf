cmake_minimum_required(VERSION 3.5)

set(APPLICATION brdfExp3000)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -fopenmp")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

FILE(GLOB HEADERS
    *.h
)

FILE(GLOB SOURCES
    Quad.cpp
    Sphere.cpp
    BRDFAnalytic.cpp
    BRDFBase.cpp
    BRDFImageSlice.cpp
    BRDFMeasuredAniso.cpp
    BRDFMeasuredMERL.cpp
    ColorVarWidget.cpp
    FloatVarWidget.cpp
    DGLFrameBuffer.cpp
    DGLShader.cpp
    IBLWidget.cpp
    IBLWindow.cpp
    ImageSliceWidget.cpp
    ImageSliceWindow.cpp
    LitSphereWindow.cpp
    main.cpp
    glerror.cpp
    MainWindow.cpp
    ViewerWindow.cpp
    ParameterGroupWidget.cpp
    ParameterWindow.cpp
    SharedContextGLWidget.cpp
    ShowingDockWidget.cpp
    PlotCartesianWindow.cpp
    PlotCartesianWidget.cpp
    PlotPolarWidget.cpp
    Plot3DWidget.cpp
    LitSphereWidget.cpp
    SimpleModel.cpp
    Paths.cpp
    ptex/PtexReader.cpp
    ptex/PtexUtils.cpp
    ptex/PtexCache.cpp
    ptex/PtexHalf.cpp
    ChefDevr/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../BRDF3000/src/Parametrisation/*.cpp
)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

#target_compile_definitions(PTEX_STATIC NOMINMAX)

include_directories(
   ${Qt5Widgets_INCLUDES}
   ${Qt5OpenGL_INCLUDES}
		${CMAKE_CURRENT_SOURCE_DIR}/../../BRDF3000/src/Parametrisation/
   ${CMAKE_CURRENT_SOURCE_DIR}/../../BRDF3000/lib/Eigen/
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${APPLICATION}
	${SOURCES}
	${HEADERS}
)

qt5_use_modules(${APPLICATION} Widgets OpenGL)

set(EXT_LIBS ${QT_LIBRARIES} ${OPENGL_LIBRARIES} "-lz")
target_link_libraries(${APPLICATION} ${EXT_LIBS})
