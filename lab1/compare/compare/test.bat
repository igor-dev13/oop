set PROGRAM="%~1"

rem c�������� ������ ������
%PROGRAM% empty.txt %TEMP%\empty.txt
if NOT ERRORLEVEL 0 goto err
fc.exe %TEMP%\empty.txt empty.txt
if NOT ERRORLEVEL 0 goto err

rem ������� ��������� ��� ������ ���� ���� ���� ����, � ������ ���
fc.exe empty.txt text.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ���� ����� ������
fc.exe text.txt text2.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ���� �� ������ ���� �� �������� ������
%PROGRAM% non-existing-file-name.txt text.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1