# Get source and destination paths
$extensionsPath = "$env:USERPROFILE\.vscode\extensions"
$backupPath = "D:\VSCodeExtensions_Backup"

Write-Host "Extensions Path: $extensionsPath"
Write-Host "Backup location: $backupPath"

# Check if backup directory exists and is not empty
if (Test-Path $backupPath) {
    $existingFiles = Get-ChildItem -Path $backupPath
    if ($existingFiles.Count -gt 0) {
        Write-Host "Error: Backup directory '$backupPath' already exists and is not empty."
        Write-Host "Please manually clear the directory first."
        exit
    }
}

# Create backup directory if it doesn't exist
if (!(Test-Path $backupPath)) {
    New-Item -Path $backupPath -ItemType Directory | Out-Null
}

# Get all subdirectories
$extensions = Get-ChildItem -Path $extensionsPath -Directory

# Show total count
Write-Host "Found $($extensions.Count) extensions to backup..."
Write-Host "Starting backup process..."

# Copy each extension one by one
foreach ($extension in $extensions) {
    Write-Host "Copying extension: $($extension.Name)..."
    Copy-Item -Path $extension.FullName -Destination "$backupPath\$($extension.Name)" -Recurse -Force
}

Write-Host "Backup completed successfully!"