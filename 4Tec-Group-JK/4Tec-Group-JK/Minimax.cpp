#include "Minimax.h"

Move Minimax::doMove(State state)
{
	//int bestScore = -std::numeric_limits<int>::max();
	//Move bestMove;
	//bestMove.index = -1;
	//bestMove.score = bestScore;
	////minimax function
	//std::vector<int> availableMoves = state.getLegalSpotsToPlay();
	//for (int availableMove : availableMoves)
	//{
	//	Move move;
	//	move.index = availableMove;
	//	move.score = evaluate(state, CheckerType::Yellow, move);
	//	if (move.score > bestMove.score)
	//	{
	//		bestMove.score = move.score;
	//		bestMove.index = move.index;
	//	}
	//}

	//return bestMove;
	Move bestmove = getBestMove(state, CheckerType::Yellow, 0, Move());
	state.setPieceAtPosition(bestmove.index, CheckerType::Yellow);
	moves.clear();
	return bestmove;
}

Move Minimax::getBestMove(State& state, CheckerType player, int depth, Move move)
{

	GameOver gameover = state.checkVictory();
	if (gameover == GameOver::Yellow && player == CheckerType::Yellow || gameover == GameOver::Red && CheckerType::Red == player)
	{
			return Move(10000000);
	}
	else if(gameover == GameOver::Yellow && player != CheckerType::Yellow || gameover == GameOver::Red && CheckerType::Red != player)
	{
		return Move(-10000000);
	}
	else if (gameover == GameOver::Tie)
	{
		return Move(0);
	}
	if (depth >= MAX_DEPTH)
	{
		Move newMove;
		newMove.index = move.index;
		newMove.score = evaluate(state, player, move);
		CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
		newMove.score += -evaluate(state, oppositeColour, move);
		//if (player == CheckerType::Yellow) newMove.score *= -1;
		return newMove;
	}

	std::vector<int> availableMoves = state.getLegalSpotsToPlay();
	for (int availableMove : availableMoves)
	{
		Move move(0);
		move.index = availableMove;
		if (state.getPieceAtPosition(availableMove) == CheckerType::None)
		{
			state.setPieceAtPosition(availableMove, player);
			if (player == CheckerType::Red) //ai
			{
				//move.score = evaluate(state, player, move);
				//if (move.score == 10000000 - 1) return move;
				move.score = getBestMove(state, CheckerType::Yellow, depth + 1, move).score;

			}
			else
			{

				//move.score = evaluate(state, player, move);
				//if (move.score == 10000000 - 1) return move;
				move.score = getBestMove(state, CheckerType::Red, depth + 1, move).score;
			}
			moves.push_back(move);
			state.setPieceAtPosition(availableMove, CheckerType::None);
		}
	}
	int bestMove = 0;
	if (player == CheckerType::Red)
	{
		int bestScore = -10000000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score >= bestScore)
			{
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else
	{
		int bestScore = 10000000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score <= bestScore)
			{
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	//std::cout << moves[bestMove].score << std::endl;
	return moves[bestMove];
}

int Minimax::evaluate(State& state, CheckerType player, Move& move)
{
	CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
	int score = 0;
	if ((state.checkVictory() == GameOver::Red && player == CheckerType::Red) || (state.checkVictory() == GameOver::Yellow && player == CheckerType::Yellow))
	{
		score = 10000000 - 1;
		return score;
	}
	if ((state.checkVictory() == GameOver::Red && oppositeColour == CheckerType::Red) || (state.checkVictory() == GameOver::Yellow && oppositeColour == CheckerType::Yellow))
	{
		score = -10000000 + 1;
		return score;
	}
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
