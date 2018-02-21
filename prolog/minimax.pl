:- include('tictactoe.pl').

% minimax(Pos, BestNextPos, Val)
% Pos is a position, Val is its minimax value.
% Best move from Pos leads to position BestNextPos.
minimax(Pos, BestNextPos, Levels, Val) :-                  % Pos has successors
	Levels >= 0,
    bagof(NextPos, move(Pos, NextPos), NextPosList),
	Levels1 is Levels -1,
    best(NextPosList, BestNextPos, Levels1, Val), !.

minimax(Pos, _, _, Val) :-                     % Pos has no successors
    utility(Pos, Val).


best([Pos], Pos, Levels, Val) :-
    minimax(Pos, _, Levels, Val), !.

best([Pos1 | PosList], BestPos, Levels, BestVal) :-
    minimax(Pos1, _, Levels, Val1),
    best(PosList, Pos2, Levels, Val2),
    betterOf(Pos1, Val1, Pos2, Val2, BestPos, BestVal).



betterOf(Pos0, Val0, _, Val1, Pos0, Val0) :-   % Pos0 better than Pos1
    min_to_move(Pos0),                         % MIN to move in Pos0
    Val0 > Val1, !                             % MAX prefers the greater value
    ;
    max_to_move(Pos0),                         % MAX to move in Pos0
    Val0 < Val1, !.                            % MIN prefers the lesser value

betterOf(_, _, Pos1, Val1, Pos1, Val1).        % Otherwise Pos1 better than Pos0