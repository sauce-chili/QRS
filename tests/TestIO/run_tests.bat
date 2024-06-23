@echo off

:: Задаем путь к exe файлу
set exePath="..\..\cmake-build-release\ModuleWork_Q_RS_main.exe"

:: Задаем путь к папке test
set testDir=".\tests"

:: Проверка работоспособности базовых логических операций

:: AND операция
echo. > %testDir%\out_1.html
%exePath% %testDir%\in_1.txt %testDir%\out_1.html

:: OR операция
echo. > %testDir%\out_2.html
%exePath% %testDir%\in_2.txt %testDir%\out_2.html

:: NOT операция
echo. > %testDir%\out_3.html
%exePath% %testDir%\in_3.txt %testDir%\out_3.html

:: Проверка работоспособности логических операций в совокупности с другими типами узлов логического выражения

:: Дерево состоящие из одной переменной (a * x && -032)
echo. > %testDir%\out_4.html
%exePath% %testDir%\in_4.txt %testDir%\out_4.html

:: Дерево состоит из константы (250 + -0xFA)
echo. > %testDir%\out_5.html
%exePath% %testDir%\in_5.txt %testDir%\out_5.html

:: Сложное дерево с 2-мя параметрами (a[0][0] + b) * 18e-10 && -c != 0
echo. > %testDir%\out_6.html
%exePath% %testDir%\in_6.txt %testDir%\out_6.html

:: Сложное дерево с 3-мя параметрами
:: ! x && (-(a[i] && b) || !a[i]) || a[i] && (-(a[i] && b) || x)
echo. > %testDir%\out_7.html
%exePath% %testDir%\in_7.txt %testDir%\out_7.html

:: Дерево с коммутационным параметром (a[i]*b=b*a[i])
:: !(a[i] * b && -0xFA) || (x && (b * a[i]))
echo. > %testDir%\out_8.html
%exePath% %testDir%\in_8.txt %testDir%\out_8.html

:: Проверка обработки ошибок:

:: Пустое дерево
%exePath% %testDir%\in_9.txt %testDir%\out_9.html > %testDir%\out_9.html 2>&1

:: Отсутствует требуемый для бинарной операции операнд операнд
%exePath% %testDir%\in_10.txt %testDir%\out_10.html > %testDir%\out_10.html 2>&1

:: Отсутствует требуемый для унарной операции операнд операнд
%exePath% %testDir%\in_14.txt %testDir%\out_14.html > %testDir%\out_14.html 2>&1

:: Встречена неизвестная последовательность
%exePath% %testDir%\in_11.txt %testDir%\out_11.html > %testDir%\out_11.html 2>&1

:: Превышение лимита параметров
%exePath% %testDir%\in_12.txt %testDir%\out_12.html > %testDir%\out_12.html 2>&1

:: Лишний операнд
%exePath% %testDir%\in_13.txt %testDir%\out_13.html > %testDir%\out_13.html 2>&1

:: Все операнды лишние
%exePath% %testDir%\in_15.txt %testDir%\out_15.html > %testDir%\out_15.html 2>&1

:: Файл не существует
%exePath% %testDir%\non_existent_file.txt %testDir%\out_non_existent_file.html > %testDir%\out_non_existent_file.html 2>&1
