cmake_minimum_required (VERSION 2.6)

#name of the project
PROJECT(i2p_emotion_engine)

#setup where are the modules: for findKinectSDK.cmake
set(CMAKE_MODULE_PATH $ENV{I2P_MODULE}/i2pCmake)

#dependencies for this project
#i2p: thrift boost libevent
#to be done before pkg search
include($ENV{I2P_MODULE}/i2pCmake/i2p.cmake)




if (WIN32)
    set(BOOST_ROOT "$ENV{IMI_LIBRARIES}/boost_1_49_0")
    set(GLUT_ROOT_PATH $ENV{IMI_LIBRARIES}/freeglut)
endif()

FIND_PACKAGE(Thrift REQUIRED)
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(GLUT)
FIND_PACKAGE(GLUI)


#####################################################################
# Generate Thrift stubs
#####################################################################
include_directories($ENV{I2P_MODULE}/i2pThrift/gen-cpp)
GENERATE_STUBS(I2P.thrift cpp)
GENERATE_STUBS(Inputs.thrift cpp)
GENERATE_STUBS(Control.thrift cpp)
#for the test server
GENERATE_STUBS(I2P.thrift py)
GENERATE_STUBS(Inputs.thrift py)
GENERATE_STUBS(Feedback.thrift py)
GENERATE_STUBS(VHSimpleService.thrift py)
GENERATE_STUBS(I2P.thrift java)
GENERATE_STUBS(Inputs.thrift java)
GENERATE_STUBS(I2P.thrift csharp)
GENERATE_STUBS(Inputs.thrift csharp)


INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLUI_INCLUDE_DIR})
INCLUDE_DIRECTORIES($ENV{I2P_MODULE}/i2pThrift/tools/cpp)
INCLUDE_DIRECTORIES($ENV{I2P_MODULE}/i2pThrift/gen-cpp)

INCLUDE_DIRECTORIES(${I2P_INCLUDES})
INCLUDE_DIRECTORIES(${THRIFT_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

set( SRCS
    ./src/AffectiveSystem.cpp
    ./src/axis.cpp
    ./src/BasicMath.cpp
    ./src/collision_detection.cpp
    ./src/control_interface.cpp
    ./src/Probability.cpp
	./src/Datastructure.cpp
	./src/global_declaration.cpp
)

set( HDRS
    ./src/AffectiveSystem.h
    ./src/axis.h
    ./src/BasicMath.h
    ./src/collision_detection.h
    ./src/control_interface.h
    ./src/Datastructure.h
    ./src/Probability.h
	./src/global_declaration.h
	./src/SpeechInput_server.hpp
	./src/InitMoodServer.hpp
)

SOURCE_GROUP( Headers FILES ${HDRS})
SOURCE_GROUP( Sources FILES ${SRCS})

file(TO_CMAKE_PATH "$ENV{I2P_MODULE}/i2pThrift" I2P_MODULE_PATH)

set( I2P_SRCS
	${I2P_MODULE_PATH}/gen-cpp/ObjectDetectionService.h
	${I2P_MODULE_PATH}/gen-cpp/ObjectDetectionService.cpp
    ${I2P_MODULE_PATH}/gen-cpp/TrackingService.cpp
    ${I2P_MODULE_PATH}/gen-cpp/TrackingService.h
    ${I2P_MODULE_PATH}/gen-cpp/I2P_constants.cpp
    ${I2P_MODULE_PATH}/gen-cpp/I2P_constants.h
    ${I2P_MODULE_PATH}/gen-cpp/I2P_types.cpp
    ${I2P_MODULE_PATH}/gen-cpp/I2P_types.h
    ${I2P_MODULE_PATH}/gen-cpp/Inputs_constants.cpp
    ${I2P_MODULE_PATH}/gen-cpp/Inputs_constants.h
    ${I2P_MODULE_PATH}/gen-cpp/Inputs_types.cpp
    ${I2P_MODULE_PATH}/gen-cpp/Inputs_types.h
    ${I2P_MODULE_PATH}/tools/cpp/ProtectedClient.h
	${I2P_MODULE_PATH}/gen-cpp/AgentControl.h
	${I2P_MODULE_PATH}/gen-cpp/AgentControl.cpp
)




SOURCE_GROUP( i2p FILES ${I2P_SRCS})

####################################################################
# Common Tools from I2P
set( COMMON_HDRS
    ${I2P_MODULE_PATH}/tools/cpp/ThriftTools.hpp
)
set( COMMON_SRCS
    ${I2P_MODULE_PATH}/tools/cpp/ThriftTools.cpp
)

if(WIN32)
    set( COMMON_SRCS ${COMMON_SRCS} 
        ${I2P_MODULE_PATH}/tools/cpp/ThriftTools_Win32.cpp ) 
else(WIN32)
    set( COMMON_SRCS ${COMMON_SRCS} 
        ${I2P_MODULE_PATH}/tools/cpp/ThriftTools_Unix.cpp ) 
endif(WIN32)
SOURCE_GROUP( I2PCommonSources FILES ${COMMON_SRCS})
set(HDRS ${HDRS} ${COMMON_HDRS})
set(SRCS ${SRCS} ${COMMON_SRCS} ${I2P_SRCS})



IF(WIN32)
ADD_EXECUTABLE(i2p_emotion_engine
    ${HDRS} ${SRCS} 
)
ENDIF(WIN32)

IF(WIN32)
  TARGET_LINK_LIBRARIES(i2p_emotion_engine
     debug ${THRIFT_LIBRARY_DEBUG}
     optimized ${THRIFT_LIBRARY_RELEASE}
    ${GLUT_LIBRARY}
    debug ${GLUI_LIBRARY_DEBUG}
    optimized ${GLUI_LIBRARY_RELEASE}
    )
ENDIF(WIN32)

