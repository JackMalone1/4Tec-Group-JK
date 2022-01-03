#include "Minimax.h"

Move Minimax::doMove(State& state)
{
	/*int bestScore = -std::numeric_limits<int>::max();
	Move bestMove;
	bestMove.index = -1;
	bestMove.score = bestScore;
	minimax function
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

	return bestMove;*/
	Move bestmove = getBestMove(state, CheckerType::Yellow);
	state.setPieceAtPosition(bestmove.index, CheckerType::Yellow);
	moves.clear();
	return bestmove;
}

Move Minimax::getBestMove(State& state, CheckerType player)
{
	//GameOver gameOver = state.checkVictory();

	//if (gameOver != GameOver::None)
	//{
	//	if (gameOver == GameOver::Tie)
	//	{
	//		return Move(0);
	//	}
	//	else if (gameOver == GameOver::Red && m_aiColour == CheckerType::Red)
	//	{
	//		return Move(10);
	//	}
	//	else if (gameOver == GameOver::Yellow && m_aiColour == CheckerType::Yellow)
	//	{
	//		return Move(10);
	//	}
	//	else //loss
	//	{
	//		return Move(-10);
	//	}
	//}
	//return Move();

	GameOver gameover = state.checkVictory();
	if (gameover == GameOver::Yellow)
	{
			return Move(10);
	}
	else if(gameover == GameOver::Red)	
	{
		return Move(-10);
	}
	else if (gameover == GameOver::Tie)
	{
		return Move(0);
	}

	/*for (int z = 0; z < 4; z++)
	{
		if (currentDepth >= MAX_DEPTH)
		{
			break;
		}
		for (int y = 0; y < 4; y++)
		{
			if (currentDepth >= MAX_DEPTH)
			{
				break;
			}
			for (int x = 0; x < 4; x++)
			{*/
	std::vector<int> availableMoves = state.getLegalSpotsToPlay();
	for (int availableMove : availableMoves)
	{
		Move move;
		move.index = availableMove;
		if (state.getPieceAtPosition(availableMove) == CheckerType::None)
		{

			//move.x = x;
			//move.y = y;
			//move.z = z;
			//move.index = (x * 4 + y) + (z * 16);

			state.setPieceAtPosition(availableMove, player);
			if (player == CheckerType::Yellow) //ai
			{
				move.score = evaluate(state, CheckerType::Red, move);
				//move.score = getBestMove(state, CheckerType::Red).score;
			}
			else
			{
				move.score = evaluate(state, CheckerType::Yellow, move);
				//move.score = getBestMove(state, CheckerType::Yellow).score;
			}
			moves.push_back(move);
			state.setPieceAtPosition(availableMove, CheckerType::None);
		}
	}
	int bestMove = 0;
	if (player == CheckerType::Yellow)
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
	return moves[bestMove];
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
