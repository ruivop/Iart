import java.util.Arrays;
import java.util.Collections;

public class Game {
	char player = 'b';
	char opponent = 'w';

	// This function returns true if there are moves
	// remaining on the board. It returns false if
	// there are no moves left to play.
	boolean isMovesLeft(char b[][]) {
		for (int i = 0; i<b.length; i++)
			for (int j = 0; j<b.length; j++)
				if (b[i][j]=='_')
					return true;
		return false;
	}

	//gives a score of a given board from -100 to 100
	int evaluate(char b[][]) {
		int furthestBlack = b.length; //how many tiles are left to reach the end
		int furthestWhite = b.length; //how many tiles are left to reach the end
		
		//check the black
		for(int i = 0; i < b.length; i++){
			for(int j = 0; j < b.length; j++){
				//check the top
				if(i ==0){
					furthestBlack = Math.min(furthestBlack,
							calcOrthoadjUp(b, i, j));
				}
				//check the right
				if(j == 0){
					furthestWhite = Math.min(furthestWhite,
							calcOrthoadjRh(b, i, j));
				}
			}
		}
		int ret = 0;
		//if(player=='b'){
			//if(furthestBlack < furthestWhite){
				ret = (int) ((1 - (1.0*furthestBlack)/b.length)*100);
			//} else {
			//	ret = -(int) ((1 - (1.0*furthestWhite)/b.length)*100);
			//}
		/*} else{
			if(furthestBlack < furthestWhite){
				ret = -(int) ((1 - (1.0*furthestBlack)/b.length)*100);
			} else {
				ret = (int) ((1 - (1.0*furthestWhite)/b.length)*100);
			}
		}*/
		return ret;
	}

	private int calcOrthoadjUp(char[][] b, int i, int j) {
		if(i<0 || j<0 || i>=b.length || j>=b.length || b[i][j] != 'b')
			return b.length;

		if(i == b.length-1){
			return 0;
		}

		int furthest = b.length-i-1;
		b[i][j] = '_';
		int[] num = { calcOrthoadjUp(b,i+1,j),
				calcOrthoadjUp(b,i-1,j),
				calcOrthoadjUp(b,i,j+1),
				calcOrthoadjUp(b,i,j-1)
		};
		b[i][j] = 'b';

		for (int index = 0; index < num.length; index++) {
			if (num[index] < furthest) {
				furthest = num[index];
			}
		}
		return furthest;
	}

	private int calcOrthoadjRh(char[][] b, int i, int j) {
		if(i<0 || j<0 || i>=b.length || j>=b.length || b[i][j] != 'w')
			return b.length;

		if(j == b.length-1){
			return 0;
		}

		int furthest = b.length-j-1;
		b[i][j] = '_';
		int[] num = { calcOrthoadjRh(b,i+1,j),
				calcOrthoadjRh(b,i-1,j),
				calcOrthoadjRh(b,i,j+1),
				calcOrthoadjRh(b,i,j-1)
		};
		b[i][j] = 'w';

		for (int index = 0; index < num.length; index++) {
			if (num[index] < furthest) {
				furthest = num[index];
			}
		}
		return furthest;
	}

	// This is the minimax function. It considers all
	// the possible ways the game can go and returns
	// the value of the board
	int minimax(char b[][], int depth, boolean isMax){
		int score = evaluate(b);
		if(depth == 2){
			return score;
		}

		// If Maximizer has won the game return his/her
		// evaluated score
		if (score == 100)
			return score;

		// If Minimizer has won the game return his/her
		// evaluated score
		if (score == -100)
			return score;

		// If there are no more moves and no winner then
		// it is a tie
		if (isMovesLeft(b)==false)
			return 0;

		// If this maximizer's move
		if (isMax){
			int best = -1000;

			// Traverse all cells
			for (int i = 0; i<b.length; i++) {
				for (int j = 0; j<b.length; j++) {
					// Check if cell is empty
					if (b[i][j]=='_'){
						// Make the move
						b[i][j] = player;

						// Call minimax recursively and choose
						// the maximum value
						best = Math.max( best,
								minimax(b, depth+1, !isMax) );

						// Undo the move
						b[i][j] = '_';
					}
				}
			}
			return best;
		}

		// If this minimizer's move
		else {
			int best = 1000;

			// Traverse all cells
			for (int i = 0; i<b.length; i++)
			{
				for (int j = 0; j<b.length; j++)
				{
					// Check if cell is empty
					if (b[i][j]=='_')
					{
						// Make the move
						b[i][j] = opponent;

						// Call minimax recursively and choose
						// the minimum value
						best = Math.min(best,
								minimax(b, depth+1, !isMax));

						// Undo the move
						b[i][j] = '_';
					}
				}
			}
			return best;
		}
	}

	// This will return the best possible move for the player
	Move findBestMove(char board[][], char p)
	{
		int bestVal = -1000;
		Move bestMove = new Move();
		bestMove.row = -1;
		bestMove.col = -1;

		this.player = p;
		this.opponent = p == 'b' ? 'w' : 'b';

		// Traverse all cells, evaluate minimax function for
		// all empty cells. And return the cell with optimal
		// value.
		for (int i = 0; i<board.length; i++){
			for (int j = 0; j<board.length; j++){
				// Check if cell is empty
				if (board[i][j]=='_'){
					// Make the move
					board[i][j] = player;

					// compute evaluation function for this
					// move.
					int moveVal = minimax(board, 1, false);

					// Undo the move
					board[i][j] = '_';

					// If the value of the current move is
					// more than the best value, then update
					// best/
					if (moveVal > bestVal)
					{
						bestMove.row = i;
						bestMove.col = j;
						bestVal = moveVal;
					}
				}
			}
		}

		System.out.println("The value of the best Move is : " + bestVal);

		return bestMove;
	}

	// Driver code
	public static void main(String [ ] args)
	{
		char board[][] =
			{
					{ '_', 'w', '_', '_', '_', '_', 'b', '_', '_', '_', '_', 'w', '_', '_' },
					{ '_', '_', '_', 'b', '_', '_', 'b', 'b', 'w', '_', '_', '_', '_', 'b' },
					{ 'b', '_', '_', '_', '_', 'w', '_', 'b', '_', '_', 'b', '_', '_', '_' },
					{ '_', '_', 'w', '_', '_', '_', '_', 'b', 'b', '_', '_', '_', 'w', '_' },
					{ '_', '_', '_', '_', 'b', '_', '_', '_', 'b', 'w', '_', '_', '_', '_' },
					{ '_', 'b', '_', '_', '_', '_', 'w', '_', 'b', '_', '_', 'b', '_', '_' },
					{ 'w', '_', 'w', 'w', '_', '_', '_', '_', 'b', '_', '_', '_', '_', 'w' },
					{ 'w', 'w', 'w', '_', '_', 'b', '_', '_', 'b', 'b', 'w', '_', '_', '_' },
					{ '_', '_', 'b', '_', '_', '_', '_', 'w', '_', 'b', '_', '_', 'b', '_' },
					{ '_', '_', '_', '_', 'w', '_', '_', '_', '_', 'b', '_', '_', '_', '_' },
					{ '_', 'w', '_', '_', '_', '_', 'b', '_', '_', 'b', 'b', 'b', '_', '_' },
					{ '_', '_', '_', 'b', '_', '_', '_', '_', 'w', 'b', '_', 'b', '_', 'b' },
					{ 'b', '_', '_', '_', '_', 'w', '_', '_', '_', '_', '_', '_', '_', '_' },
					{ '_', '_', 'w', '_', '_', '_', '_', 'b', '_', '_', '_', '_', '_', '_' }
			};
		Game game = new Game();
		Move bestMove = game.findBestMove(board, 'b');
		//int score = game.evaluate(board);
		//System.out.println("The score is: "  + score);

		System.out.println("The Optimal Move is");
		System.out.println("ROW: " + bestMove.row + " COL: " + bestMove.col);
	}
}
