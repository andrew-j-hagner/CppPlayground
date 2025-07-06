# Build and run script for Windows PowerShell

# Create build directory
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Name "build"
}

# Navigate to build directory
Set-Location "build"

# Run CMake to configure the project
cmake .. -G "MinGW Makefiles"

# Build the project
cmake --build .

# Run the executable if build was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful! Running Taggleos..."
    & "./bin/taggleos.exe"
} else {
    Write-Host "Build failed with exit code: $LASTEXITCODE"
}

# Return to parent directory
Set-Location ".."
