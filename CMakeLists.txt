cmake_minimum_required(VERSION 3.26)
project(SuperVAL)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
  set(SFML_DIR "C:/Program Files/SFML/lib/cmake/SFML")
  set(SFML_STATIC_LIBRARIES TRUE)
  add_compile_options(
    $<$<CONFIG:>:/MT> #---------|
    $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
    $<$<CONFIG:Release>:/MT> #--|
  )
endif()

find_package(SFML 2.6.1 COMPONENTS window system graphics REQUIRED)
link_libraries(sfml-graphics sfml-window)

add_executable(SuperVAL
        main.cpp
        Rame.cpp
        Station.cpp
        function.cpp
)
