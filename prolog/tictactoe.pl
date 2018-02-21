:- use_module(library(lists)).

% nextPlayer(X1, X2)
% True if X2 is the next player to play after X1.
nextPlayer(w, b).
nextPlayer(b, w).

move([X1, play, Board], [X2, play, NextBoard]) :-
    nextPlayer(X1, X2),
    move_auxu(X1, Board, NextBoard).

% move_aux(+Player, +Board, -NextBoard)
% True if NextBoard is Board whith an empty case replaced by Player mark.
move_auxu(P, [A|Bs], [A1|Bs]) :- move_aux(P, A, A1).
move_auxu(P, [A|B1s], [A|B2s]) :- move_auxu(P, B1s, B2s).

move_aux(P, ['o'|Bs], [P|Bs]).

move_aux(P, [B|Bs], [B|B2s]) :-
    move_aux(P, Bs, B2s).


% min_to_move(+Pos)
% True if the next player to play is the MIN player.
min_to_move([w, _, _]).

% max_to_move(+Pos)
% True if the next player to play is the MAX player.
max_to_move([b, _, _]).

% utility(+Pos, -Val) :-
% True if Val the the result of the evaluation function at Pos.
% We will only evaluate for final position.
% So we will only have MAX win, MIN win or draw.
% We will use  1 when MAX win
%             -1 when MIN win
%              0 otherwise.

utility([Player,_,Board], Val):- scoreElm(Board, Player, Val).
scoreElm(Board, Elm, Score):- findAllElm(Board, Elm, Places),!,
								scorePlaces(Places, Score),!.

scorePlaces([], 0).
scorePlaces([[X,Y]|R], Score):- checkDown([X,Y], R),
									scorePlaces(R, Score1), Score is Score1+1.
scorePlaces([_|R], Score):- scorePlaces(R, Score).

checkDown([X,Y], R):- Y1 is Y+1, member([X,Y1], R).
								
								
findAllElm(Board, Elm, Places):- bagof([X,Y], findNextElem(Board, Elm, 0, X, Y), Places).

findNextElem([], _, _, _, _):- !,fail.
findNextElem([A|_], Elm, Y, X, Y):-  findNextElem(A, Elm,0,X).
findNextElem([_|B], Elm, CntY, X, Y):- CntY1 is CntY+1, 
									findNextElem(B, Elm, CntY1, X, Y).
findNextElem([], _, _, _):- !,fail.							
findNextElem([Elm|_], Elm, X, X).
findNextElem([_|R], Elm, CntX, X):-CntX1 is CntX+1, findNextElem(R, Elm, CntX1, X).


	
tabl([
	[ 'o', 'w', 'o', 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'o' ],
	[ 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o', 'o', 'b' ],
	[ 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'b', 'o', 'o', 'b', 'o', 'o', 'o' ],
	[ 'o', 'o', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'w', 'o' ],
	[ 'o', 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o', 'o' ],
	[ 'o', 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o', 'o', 'b', 'o', 'o' ],
	[ 'w', 'o', 'w', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'b', 'w' ],
	[ 'w', 'o', 'w', 'o', 'o', 'b', 'o', 'o', 'o', 'b', 'w', 'o', 'b', 'o' ],
	[ 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o', 'o', 'b', 'o' ],
	[ 'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'b', 'b', 'o' ],
	[ 'o', 'w', 'o', 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'b', 'b', 'o', 'o' ],
	[ 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'o', 'b', 'o', 'b' ],
	[ 'b', 'o', 'o', 'o', 'o', 'w', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o' ],
	[ 'o', 'o', 'w', 'o', 'o', 'o', 'o', 'b', 'o', 'o', 'o', 'o', 'o', 'o' ]]).	
	
printtabl([A|B]):-format(' ~w |', [' ']), printcabc(A,0),nl, printtabl([A|B],0).
printtabl:- tabl([A|B]),format(' ~w |', [' ']), printcabc(A,0),nl, printtabl([A|B],0).
printcabc([],_).
printcabc([_|B], N):- N1 is N+1, ((N < 10, format(' ~w |', [N])) ; (N >= 10, format('~w |', [N]))), printcabc(B, N1).
printtabl([],_).
printtabl([A|B], N):- ((N < 10, format(' ~w | ', [N])) ; (N >= 10, format('~w | ', [N]))), println(A), nl, N1 is N + 1, printtabl(B, N1).
println([]).
println([A|B]):-write(A), write(' | '), println(B).