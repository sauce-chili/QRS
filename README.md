<h1>Программа для составления таблицы истинности заданного логического выражения</h1>
<p>
<u>Автор:</u> <i>Смирнов Дмитрий Андреевич</i>
<br><small>ст. гр. ПрИн-267 ФГБОУ ВО "ВолгГТУ", г. Волгоград 2024 год.</small> <br />
</p>

---
<h2><b>Назначение</b></h2>
Программа предназначена для построения таблицы истинности логического выражения написанного на языке С++.

---
<h2><b>Формат входных данных</b></h2>
<p>
Входные данные представляются в виде путей до двух текстовых файлов.<br />
В первом текстовом фале содержится запись логического выражения. Данные в файле разделены пробелами и записываются в постфиксном формате: сначала пишутся операнды, затем операция. <br />
<b>Пример:</b> <br />
Логическое выражение: <br />

(a[0][0] + b) * 18e-10 && -c != 0 <br />
Запись логического выражения внутри входного файла: <br />

a 0 [] 0 [] b + 18e-10 * c -$ 0 != &&
</p>

---

<h2><b>Формат выходных данных</b></h2>
<p>
Выходные данные представляются в виде файла с расширением .html . После завершения работы программы(если во входных данных не было найдено ошибок), в файле будет находится html код таблицы.  В первой строке таблицы будут перечислены используемые в логическом выражении параметры, записанные в инфиксной форме, и результат выражения, обозначаемый буквой F. В последующих строках перечислены значения (0 – «ложь» или 1 – «истина»),  которое принимает параметр на соответсвенной позиции, и значение выражение при заданных параметрах. <br />

<b>Пример выходного файла для логического выражения:</b><br />
(a[0][0] + b) * 18e-10 && -c != 0 <br />
<b>Выходной файл:</b><br/>

<!DOCTYPE html>  
<html>  
<head>  
 <style> table {  
            border: 1px solid black;  
            border-collapse: collapse;  
            width: 100%;  
        }  
        td {  
            border: 1px solid black;  
            text-align: center;  
            padding: 8px;  
            word-wrap: break-word;  
            word-break: break-all;  
        }  
    </style>  
</head>  
<body>  
<table><tr><td>(a[0][0]+b)*18e-10</td><td>-c!=0</td><td>F</td></tr><tr><td>0</td><td>0</td><td>0</td></tr><tr><td>0</td><td>1</td><td>0</td></tr><tr><td>1</td><td>0</td><td>0</td></tr><tr><td>1</td><td>1</td><td>1</td></tr></table>  
</body>  
</html>
 
---
<h2><b>Способы запуска программы</b></h2>
<p>
<u><i>В основном режиме</i></u>:<br />
<code>
.\ModuleWork_Q_RS_main.exe .\input.txt .\out.html
</code>
<br/>
<u><i>В режиме тестирования:</i></u><br/>
<code>
.\ModuleWork_Q_RS_main.exe --test
</code>
<br/>
</p>

---

<h2><b>Иерархия</b></h2>

<ul>
<li>cmake-build-release/ModuleWork_Q_RS_main.exe - Исполняемый файл приложения</li>
<li>src
<ul>
<li>builders/ExprNodeBuilder - Cодержит вспомогательный класс для построения узлов дерева.</li>
<li>entities -  Содержит абстракции и реализации узлов дерева-выражения
<ul>
<li>Arithmetic - Содержит реализацию узлов являющихся арифметическими операциями.</li>
<li>Constant - Содержит реализацию узлов-констант.</li>
<li>Logical - Содержит реализацию узлов являющихся логическими операциями.</li>
</ul>
</li>
<li>exception - Содержит классы исключений, используемые в приложении.</li>
<li>truthtablegererator/Generator - Содержит класс для генерации таблиц истинности.</li>
<li>utils - Содержит утилитные классы и функции, используемые в приложении.</li>
</ul>
</li> 
<li>tests - Содержит модульные тесты
<ul>
<li>TestIO - Содержит тесты ввода/вывода
</li>
</ul>
</li>
</ul>

---

<h2><b>Технические требования</b></h2>
Программа разработана с использованием языка С++ стандарта С++20 ISO/IEC.

---
<h2><b>Особенности автодокументирования</b></h2>
Для автодокументирования исходного задействована кросплатформенная система документирования Doxygen. 
<br><br>
Советуем, после установки самого приложения Doxygen, скачанного с  <a href="https://www.doxygen.nl/">официального сайта</a>, посетить <a href="https://www.doxygen.nl/manual/install.html">страницу</a> для ознакомления с использованием Doxygen в вашей операционной системе.  
<br><br>
Так, пользователи Windows 10/11, для получения корретно сгенерированной страницы с документацией (включая иерархию вызова функций), должны устноавить дополнительную программу <a href="https://graphviz.org/">GraphViz</a> 

---
<p>
Репозиторий: <br />
<a href=https://github.com/sauce-chili/QRS>https://github.com/sauce-chili/QRS</a><br/>
</p>
