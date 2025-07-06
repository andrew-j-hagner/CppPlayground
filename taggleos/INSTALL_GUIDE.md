# Installation and Build Guide for Taggleos

## Required Tools Installation

To build the Taggleos GUI application, you need to install the following tools:

### 1. Install Qt6

**Option A: Qt Online Installer (Recommended)**
1. Download Qt Online Installer from: https://www.qt.io/download-open-source
2. Run the installer and select:
   - Qt 6.5.0 or later
   - Qt Creator (IDE)
   - MinGW 11.2.0 64-bit (compiler)
   - CMake
   - Ninja

**Option B: Qt Maintenance Tool (if Qt is already installed)**
1. Find "Qt Maintenance Tool" in your Start Menu
2. Add missing components: Qt 6.x, MinGW compiler, CMake

### 2. Install Visual Studio Build Tools (Alternative)

If you prefer using Visual Studio:
1. Download "Build Tools for Visual Studio 2022" from Microsoft
2. Install with C++ build tools workload

### 3. Install CMake Separately (if not included with Qt)

1. Download from: https://cmake.org/download/
2. Add to PATH during installation

## Build Instructions

### After Installing Qt6:

1. **Open Qt Creator** or **Developer Command Prompt**

2. **Set Environment Variables:**
   ```powershell
   # Add Qt6 to PATH (adjust path to your Qt installation)
   $env:PATH += ";C:\Qt\6.5.0\mingw_64\bin"
   $env:PATH += ";C:\Qt\Tools\mingw1120_64\bin"
   $env:PATH += ";C:\Qt\Tools\CMake_64\bin"
   ```

3. **Navigate to project and build:**
   ```powershell
   cd "c:\Users\Andrew Hagner\Desktop\Repositories\C++\cpp-console-app\taggleos"
   ./build.ps1
   ```

### Alternative: Using Qt Creator IDE

1. Open Qt Creator
2. Open Project: Select the `CMakeLists.txt` file in the taggleos directory
3. Configure the project with Qt6 kit
4. Build and run from Qt Creator

### Alternative: Manual Build with qmake

If CMake is not available, I can create a `.pro` file for qmake:

```powershell
# After Qt6 is installed and in PATH
cd taggleos
qmake -project
qmake
make  # or nmake on Windows
```

## Quick Test

After installing Qt6, test if the tools are available:

```powershell
cmake --version
qmake --version
g++ --version  # or mingw32-g++.exe --version
```

If all commands work, then run:
```powershell
cd taggleos
./build.ps1
```

## Troubleshooting

**"cmake not found"**: Install CMake or add Qt's CMake to PATH
**"g++ not found"**: Install MinGW compiler or add Qt's MinGW to PATH
**"Qt6 not found"**: Set CMAKE_PREFIX_PATH to your Qt6 installation

Would you like me to create a qmake-based build as an alternative to CMake?
