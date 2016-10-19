set PROGRAM="%~1"

rem ��������� ������ ��� ����������
echo run program without arguments:
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-parameters-count-error.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem �������� ������� c ������ ������ �����, ��� ��������� ����� � �����
echo run program with the letter instead of a number, parameter number in byte:
%PROGRAM% K 2 R > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-when-input-word-instead-of-int-for-bite.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem �������� ������� c ������ ������ �����, ��� ��������� ���������� ����� ��� ��������
echo run program with the letter instead of numbers for setting the number of bits for offset:
%PROGRAM% 17 J R > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-when-input-word-instead-of-int-for-number-of-bits.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem �������� ������� c ��������� ������, ��� ��������� ����������� ������ � �����
echo run program with the wrong letter, set to the direction of rotate in a byte:
%PROGRAM% 17 4 E > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-when-input-wrong-direction-letter.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem �������� ������� c ������ 260, � �������� ��������� ����� � �����
echo run program with the number 260 as a parameter in byte number:
%PROGRAM% 260 4 L > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-bite-is-overload.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem �������� ������� c ������ 10, � �������� ��������� ����������� ������ � �����
echo run program with the number of trigger 10, as a parameter in the rotate direction byte:
%PROGRAM% 17 10 L > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-count-of-bits-in-bite-overload.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem �������� ������� � ������, 17, ����������� ����� 2 � ������� ����� � �������� ���������
echo run program with number 17, and number 2 bits rotate to the left as a parameter:
%PROGRAM% 17 2 L > %TEMP%\output.txt
if NOT ERRORLEVEL 0 goto err
fc.exe out_files\expected-output-right-nubmer-pass-left.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem �������� ������� � ������, 17, ����������� ����� 2 � ������� ������ � �������� ���������
echo run program with number 4, and number 2 bits rotate to the left as a parameter:
%PROGRAM% 4 2 R > %TEMP%\output.txt
if NOT ERRORLEVEL 0 goto err
fc.exe out_files\expected-output-right-nubmer-pass-right.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1