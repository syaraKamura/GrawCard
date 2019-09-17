SET BULD_SOLUTION=%1
SET PLATFORM=%2
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" %BULD_SOLUTION% /p:Platform="%PLATFORM%" /t:clean;rebuild
pause