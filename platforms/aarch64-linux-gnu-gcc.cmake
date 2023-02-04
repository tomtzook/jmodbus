set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++")
set(CMAKE_AR "aarch64-linux-gnu-ar" CACHE FILEPATH Archiver)
set(CMAKE_RANLIB "aarch64-linux-gnu-ranlib" CACHE FILEPATH Indexer)

set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "-march=armv8-a")
set(CMAKE_CXX_FLAGS "-march=armv8-a")

# cache flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "c flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "c++ flags")

# Fix Java Includes
set(JAVA_HOME $ENV{JAVA_HOME})

set(JAVA_AWT_LIBRARY ${JAVA_HOME}/lib/libjawt.so)
set(JAVA_JVM_LIBRARY ${JAVA_HOME}/lib/server/libjvm.so)
set(JAVA_INCLUDE_PATH ${JAVA_HOME}/include)
set(JAVA_INCLUDE_PATH2 ${JAVA_HOME}/include/linux)
set(JAVA_AWT_INCLUDE_PATH ${JAVA_HOME}/include)
