# Taggleos - Tag-Based Storage GUI Application

A C++ GUI application for managing and searching data using a tag-based storage system.

## Features

- **Tag Management**: Create, edit, and organize tags in a hierarchical structure
- **Data Storage**: Store and retrieve data with associated tags
- **Search Functionality**: Search data by tags or content
- **Modern GUI**: Built with Qt6 for a responsive user interface
- **Cross-Platform**: Runs on Windows, macOS, and Linux

## Prerequisites

To build and run this application, you need:

1. **Qt6**: Install Qt6 with the following components:
   - Qt6 Core
   - Qt6 Widgets
   - Qt6 CMake integration

2. **CMake**: Version 3.16 or later

3. **C++ Compiler**: Supporting C++20 standard
   - Visual Studio 2019/2022 (Windows)
   - GCC 10+ (Linux/MinGW)
   - Clang 12+ (macOS)

### Installing Qt6 on Windows

1. Download Qt6 from [https://www.qt.io/download](https://www.qt.io/download)
2. Install Qt6 with Qt Creator
3. Make sure to add Qt6 to your PATH environment variable

### Installing with vcpkg (Alternative)

```powershell
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat

# Install Qt6
./vcpkg install qt6[core,widgets]
```

## Building the Application

### Using PowerShell (Windows)

```powershell
# Navigate to the taggleos directory
cd taggleos

# Run the build script
./build.ps1
```

### Manual Build Steps

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "MinGW Makefiles"  # On Windows with MinGW
# or
cmake .. -G "Visual Studio 17 2022"  # On Windows with Visual Studio
# or
cmake ..  # On Linux/macOS

# Build
cmake --build .

# Run
./bin/taggleos  # Linux/macOS
./bin/taggleos.exe  # Windows
```

## Architecture

The application follows a modular architecture:

- **Core Models**: `Tag` and `Data` classes for data representation
- **Tag Manager**: Central management system for tags and data
- **Data Store**: Low-level storage backend
- **GUI Widgets**: Reusable UI components
- **Main Window**: Application orchestration

## Usage

1. **Adding Tags**: Use the Tag Widget to create and organize tags
2. **Searching Data**: Use the Search Widget to find data by tags or content
3. **Managing Data**: Save and load data with associated tags

## Project Structure

```
taggleos/
├── CMakeLists.txt          # Build configuration
├── build.ps1               # Build script for Windows
├── README.md               # This file
└── src/
    ├── main.cpp            # Application entry point
    ├── mainwindow.h/cpp    # Main application window
    ├── tagmanager.h/cpp    # Core tag management
    ├── datastore.h/cpp     # Data storage backend
    ├── models/             # Data models
    │   ├── tag.h/cpp       # Tag model
    │   └── data.h/cpp      # Data model
    └── widgets/            # UI components
        ├── tagwidget.h/cpp     # Tag management widget
        └── searchwidget.h/cpp  # Search interface widget
```

## Development

### Adding New Features

1. **Models**: Add new data models in `src/models/`
2. **Widgets**: Create new UI components in `src/widgets/`
3. **Core Logic**: Extend `TagManager` for new functionality

### Code Style

- Use C++20 features where appropriate
- Follow RAII principles
- Use smart pointers for memory management
- Employ the PIMPL idiom for implementation hiding

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## License

This project is open source and available under the [MIT License](LICENSE).

## Troubleshooting

### Common Issues

1. **Qt6 not found**: Ensure Qt6 is installed and in your PATH
2. **CMake errors**: Check that CMake can find Qt6 by setting `CMAKE_PREFIX_PATH`
3. **Build errors**: Verify you have a C++20 compatible compiler

### Setting Qt6 Path

If CMake cannot find Qt6, set the path explicitly:

```bash
# Windows
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.5.0\msvc2019_64"

# Linux/macOS
cmake .. -DCMAKE_PREFIX_PATH="/opt/Qt/6.5.0/gcc_64"
```
