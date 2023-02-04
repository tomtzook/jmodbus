set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x64)

if("${CROSS}" STREQUAL "")
  set(CROSS x86_64-w64-mingw32)
endif()

set(CMAKE_C_COMPILER ${CROSS}-gcc)
set(CMAKE_CXX_COMPILER ${CROSS}-g++)
set(CMAKE_AR ${CROSS}-ar CACHE FILEPATH Archiver)
set(CMAKE_RANLIB ${CROSS}-ranlib CACHE FILEPATH Indexer)

set(CMAKE_FIND_ROOT_PATH
  /usr/${CROSS})

# modify default behavior of FIND_XXX() commands to
# search for headers/libs in the target environment and
# search for programs in the build host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".dll.a" ".lib" ".a")

# Fix Java Includes
set(JAVA_HOME $ENV{JAVA_HOME})

set(JAVA_AWT_LIBRARY ${JAVA_HOME}/lib/libjawt.so)
set(JAVA_JVM_LIBRARY ${JAVA_HOME}/lib/server/libjvm.so)
set(JAVA_INCLUDE_PATH ${JAVA_HOME}/include)
set(JAVA_INCLUDE_PATH2 ${JAVA_HOME}/include/linux)
set(JAVA_AWT_INCLUDE_PATH ${JAVA_HOME}/include)
