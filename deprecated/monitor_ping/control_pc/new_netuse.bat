@echo off
setlocal enabledelayedexpansion
if EXIST mount_drive (
set /p DRIVE=<mount_drive
goto L_UMOUNT
) else (
goto L_MOUNT
)
:L_MOUNT
for  %%C in (Z Y X W V U T S R Q P O N M L K J I H G F E D C B A) do (
set DRIVE=%%C
echo %DRIVE%
net use %DRIVE%: \\192.168.7.112\jeff
if %ERRORLEVEL% EQU 0 (
echo %DRIVE%> mount_drive
echo mount on %DRIVE%
exit /b 0
)
)
:L_UMOUNT
net use %DRIVE%: /delete
del mount_drive
EXIT /b 0
