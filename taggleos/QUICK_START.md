# Quick Start Guide for Taggleos GUI

## Prerequisites Check

Before building, ensure you have:
- Qt6 installed (with Widgets and Core modules)
- CMake 3.16 or later
- A C++20 compatible compiler

## Build Instructions

### Option 1: Using the Build Script (Recommended)

```powershell
cd taggleos
./build.ps1
```

### Option 2: Manual Build

```powershell
cd taggleos
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./bin/taggleos.exe
```

## If You Don't Have Qt6

Install Qt6 using one of these methods:

### Method 1: Official Qt Installer
1. Download from: https://www.qt.io/download
2. Install Qt6 with Qt Creator
3. Make sure Qt6 is in your PATH

### Method 2: vcpkg Package Manager
```powershell
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg install qt6[core,widgets]
```

Then when building, specify the vcpkg toolchain:
```powershell
cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```

## Running the Application

After a successful build, the executable will be in `build/bin/taggleos.exe`

The application provides:
- A tag management panel on the left
- A search interface on the right
- File menu for data operations
- Context menus for tag operations

## Troubleshooting

If you get CMake errors about Qt6 not being found:

1. Make sure Qt6 is installed
2. Set the CMAKE_PREFIX_PATH to your Qt6 installation:
   ```powershell
   cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.5.0\msvc2019_64"
   ```

For compiler errors, ensure you're using a C++20 compatible compiler (GCC 10+, Clang 12+, or Visual Studio 2019+).
