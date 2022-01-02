#include "Minimax.h"

Move Minimax::doMove(State& state, int currentDepth)
{
	int bestScore = -std::numeric_limits<int>::max();
	Move bestMove;
	bestMove.index = -1;
	bestMove.score = bestScore;
	//minimax function
	std::vector<int> availableMoves = state.getLegalSpotsToPlay();
	for (int availableMove : availableMoves)
	{
		Move move;
		move.index = availableMove;
		move.score = evaluate(state, CheckerType::Yellow, move);
		if (move.score > bestMove.score)
		{
			bestMove.score = move.score;
			bestMove.index = move.index;
		}
	}

	return bestMove;
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
	CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
	int score = 0;
	//check if you are one move from winning
	//should get more points 
	state.setPieceAtPosition(move.index, player);
	if (state.checkVictory() != GameOver::None && state.checkVictory() != GameOver::Tie)
	{
		score = std::numeric_limits<int>::max();
		return score;
	}
	//check if you're opponent is still close to winning
	state.setPieceAtPosition(move.index, CheckerType::None);
	//get horizontal for board
	std::array<CheckerType, 3> row = state.getAllOnSameRow(move.index);
	if (areAllColour(oppositeColour, row))
	{
		score = std::numeric_limits<int>::max();
		return score;
	}
	//get column for board
	std::array<CheckerType, 3> col = state.getAllOnSameColumn(move.index);
	if (areAllColour(oppositeColour, col))
	{
		score = std::numeric_limits<int>::max();
		return score;
	}
	//get straight down for move
	std::array<CheckerType, 3> straightDown = state.getAllStraightDown(move.index);
	if (areAllColour(oppositeColour, straightDown))
	{
		score = std::numeric_limits<int>::max();
		return score;
	}
	//if on a board diagonal or diagonal between boards check all of those diagonals
	if (state.isOnBoardDiagonal(move.index))
	{
		std::array<CheckerType, 3> diagonal = state.getAllOnSameBoardDiagonal(move.index);
		if (areAllColour(oppositeColour, diagonal))
		{
			score = std::numeric_limits<int>::max();
			return score;
		}
	}
	if (state.isOnDiagonal(move.index))
	{
		std::array<CheckerType, 3> diagonal = state.getAllOnSameDiagonal(move.index);
		if (areAllColour(oppositeColour, diagonal))
		{
			score = std::numeric_limits<int>::max();
			return score;
		}
		evaluateGroup(player, score, diagonal);
	}
	evaluateGroup(player, score, row);
	evaluateGroup(player, score, col);
	evaluateGroup(player, score, straightDown);
	if (state.isCorner(move.index))
	{
		score += 1;
	}
	return score;
}

void Minimax::evaluateGroup(CheckerType player, int& score, std::array<CheckerType, 3> group)
{
	for (CheckerType type : group)
	{
		if (type == player)
		{
			score += 2;
		}
		else if (type == CheckerType::None)
		{
			score += 1;
		}
		else//opposite colour so we want to remove one from the score
		{
			score -= 1;
		}
	}
}

bool Minimax::areAllColour(CheckerType colour, std::array<CheckerType, 3> arr)
{
	for (CheckerType type : arr)
	{
		if (type != colour) return false;
	}
	return true;
}
