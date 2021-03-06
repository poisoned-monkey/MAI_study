# Отчет по лабораторной работе
## по курсу "Искусственый интеллект"

### Студенты: 

| ФИО       | Роль в проекте                     | Оценка       |
|-----------|------------------------------------|--------------|
| Гамов | Программист, теоретик |          |
| Купцов | Программист, теоретик |       |
| Кузьмичев | Тестирование, проработка отчета |      |
| Голубев | Теоретик, тестировщик |          |
| Аксёнов | Написание отчета |          |

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |    4.3           |

> *База знаний достаточно проста. Практическое использование не очень осмысленно, т.к. пользователю необходимо точно перечислить набор исходных условий, и при малейшем отклонении от списка решение не будет найдено. Логичнее было бы использовать обратный вывод (или комбинированный). Отчет не описывает процесс коллективной работы.*

## Тема работы

Экспертная система для определения языка программирования, описанного свойствами, которые необходимы клиенту. 

## Концептуализация предметной области

При концептуализации предметной области, мы выделили следующие понятия:

Компилируемость

Интерпритируемость

Наличие ООП		

Возможность использования скриптов		

Наличие сборщика мусора	

Тип языка: функиональный,

логический, 

императивный			

Многопоточность		

Мультипроцессорность		

Кроссплатформенность		

Язык высокого/низкого уровня		

Адаптивность		

И построили следующие связи:

Некий язык программирования – вершина звена понятий -> тип этого языка: например, функциональный, высокого уровня и т.д. -> требования к языку: с ООП или без, с возможностью распараллеливания или без, комплируемый, некомпилируемый и т. д. -> приоритет выбора: если язык адаптивен, нежели другой, то лучше взять именно его.

Как динамические знания в нашей системе, можно выделить: языки программирования и их свойства. Как статические – требования пользователя к подбираемому в системе языку, его характеристики и свойства.

Данная предметная область может быть разделена между участниками для коллективного создания базы знаний по определенным различным свойствам каждого языка программирования. 

Приведите графические иллюстрации:
![Дерево И-ИЛИ](https://user-images.githubusercontent.com/55700839/112383303-02b61000-8cfe-11eb-91ea-3d04c4006a55.png)

## Принцип реализации системы

Для реализации системы была использована СП Python. Выбор пал на него в силу несложного синтаксиса и возможности использования нужных библиотек.
При написании на более императивном языке пришлось бы потратить больше времени и усилий как для поиска по базе знаний, так и для посторения дерева решений.

Нами был использован прямой вывод на базе библиотеки Pyknow. PyKnow - это библиотека для построения экспертных систем прямого вывода на Python, которая спроектирована так, чтобы быть похожей на классическую систему CLIPS. Данное сочетание было выбрано по причине простоты и понятности реализации.

## Механизм вывода

Для вывода ответа пользователю предлагается ответить на серию вопросов (факты о желаемом языке программирования). Во время каждого вопроса система находится в некоторой вершине дерева решений. <br/>
Пользователю задаётся вопрос содержащийся в текущей вершине, затем, в зависимости от ответа, происходит переход в другую вершину. <br/>

В результате прохода дерева от корня до одного из листов формируется запрос к базе знаний, на основе которого формируется ответ для пользователя.

## Извлечение знаний и база знаний

Процесс извлечения знаний можно разделить на два этапа. Сначала были придуманы вопросы, и по ним была создана таблица. Вторым этапом стало создание дерева знаний. Это было сделано на одной из первых конференций в дискорде. 

## Протокол работы системы

Приведите несколько примеров работы системы, проиллюстрируйте их фрагментами деревьев вывода.

![Тест 1](https://github.com/MAILabs-Edu-AI/lab-expert-system-programingai/blob/master/img/ai_test1.png)

![Тест 2](https://github.com/MAILabs-Edu-AI/lab-expert-system-programingai/blob/master/img/ai_test2.png)

## Выводы

Данная лабораторная работа заставила задуматься над разнообразием подходов к решению задач с помощью искуственного интелекта. Многим людям из нашей команды было не знакомо понятие "Экспертная система", и было интересно узнать, что такие системы могут использоваться для решения широкого спектра задач, к примеру, интерпретации, предсказания, диагностики, планирования, конструирования и т.д. Основная сложность работы состояла в правильной концептуцализации предметной области, в построении связей и деревая И-ИЛИ. Командная работа пришлась как нельзя кстати, так как именно благодаря ей каждый смог найти себе роль, выбрать ту часть работы, которая ему ближе всего, в которой он разбирается лучше других. Для коммуникациии внутри команды мы использовали канал в дискорде. Уже на этапе создания отчета мы узнали о таком инструменте, как scrum, который бы пригодился в нашей работе. В следующих командных ЛР было бы разумно использовать его. 

Помните, что несодержательные выводы -
самая частая причина снижения оценки.
