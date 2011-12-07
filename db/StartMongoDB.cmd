rem mongod.exe --dbpath data

net stop MongoDB
mongod --remove
sc delete MongoDB
mongod --logpath C:\dev\fugu\trunk\db\logs\logfilename.log --logappend --dbpath C:\dev\fugu\trunk\db\data --directoryperdb --install
net start MongoDB

if not %ERRORLEVEL% == 0 pause