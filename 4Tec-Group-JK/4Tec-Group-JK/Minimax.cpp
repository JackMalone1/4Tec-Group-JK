#include "Minimax.h"

static bool compare(Move move, Move other)
{
	return move.score > other.score;
}

Move Minimax::doMove(State state)
{
	Move bestmove = getBestMove(state, CheckerType::Yellow, 0, Move());
	state.setPieceAtPosition(bestmove.index, CheckerType::Yellow);
	moves.clear();
	return bestmove;
}

Move Minimax::getBestMove(State& state, CheckerType player, int depth, Move move)
{
	std::vector<Move> rankedMoves;
	if (depth == MAX_DEPTH)
	{
		move.score = evaluate(state, player, move);
		return move;
	}
	else
	{
		std::vector<int> availableMoves = state.getLegalSpotsToPlay();
		for (int i : availableMoves)
		{
			move.index = i;
			CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
			move = getBestMove(state, oppositeColour, depth + 1, move);
			rankedMoves.push_back(move);
		}
	}
	return *std::max_element(rankedMoves.begin(), rankedMoves.end(), compare);
}

int Minimax::evaluate(State& state, CheckerType player, Move& move)
{
	CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
	int score = 0;

	std::array<CheckerType, 3> row = state.getAllOnSameRow(move.index);
	if (areAllColour(oppositeColour, row))
	{
		score = 10000000 - 1;
		return score;
	}
	std::array<CheckerType, 3> col = state.getAllOnSameColumn(move.index);
	if (areAllColour(oppositeColour, col))
	{
		score = 10000000 - 1;
		return score;
	}
	std::array<CheckerType, 3> straightDown = state.getAllStraightDown(move.index);
	if (areAllColour(oppositeColour, straightDown))
	{
		score = 10000000 - 1;
		return score;
	}
	if (state.isOnBoardDiagonal(move.index))
	{
		std::array<CheckerType, 3> diagonal = state.getAllOnSameBoardDiagonal(move.index);
		if (areAllColour(oppositeColour, diagonal))
		{
			score = 10000000 - 1;
			return score;
		}
	}
	if (state.isOnDiagonal(move.index))
	{
		std::array<CheckerType, 3> diagonal = state.getAllOnSameDiagonal(move.index);
		if (areAllColour(oppositeColour, diagonal))
		{
			score = 10000000 - 1;
			return score;
		}
		evaluateGroup(player, score, diagonal);
	}
	evaluateGroup(player, score, row);
	evaluateGroup(player, score, col);
	evaluateGroup(player, score, straightDown);
	if (state.isCorner(move.index))
	{
		score += 35;
	}
	if (player == CheckerType::Red)
	{
		score *= -1;
	}
	return score;
}

void Minimax::evaluateGroup(CheckerType player, int& score, std::array<CheckerType, 3> group)
{
	for (CheckerType type : group)
	{
		if (type == player)
		{
			score += 30;
		}
		else if (type == CheckerType::None)
		{
			score += 15;
		}
		else//opposite colour so we want to remove one from the score
		{
			score -= 10;
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
