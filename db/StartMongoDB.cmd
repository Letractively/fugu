mongod.exe --dbpath data

rem mongod --remove
rem mongod --install --logpath mongodb.log --logappend --dbpath data

if not %ERRORLEVEL% == 0 pause