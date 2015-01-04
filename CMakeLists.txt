cmake_minimum_required(VERSION 2.8.4)
project(gooey2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_directories(/usr/local/lib)

set(SOURCE_FILES

    include/gooey/geom/Point.hpp
    include/gooey/geom/Rect.hpp
    include/gooey/geom/Size.hpp

    include/gooey/DrawingContext.hpp
    include/gooey/Event.hpp
    include/gooey/View.hpp
    include/gooey/Window.hpp
    include/gooey/WindowManager.hpp

    include/gooey/cmp/Button.hpp
    include/gooey/cmp/Label.hpp
    include/gooey/cmp/Panel.hpp
    include/gooey/cmp/SDLSurfaceView.hpp
    include/gooey/cmp/SplitView.hpp

    include/gooey/fwd.hpp
    include/gooey/gooey.hpp

    src/DrawingContext.cpp
    src/View.cpp
    src/Window.cpp
    src/WindowManager.cpp

    src/cmp/Button.cpp
    src/cmp/Label.cpp
    src/cmp/Panel.cpp
    src/cmp/SDLSurfaceView.cpp
    src/cmp/SplitView.cpp

    src/debug.cpp

    main.cpp

)

add_executable(gooey2 ${SOURCE_FILES})

target_link_libraries(gooey2 SDL2)
target_link_libraries(gooey2 SDL2_gfx)
target_link_libraries(gooey2 SDL2_image)
target_link_libraries(gooey2 SDL2_mixer)
target_link_libraries(gooey2 SDL2_ttf)
target_link_libraries(gooey2 SDL2_net)
target_link_libraries(gooey2 cairo)

include_directories(include)