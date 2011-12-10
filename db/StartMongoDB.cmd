mongod.exe --dbpath data

rem net stop MongoDB
rem mongod --remove
rem sc delete MongoDB
rem mongod --logpath D:\dev\fugu\trunk\db\logs\logfilename.log --logappend --dbpath D:\dev\fugu\trunk\db\data --directoryperdb --install
rem net start MongoDB

if not %ERRORLEVEL% == 0 pause