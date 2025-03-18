

# Get the current user's local application data path
$localAppData = [System.Environment]::GetFolderPath('LocalApplicationData')

# Define Cursor installation path
$cursorPath = Join-Path -Path $localAppData -ChildPath "Programs\cursor\Cursor.exe"

# Registry path (using HKLM instead of HKCR)
# Add folder background right mouse menu of " Open with Cursor"
$regPath = "HKLM:\SOFTWARE\Classes\Directory\Background\shell\OpenWithCursor"
# Add folder right mouse menu of " Open with Cursor"
$regPath = "HKLM:\SOFTWARE\Classes\Folder\shell\OpenWithCursor"

try {
    # Create registry key
    if (!(Test-Path $regPath)) {
        New-Item -Path $regPath -Force -ErrorAction Stop | Out-Null
    }
    Set-ItemProperty -Path $regPath -Name "(default)" -Value "Open with Cursor" -ErrorAction Stop

    # Create command key
    $commandPath = Join-Path -Path $regPath -ChildPath "command"
    if (!(Test-Path $commandPath)) {
        New-Item -Path $commandPath -Force -ErrorAction Stop | Out-Null
    }
    Set-ItemProperty -Path $commandPath -Name "(default)" -Value "`"$cursorPath`" `"%V`"" -ErrorAction Stop

    Write-Host "Right-click menu item 'Open with Cursor' has been successfully added."
    Write-Host "Path: $cursorPath"
}
catch {
    Write-Host "Error: This script requires administrator privileges to modify the registry."
    Write-Host "Please run PowerShell as administrator and try again."
    Write-Host "Error details: $_"
}
