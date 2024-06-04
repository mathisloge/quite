find_package(imgui CONFIG REQUIRED)

add_executable(quite-studio main.cpp)
target_link_libraries(quite-studio PRIVATE 
    quite::quite
    quite::logger
    imgui::imgui
)


target_sources(quite-studio PRIVATE
    app.cpp 
    app.hpp
)
add_subdirectory(windows)
