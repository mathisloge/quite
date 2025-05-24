target_sources(
    quite-studio
    PRIVATE
        application_manager.hpp
        application_manager.cpp
        object_tree.hpp
        object_tree.cpp
        scheduler.hpp
        scheduler.cpp
)
target_include_directories(quite-studio PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
