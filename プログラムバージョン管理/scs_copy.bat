@echo off
setlocal enabledelayedexpansion

:: 
:: 作業フォルダ名を求める
::
set "Dirname=%~dp1"
cd "%Dirname%"


::
:: Application Nameを求める
::
for /f tokens^=2^ delims^=^" %%a in ('findstr -r /c:"<Application Name=\".*\">$" "%~1"') do (
  set "Name=%%~a"
)

:: 
:: Description、Version、Typeを求める
::
for /f tokens^=2^,4^,6^ delims^=^" %%a in ('findstr -r /c:"<PID Description=\".*\" Version=\".*\" Type=\".*\"/>$" "%~1"') do (
  set "Description=%%~a"
  set "Version=%%~b"
  set "Type=%%~c"
)

:: 
:: scsファイル名を求める
::
for /f tokens^=4^ delims^=^" %%a in ('findstr -r /c:"<MainModule ModuleName=\"MAINTASK\" FileName=\".*\"/>$" "%~1"') do (
  set "scs_filename=%%~a"
  set "scs_basename=%%~na"
)

:: 
:: lhxファイル名を求める
::
for /f tokens^=2^ delims^=^" %%A in ('findstr -r /c:"<Hexfile FileName=\".*\"/>$" "%~1"') do (
  set "lhx_filename=%%~A"
  set "lhx_basename=%%~nA"
)

:: 
:: lhxファイルの更新日時を求める
::
for /f "usebackq tokens=1,2" %%A in (`forfiles /m "%lhx_filename%" /c "cmd /c echo @fdate @ftime"`) do (
    set "d=%%A"
    set "t=%%B"
)
set "prefix=%Version:.=%_%d:/=%%t::=%"

echo dirname = !Dirname!
echo Name = !Name!
echo Description = !Description!
echo Version = !Version!
echo Type = !Type!
echo scs filename = !scs_filename!
echo scs basename = !scs_basename!
echo lhx filename = !lhx_filename!
echo lhx basename = !lhx_basename!
echo prefix = !prefix!

::
:: LHXファイルをコピーする
:: 
if not exist "lhx" mkdir "lhx"
copy "%lhx_filename%" "lhx\%lhx_basename%%prefix%.lhx"

::
:: SCSファイルをコピーする
:: 
if not exist "scs" mkdir "scs"
copy "%scs_filename%" "scs\%scs_basename%%prefix%.scs"

pause