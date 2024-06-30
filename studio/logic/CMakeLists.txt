target_sources(quite-studio PRIVATE 
    application_manager.hpp 
    application_manager.cpp
    scheduler.hpp
    scheduler.cpp
)
target_include_directories(quite-studio PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
