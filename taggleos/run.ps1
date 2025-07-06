# Taggleos Launcher Script
# This script sets up the environment and runs the Taggleos application

# Set up Qt6 environment
$env:PATH += ";C:\Qt\6.9.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;C:\Qt\Tools\CMake_64\bin;C:\Qt\Tools\Ninja"

# Check if the application exists
if (Test-Path "build\bin\taggleos.exe") {
    Write-Host "Starting Taggleos GUI Application..."
    Start-Process -FilePath "build\bin\taggleos.exe"
    Write-Host "Taggleos has been launched!"
} else {
    Write-Host "Taggleos executable not found. Please build the project first."
    Write-Host "Run: ./build.ps1"
}
