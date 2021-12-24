#include "Minimax.h"

void Minimax::doMove(State& state)
{
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
		else
		{
			return Move(-10);
		}
	}


	return Move();
}
