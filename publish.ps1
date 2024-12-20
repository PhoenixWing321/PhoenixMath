# check if my.config exists  
if (-not (Test-Path "my.config")) {
    Write-Host "my.config is not found!"
    exit 1
}

# Read configuration file
$config = Get-Content "my.config" | Where-Object { $_ -notmatch '^\s*#' -and $_ -notmatch '^\s*$' } | 
ConvertFrom-StringData

# Get paths from config
$outputDir = $config.ROOT_DIR_EXPORT_LIB
$buildDir = $config.ROOT_DIR_BUILD

# Copy files
Write-Host "Copying Debug lib: $buildDir\math\Debug\PhoenixMath.lib -> $outputDir\Debug\"   
Copy-Item -Path "$buildDir\math\Debug\PhoenixMath.lib" -Destination "$outputDir\Debug\" -Force

Write-Host "Copying Release lib: $buildDir\math\Release\PhoenixMath.lib -> $outputDir\bin\"   
Copy-Item -Path "$buildDir\math\Release\PhoenixMath.lib" -Destination "$outputDir\bin\" -Force

Write-Host "Export completed!"
