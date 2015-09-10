@echo off

call env_vs.bat %1

rem --------------- Local settings -------------- 

if exist "localenv.bat" (
  echo Setting local environment from localenv.bat
  call "localenv.bat"
) else (
  echo Warning: file localenv.bat does not exist; using default environment
)

rem --------------- Configuration -------------- 

if ["%PROJECT_DIR%"] == [""] set "PROJECT_DIR=%CD%"
echo Project directory: %PROJECT_DIR%

rem --------------- Products path --------------
if ["%PRODUCTSDIR%"] == [""] set "PRODUCTSDIR=c:\products.vs2005"
echo Products directory: %PRODUCTSDIR%

rem --------------- cmake --------------
if ["%CMAKEDIR%"] == [""] set "CMAKEDIR=%PRODUCTSDIR%\cmake-2.8.7"
set PATH=%CMAKEDIR%\bin;%PATH%
echo CMAKE directory: %CMAKEDIR%

rem --------------- cppunit --------------
if ["%CPPUNITDIR%"] == [""] set "CPPUNITDIR=%PRODUCTSDIR%\cppunit-1.12.1"
set PATH=%CPPUNITDIR%\lib;%PATH%
echo CPPUNIT directory: %CPPUNITDIR%

rem --------------- qt --------------
rem if ["%QTDIR%"] == [""] set "QTDIR=%PRODUCTSDIR%\qt-4.7.1"
set "QTDIR=%PRODUCTSDIR%\qt-4.7.1"
set "CMAKE_PREFIX_PATH=%QTDIR%"
set PATH=%QTDIR%\bin;%PATH%
echo QT directory: %QTDIR%

rem --------------- doxygen --------------
if ["%DOXYGENDIR%"] == [""] set "DOXYGENDIR=%PRODUCTSDIR%\doxygen-1.8.9"
set PATH=%DOXYGENDIR%\bin;%PATH%
echo DOXYGEN directory: %DOXYGENDIR%

rem --------------- cppcheck --------------
if ["%CPPCHECKDIR%"] == [""] set "CPPCHECKDIR=%PRODUCTSDIR%\cppcheck-1.68"
set PATH=%CPPCHECKDIR%;%PATH%
echo CPPCHECK directory: %CPPCHECKDIR%

rem --------------- Examples path --------------
if ["%TEST_DATA_DIR%"] == [""] set "TEST_DATA_DIR=%PROJECT_DIR%\testdata"
echo Test data directory: %TEST_DATA_DIR%

if ["%EXAMPLES_DIR%"] == [""] set "EXAMPLES_DIR=%PROJECT_DIR%\examples"
echo Examples directory: %EXAMPLES_DIR%
