#include "Minimax.h"

void Minimax::doMove(State& state, int currentDepth)
{
	//minimax function
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

int Minimax::evaluate(State state, CheckerType player)
{
	int score = 0;
	//check if you are one move from winning

	//check if you're opponent is still close to winning
	return score;
}
