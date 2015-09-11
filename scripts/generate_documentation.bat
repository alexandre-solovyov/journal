
cd ..
call env.bat 8
cd doc

echo Removing directories...
rmdir html /S /Q 

echo Generating documentation...
doxygen.exe journal.doxygen 2> ../scripts/generate_documentation.log

cd ../scripts
