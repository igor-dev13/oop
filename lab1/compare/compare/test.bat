set PROGRAM="%~1"

rem c�������� ����������� stdout
%PROGRAM% fileA.txt fileB.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 0 goto err
fc.exe "%TEMP%\output.txt" exepected-fileA-fileB.txt
IF ERRORLEVEL 1 goto err

rem c�������� ������ ������
%PROGRAM% empty.txt %TEMP%\empty.txt
if NOT ERRORLEVEL 0 goto err
fc.exe %TEMP%\empty.txt empty.txt
if NOT ERRORLEVEL 0 goto err

rem ������� ��������� ��� ������ ���� ���� ���� ����, � ������ ���
fc.exe empty.txt fileA.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ���� ����� ������
fc.exe fileA.txt fileB.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ���� �� ������ ���� �� �������� ������
%PROGRAM% non-existing-file-name.txt fileA.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1