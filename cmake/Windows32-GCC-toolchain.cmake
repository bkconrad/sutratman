# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

SET(CMAKE_VERBOSE_MAKEFILE ON)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH /usr/i586-mingw32msvc)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_C_COMPILER i586-mingw32msvc-gcc)
SET(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
SET(CMAKE_RC_COMPILER i586-mingw32msvc-windres)

# which compilers to use for C and C++
#SET(CMAKE_C_COMPILER i586-mingw32msvc-gcc)
#SET(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
#SET(CMAKE_RC_COMPILER i586-mingw32msvc-windres)
#SET(CMAKE_AR i586-mingw32msvc-ar)
#SET(CMAKE_LINKER i586-mingw32msvc-ld)

# cook up a dll we can actually use
SET(BUILD_SHARED_LIBS ON)

# don't use the system irrlicht
set(IRRLICHT_FOUND TRUE)
set(IRRLICHT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/irrlicht/include)
set(IRRLICHT_LIBRARY ${CMAKE_SOURCE_DIR}/lib/irrlicht/lib/Win32-gcc/libIrrlicht.a)
