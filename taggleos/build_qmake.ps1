# Build script using qmake (Qt's build system)

# Create build directories
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Name "build"
}
if (-not (Test-Path "bin")) {
    New-Item -ItemType Directory -Name "bin"
}

Write-Host "Building Taggleos with qmake..."

# Generate Makefile from .pro file
qmake taggleos.pro

# Check if qmake succeeded
if ($LASTEXITCODE -ne 0) {
    Write-Host "qmake failed. Please ensure Qt6 is installed and in PATH."
    Write-Host "Try adding Qt6 to PATH:"
    Write-Host '$env:PATH += ";C:\Qt\6.5.0\mingw_64\bin"'
    Write-Host '$env:PATH += ";C:\Qt\Tools\mingw1120_64\bin"'
    exit 1
}

# Build the project
if (Test-Path "Makefile") {
    mingw32-make
} elseif (Test-Path "Makefile.Debug") {
    mingw32-make -f Makefile.Debug
} else {
    Write-Host "No Makefile found. qmake might have failed."
    exit 1
}

# Check if build succeeded
if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful!"
    
    # Try to run the executable
    if (Test-Path "bin\taggleos.exe") {
        Write-Host "Running Taggleos..."
        & "bin\taggleos.exe"
    } elseif (Test-Path "bin\taggleos_debug.exe") {
        Write-Host "Running Taggleos (debug)..."
        & "bin\taggleos_debug.exe"
    } else {
        Write-Host "Executable not found in bin directory."
        Get-ChildItem -Recurse -Name "*.exe" | ForEach-Object {
            Write-Host "Found executable: $_"
        }
    }
} else {
    Write-Host "Build failed with exit code: $LASTEXITCODE"
    Write-Host "Please check the error messages above."
}
