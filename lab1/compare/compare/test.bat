set PROGRAM="%~1"

rem cравнение пустых файлов
%PROGRAM% empty.txt empty2.txt
if NOT ERRORLEVEL 0 goto err
fc.exe %TEMP%\empty.txt empty2.txt
if NOT ERRORLEVEL 0 goto err

rem ожидаем ненулевой код ошибки если один файл пуст, а второй нет
%PROGRAM% empty.txt text.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt text.txt
if NOT ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки если файлы разные
%PROGRAM% text.txt text2.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\text.txt text2.txt
if NOT ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки если не найден один из входящих файлов
%PROGRAM% non-existing-file-name.txt text.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-file-is-missing.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1