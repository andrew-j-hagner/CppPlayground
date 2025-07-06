cmake_minimum_required(VERSION 3.16)
project(Taggleos VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Set Qt6 to automatically run MOC when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add executable
add_executable(taggleos
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/tagmanager.cpp
    src/tagmanager.h
    src/datastore.cpp
    src/datastore.h
    src/models/tag.cpp
    src/models/tag.h
    src/models/data.cpp
    src/models/data.h
    src/widgets/tagwidget.cpp
    src/widgets/tagwidget.h
    src/widgets/searchwidget.cpp
    src/widgets/searchwidget.h
)

# Link Qt6 libraries
target_link_libraries(taggleos Qt6::Core Qt6::Widgets)

# Set output directory
set_target_properties(taggleos PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Enable warnings
if(MSVC)
    target_compile_options(taggleos PRIVATE /W4)
else()
    target_compile_options(taggleos PRIVATE -Wall -Wextra -Wpedantic)
endif()
