set PROGRAM="%~1"

rem проверяем запуск без параметров
echo run program without arguments:
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-parameters-count-error.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска c буквой вместо числа, для параметра число в байте
echo run program with the letter instead of a number, parameter number in byte:
%PROGRAM% K 2 R > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-when-input-word-instead-of-int-for-bite.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска c буквой вместо числа, для параметра количество битов для смещения
echo run program with the letter instead of numbers for setting the number of bits for offset:
%PROGRAM% 17 J R > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-when-input-word-instead-of-int-for-number-of-bits.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска c ошибочной буквой, для параметра направления сдвига в байте
echo run program with the wrong letter, set to the direction of rotate in a byte:
%PROGRAM% 17 4 E > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-when-input-wrong-direction-letter.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска c числом 260, в качестве параметра число в байте
echo run program with the number 260 as a parameter in byte number:
%PROGRAM% 260 4 L > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-bite-is-overload.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска c числом 10, в качестве параметра направления сдвига в байте
echo run program with the number of trigger 10, as a parameter in the rotate direction byte:
%PROGRAM% 17 10 L > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe out_files\expected-output-count-of-bits-in-bite-overload.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска с числом, 17, количеством битов 2 и сдвигом влево в качестве параметра
echo run program with number 17, and number 2 bits rotate to the left as a parameter:
%PROGRAM% 17 2 L > %TEMP%\output.txt
if NOT ERRORLEVEL 0 goto err
fc.exe out_files\expected-output-right-nubmer-pass-left.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err

rem проверка запуска с числом, 17, количеством битов 2 и сдвигом вправо в качестве параметра
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