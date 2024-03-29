# Gnocchi
A Notification Oriented Programming Language  focused on flexibility, expression, and parallelism.

code for the flex/bison part based on code available on https://github.com/ezaquarii/bison-flex-cpp-example

# Compilation

This project is based on Cmake. Its only dependencies are flex and bison. On linux, this is usually easy to install.

For Windows, the easiest way is to use Chocolatey, a package manager for Windows. You can follow the official [tutorial]{https://chocolatey.org/install#individual},
but, in essence, open a powershell as administrator and run the following command:

    Get-ExecutionPolicy

if it returns `Restricted`, run `Set-ExecutionPolicy AllSigned` or `Set-ExecutionPolicy Bypass -Scope Process`. Then run:

    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

this takes a few seconds. run `choco` to make sure everything is fine. The next step is actually installing flex and bison
from [this package]{https://community.chocolatey.org/packages/winflexbison3#install}. In order to install, run

    choco install winflexbison3

to check if it worked, try running `win_bison`. The response should be something like `win_bison.exe: missing operand `.
If everything is fine, reboot windows and then cmake should be able to find flex and bison.