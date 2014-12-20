cmake_minimum_required(VERSION 2.8.4)
project(gooey2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_directories(/usr/local/lib)

set(SOURCE_FILES

    include/gooey/geom/Point.hpp
    include/gooey/geom/Rect.hpp
    include/gooey/geom/Size.hpp
    include/gooey/Event.hpp
    include/gooey/Window.hpp
    include/gooey/WindowManager.hpp
    include/gooey/gooey.hpp

    src/Window.cpp
    src/WindowManager.cpp

    main.cpp

)

add_executable(gooey2 ${SOURCE_FILES})

target_link_libraries(gooey2 SDL2)
target_link_libraries(gooey2 SDL2_gfx)
target_link_libraries(gooey2 SDL2_image)
target_link_libraries(gooey2 SDL2_mixer)
target_link_libraries(gooey2 SDL2_ttf)
target_link_libraries(gooey2 SDL2_net)

include_directories(include)