# TTFS.ps1 — Time Travelling File System (Windows PowerShell)

# Clear screen
Clear-Host

# Colors are handled via Write-Host -ForegroundColor
function Color([string]$text, [string]$color) { Write-Host $text -ForegroundColor $color }

# Header
Color "╔════════════════════════════════════════════════════════════╗" Blue
Color "║                                                            ║" Blue
Color "║             Time Travelling File System (TTFS)             ║" Blue
Color "║                                                            ║" Blue
Color "╠════════════════════════════════════════════════════════════╣" Blue
Write-Host ("║ Author: Naman Goyal                    Entry: 2024EE30913  ║")
Write-Host ("║ Course: COL106 - Data Structures       Semester: Fall 2025 ║")
Color "╚════════════════════════════════════════════════════════════╝" Blue
Write-Host ""

function Compile {
    Color "Compiling Time Travelling File System..." Yellow
    New-Item -ItemType Directory -Path build -Force | Out-Null

    $gpp = Get-Command g++ -ErrorAction SilentlyContinue
    if (-not $gpp) {
        Color "Error: g++ not found in PATH. Please install MinGW-w64/MSYS2 and ensure g++ is available." Red
        return $false
    }

    & g++ -std=c++17 main.cpp -o build\tfs.exe -Wall -Wextra -pedantic -O2
    if ($LASTEXITCODE -eq 0) {
        Color "Compilation successful!" Green
        return $true
    } else {
        Color "Compilation failed!" Red
        return $false
    }
}

function Run {
    if (Test-Path -Path build\tfs.exe -PathType Leaf) {
        Color "Running TTFS..." Yellow
        Write-Host ""
        & .\build\tfs.exe
        return $true
    } else {
        Color "Error: Executable not found. Please compile first." Red
        return $false
    }
}

function Run-WithIO {
    if (-not (Test-Path -Path build\tfs.exe -PathType Leaf)) {
        Color "Error: Executable not found. Please compile first." Red
        return $false
    }

    Color "Running TTFS..." Yellow
    Write-Host ""

    $in = Read-Host 'Enter input filename [input.txt]'
    if ([string]::IsNullOrWhiteSpace($in)) { $in = 'input.txt' }
    $out = Read-Host 'Enter output filename [output.txt]'
    if ([string]::IsNullOrWhiteSpace($out)) { $out = 'output.txt' }

    if (-not (Test-Path -Path $in -PathType Leaf)) {
        Color "Error: '$in' not found. Please create it or choose another file." Red
        return $false
    }

    $inFull  = (Resolve-Path -LiteralPath $in).Path
    $outFull = [System.IO.Path]::GetFullPath($out)

    Start-Process -FilePath (Resolve-Path .\build\tfs.exe).Path `
        -RedirectStandardInput  $inFull `
        -RedirectStandardOutput $outFull `
        -NoNewWindow -Wait

    Color "Output written to $out" Green
    return $true
}

while ($true) {
    Write-Host ""
    Color "Please select an option:" Magenta
    Write-Host "1) Compile and Run"
    Write-Host "2) Compile and Run with custom I/O (defaults: input.txt -> output.txt)"
    Write-Host "3) Compile Only"
    Write-Host "4) Run Existing Version"
    Write-Host "5) Read Documentation"
    Write-Host "6) Exit"
    Write-Host ""
    $choice = Read-Host "Enter your choice (1-6)"
    Write-Host ""

    switch ($choice) {
        '1' { if (Compile) { Run | Out-Null } }
        '2' { if (Compile) { Run-WithIO | Out-Null } }
        '3' { Compile | Out-Null }
        '4' {
            Color "Available versions:" Yellow
            if (Test-Path -Path .\Version_History\) {
                Get-ChildItem -Path .\Version_History\ -File | ForEach-Object { $_.Name } 
                Write-Host ""
                $version = Read-Host "Enter version name to run"
                if ([string]::IsNullOrWhiteSpace($version)) {
                    Color "Error: No version name provided." Red
                } else {
                    $verPath = Join-Path .\Version_History $version
                    if (Test-Path -Path $verPath -PathType Leaf) {
                        Color "Running version: $version" Green
                        Start-Process -FilePath (Resolve-Path -LiteralPath $verPath).Path -NoNewWindow -Wait
                    } else {
                        Color "Error: Version not found." Red
                    }
                }
            } else {
                Color "Error: Version_History folder not found." Red
            }
        }
        '5' {
            $doc = Join-Path (Get-Location) 'README.md'
            if (Test-Path -Path $doc -PathType Leaf) {
                Invoke-Item -LiteralPath $doc
            } else {
                Color "Error: README.md not found." Red
            }
        }
        '6' {
            Color "Thank you for using TTFS!" Green
            break
        }
        Default { Color "Invalid option. Please try again." Red }
    }
}
