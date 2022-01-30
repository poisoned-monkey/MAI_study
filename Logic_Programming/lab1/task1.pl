% Предикаты работы со списками

my_length([],0).
my_length([_|T], N) :-
  my_length(T, N1),
  N is N1 + 1.

my_member(X,[X|_]).
my_member(X,[_|T]) :-
  my_member(X,T).

my_append([],X,X).
my_append([X|Y],Z,[X|T]) :-
  my_append(Y,Z,T).

my_remove(X,[X|T],T).
my_remove(X,[H|T],[H|Y]) :-
  my_remove(X,T,Y).

my_permute([],[]).
my_permute(X,[H|T1]) :-
  my_remove(H,X,T),
  my_permute(T,T1).

my_sublist(S,R) :-
  my_append(X,_,S),
  my_append(_,R,X).

% Нахождение элемента списка, следующего за данным

f([X,Y|_],X,R) :- 
R is Y, !. 

f([X|T], E, R) :- 
f(T, E, R).

% Разделение списка на два по принципу четности элементов

f([],[],[]). 
f([H|T], [H|R1], R2) :- 
ischet(H), f(T,R1, R2). 

f([H|T], R1, [H|R2]):- 
not(ischet(H)), f(T, R1, R2).