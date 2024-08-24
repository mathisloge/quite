find_package(imgui CONFIG REQUIRED)


cmrc_add_resource_library(studiorc ALIAS quite::studiorc NAMESPACE studiorc
    assets/fonts/SauceCodeProNerdFont-Regular.ttf
)

add_executable(quite-studio main.cpp)
target_link_libraries(quite-studio PRIVATE
    quite::quite
    quite::logger
    quite::studiorc
    imgui::imgui
)


target_sources(quite-studio PRIVATE
    app.cpp
    app.hpp
)
add_subdirectory(logic)
add_subdirectory(windows)
