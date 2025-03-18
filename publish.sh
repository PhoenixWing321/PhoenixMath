#!/bin/bash

# check if my.config exists
if [ ! -f "my.config" ]; then
    echo "my.config is not found!"
    exit 1
fi

# Read configuration file (ignoring comments and empty lines)
eval "$(grep -v '^\s*#' my.config | grep -v '^\s*$')"

# Get paths from config
outputDir=$ROOT_DIR_EXPORT_LIB
buildDir=$ROOT_DIR_BUILD

# Copy files
echo "Copying Debug lib: $buildDir/math/libPhoenixMath.a -> $outputDir/debug/"
mkdir -p "$outputDir/debug"
cp "$buildDir/math/libPhoenixMath.a" "$outputDir/debug/"

echo "Copying Release lib: $buildDir/math/libPhoenixMath.a -> $outputDir/bin/"
mkdir -p "$outputDir/bin"
cp "$buildDir/math/libPhoenixMath.a" "$outputDir/bin/"

echo "Export completed!" 