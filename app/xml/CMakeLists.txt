#dir: app/xml
#datte: 2014-07-18
#author: zuokongxiao
#discription: xml����

#��������
PROJECT(xml)

#CMAKE�汾
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#����û�������Ϣ
MESSAGE(STATUS "source dir: " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "binary dir: " ${PROJECT_BINARY_DIR})

#����������
IF(${TARGET_P} MATCHES "x86")
 MESSAGE(STATUS "compiler: gcc ")
 SET(CMAKE_C_COMPILER gcc)
ELSE()
 MESSAGE(STATUS "target_p: arm-linux-gnueabihf-gcc")
 SET(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
ENDIF()

#���ñ�����
#SET(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#SET(CMAKE_C_FLAGS "-lpthread")
SET(CMAKE_C_FLAGS "-g")
MESSAGE(STATUS "c flags: " ${CMAKE_C_FLAGS})

#�߳�
#FIND_PACKAGE(Threads REQUIRED)

#ʹ������ADD_SUBDIRECTORYָ������Ŀ����һ����Ŀ¼test
#ADD_SUBDIRECTORY(libxml2)

#�򹤳�����ͷ�ļ�����·��
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../lib/libxml2)

#����ǰĿ¼�е�Դ�ļ����Ƹ�ֵ������DIR_SRCS
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

#ָʾ����DIR_SRCS�е�Դ�ļ���Ҫ�����һ������Ϊtestxml�Ŀ�ִ���ļ�
ADD_EXECUTABLE(testxml ${DIR_SRCS})

#ָ����ִ���ļ���Ҫ���ӵ����ӿ�
TARGET_LINK_LIBRARIES(testxml ${PROJECT_SOURCE_DIR}/../common/libcommon.a)
TARGET_LINK_LIBRARIES(testxml ${PROJECT_SOURCE_DIR}/../lib/libxml2/libxml2.so)
#TARGET_LINK_LIBRARIES(testxml ${CMAKE_THREAD_LIBS_INIT})



