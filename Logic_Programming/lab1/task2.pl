% Задание 2

/*Получить таблицу групп и средний балл по каждой из групп
Для каждого предмета получить список студентов, не сдавших экзамен (grade=2)
Найти количество не сдавших студентов в каждой из групп*/

% The line below imports the data
:- [one].

% Первая часть
group(Group,L) :-
    findall(X,student(Group,X),L).

group_table([Group]) :-
    findall(X,student(Group,X),L),
    asserta(group(Group,L)),
    write(Group),
    write(": "),
    write(L),
    !.

group_table([Group|T]) :-
    findall(X,student(Group,X),L),
    asserta(group(Group,L)),
    write(Group),
    write(": "),
    write(L),
    nl,
    group_table(T).

gradeN_student(N,Name,Group) :-
    student(Group,Name),
    grade(Name,_,N).

average_grade(Group,N) :-
    bagof(X,gradeN_student(2,X,Group),L2),
    bagof(X,gradeN_student(3,X,Group),L3),
    bagof(X,gradeN_student(4,X,Group),L4),
    bagof(X,gradeN_student(5,X,Group),L5),
    length(L2,L2_length), length(L3,L3_length), length(L4,L4_length), length(L5,L5_length),
    Grades_length is L2_length + L3_length + L4_length + L5_length,
    N is (L2_length * 2 + L3_length * 3 + L4_length * 4 + L5_length * 5) / Grades_length.


% Вторая часть
notpassed_sub_list(Subject,L) :-
    bagof(X,grade(X,Subject,2),L).


% Третья часть
notpassed_student(Name,Group) :-
    student(Group,Name),
    grade(Name,_,2).

n_of_notpassed(Group,N) :-
    setof(X,notpassed_student(X,Group),L),
    length(L,N).