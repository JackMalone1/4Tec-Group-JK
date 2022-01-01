#include "Minimax.h"

void Minimax::doMove(State& state, int currentDepth)
{
	//minimax function
	std::vector<int> availableMoves = state.getLegalSpotsToPlay();
}

Move Minimax::getBestMove(State state, CheckerType player)
{
	GameOver gameOver = state.checkVictory();

	if (gameOver != GameOver::None)
	{
		if (gameOver == GameOver::Tie)
		{
			return Move(0);
		}
		else if (gameOver == GameOver::Red && m_aiColour == CheckerType::Red)
		{
			return Move(10);
		}
		else if (gameOver == GameOver::Yellow && m_aiColour == CheckerType::Yellow)
		{
			return Move(10);
		}
		else //loss
		{
			return Move(-10);
		}
	}
	return Move();
}

int Minimax::evaluate(State state, CheckerType player, Move move)
{
	int score = 0;
	//check if you are one move from winning
	state.setPieceAtPosition(move.row, move.col, move.board, player);
	if (state.checkVictory() != GameOver::None && state.checkVictory() != GameOver::Tie)
	{
		score = std::numeric_limits<int>::max();
		return;
	}
	//check if you're opponent is still close to winning
	state.setPieceAtPosition(move.row, move.col, move.board, CheckerType::None);
	return score;
}
