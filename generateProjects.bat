
call env.bat 8
cmake -G "Visual Studio 8 2005"
start "" %MSVC_EXE% Journal.sln
