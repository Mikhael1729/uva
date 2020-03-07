@ECHO OFF 
IF exist .output\ (@echo|set /p=""d) ELSE (mkdir .output\)
g++ *.cpp -o .output\a.exe
.output\a.exe

