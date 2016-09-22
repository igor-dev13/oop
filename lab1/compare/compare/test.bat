set PROGRAM="%~1"

rem cࠢ����� ������ 䠩���
%PROGRAM% empty.txt %TEMP%\empty.txt
if NOT ERRORLEVEL 0 goto err
fc.exe %TEMP%\empty.txt empty.txt
if NOT ERRORLEVEL 0 goto err

rem ������� ���㫥��� ��� �訡�� �᫨ ���� 䠩� ����, � ��ன ���
fc.exe empty.txt text.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ���㫥��� ��� �訡�� �᫨ 䠩�� ࠧ��
fc.exe text.txt text2.txt
if NOT ERRORLEVEL 1 goto err

rem ������� ���㫥��� ��� �訡�� �᫨ �� ������ ���� �� �室��� 䠩���
%PROGRAM% non-existing-file-name.txt text.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1