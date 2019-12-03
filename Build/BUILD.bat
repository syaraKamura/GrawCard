SET BULD_SOLUTION=%1
SET PLATFORM=%2
SET Configuration=%3

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" %BULD_SOLUTION% /p:Configuration="%Configuration%";Platform="%PLATFORM%" /t:clean;rebuild

echo "End Build %PLATFORM% %Configuration%"

pause