
echo Setting environment for the Visual Studio %1

if "%1" == "8" (

  rem -------- Visual Studio --------------------
  rem Detect Visual Studio (either commercial or Express edition)
  if "%VS80COMNTOOLS%" == "" (
      echo Could not find MS Visual Studio: variable VS80COMNTOOLS is not defined!
      exit 1
  ) else if exist "%VS80COMNTOOLS%\..\IDE\devenv.exe" (
      set MSVC_EXE="%VS80COMNTOOLS%\..\IDE\devenv.exe"
  ) else if exist "%VS80COMNTOOLS%\..\IDE\VCExpress.exe" (
      set MSVC_EXE="%VS80COMNTOOLS%\..\IDE\VCExpress.exe"
  ) else (
      echo "Could not find MS Visual Studio in %VS80COMNTOOLS%\..\IDE"
      echo Check environment variable VS80COMNTOOLS!
      exit 1
  )
  call "%VS80COMNTOOLS%..\Tools\vsvars32.bat"

) else if "%1" == "9" (

  rem -------- Visual Studio --------------------
  rem Detect Visual Studio (either commercial or Express edition)
  if "%VS90COMNTOOLS%" == "" (
      echo Could not find MS Visual Studio: variable VS90COMNTOOLS is not defined!
      exit 1
  ) else if exist "%VS90COMNTOOLS%\..\IDE\devenv.exe" (
      set MSVC_EXE="%VS90COMNTOOLS%\..\IDE\devenv.exe"
  ) else if exist "%VS90COMNTOOLS%\..\IDE\VCExpress.exe" (
      set MSVC_EXE="%VS90COMNTOOLS%\..\IDE\VCExpress.exe"
  ) else (
      echo "Could not find MS Visual Studio in %VS90COMNTOOLS%\..\IDE"
      echo Check environment variable VS90COMNTOOLS!
      exit 1
  )
  call "%VS90COMNTOOLS%..\Tools\vsvars32.bat"
)
