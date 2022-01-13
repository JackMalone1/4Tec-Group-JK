#include "Minimax.h"

/// <summary>
/// 
/// </summary>
/// <param name="state"></param>
/// <returns></returns>
Move Minimax::doMove(State state)
{
	Move move;
	move.index = -1;
	move.depth = 100;
	move.score = -10000000000;
	CheckerType player = CheckerType::Yellow;
	int currentDepth = 0;
	int alpha = -10000000;
	int beta = 10000000;
	Move bestmove = getBestMove(state, player, currentDepth, move, alpha, beta);
	state.setPieceAtPosition(bestmove.index, CheckerType::Yellow);
	moves.clear();
	return bestmove;
}

/// <summary>
/// 
/// </summary>
/// <param name="state"></param>
/// <param name="player"></param>
/// <param name="depth"></param>
/// <param name="move"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <returns></returns>
Move Minimax::getBestMove(State& state, CheckerType& player, int depth, Move& move, int alpha, int beta)
{
	GameOver gameover = state.checkVictory();
	if (gameover == GameOver::Yellow && player == CheckerType::Yellow || gameover == GameOver::Red && CheckerType::Red == player)
	{
		move.score = 10000000;
		return move;
	}
	else if (gameover == GameOver::Yellow && player != CheckerType::Yellow || gameover == GameOver::Red && CheckerType::Red != player)
	{
		move.score = -10000000;
		return move;
	}
	else if (gameover == GameOver::Tie)
	{
		move.score = 0;
		return move;
	}
	if (depth >= MAX_DEPTH)
	{
		Move newMove;
		newMove.index = move.index;
		move.score = evaluate(state, player, move);
		CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
		move.score += -evaluate(state, oppositeColour, move);
		if (oppositeColour == CheckerType::Red) move.score *= -1;
		move.depth = depth;
		return move;
	}

	std::vector<int> availableMoves = state.getLegalSpotsToPlay();
	for (int availableMove : availableMoves)
	{
		Move move(0);
		move.index = availableMove;
		if (state.getPieceAtPosition(availableMove) == CheckerType::None)
		{
			state.setPieceAtPosition(availableMove, player);
			if (player == CheckerType::Red) //maximiser
			{
				CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
				int score = getBestMove(state, oppositeColour, depth + 1, move, alpha, beta).score;
				alpha = std::max(alpha, score);
				if (alpha >= beta)
				{
					move.score = alpha;
					move.depth = depth;
					moves.push_back(move);
					state.setPieceAtPosition(availableMove, CheckerType::None);
					return move;
				}
				move.score = score;
			}
			else//minimiser
			{
				CheckerType oppositeColour = (player == CheckerType::Red) ? CheckerType::Yellow : CheckerType::Red;
				int score = getBestMove(state, oppositeColour, depth + 1, move, alpha, beta).score;
				beta = std::min(beta, score);
				
				if (alpha >= beta)
				{
					move.score = beta;
					move.depth = depth;
					moves.push_back(move);
					state.setPieceAtPosition(availableMove, CheckerType::None);
					return move;
				}
				move.score = score;
			}
			move.depth = depth;
			moves.push_back(move);
			state.setPieceAtPosition(availableMove, CheckerType::None);
		}
	}
	int bestMove = 0;
	int bestDepth = MAX_DEPTH + 1;
	
	if (player == CheckerType::Red)
	{
		int bestScore = -10000000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score > bestScore && moves[i].depth <= bestDepth)
			{
				bestMove = i;
				bestScore = moves[i].score;
				bestDepth = moves[i].depth;
			}
		}
	}
	else
	{
		int bestScore = 10000000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score < bestScore && moves[i].depth <= bestDepth)
			{
				bestMove = i;
				bestScore = moves[i].score;
				bestDepth = moves[i].depth;
			}
		}
	}
	return moves[bestMove];
}

/// <summary>
/// 
/// </summary>
/// <param name="state"></param>
/// <param name="player"></param>
/// <param name="move"></param>
/// <returns></returns>
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

/// <summary>
/// 
/// </summary>
/// <param name="player"></param>
/// <param name="score"></param>
/// <param name="group"></param>
void Minimax::evaluateGroup(CheckerType& player, int score, std::array<CheckerType, 3>& group)
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

/// <summary>
/// 
/// </summary>
/// <param name="colour"></param>
/// <param name="arr"></param>
/// <returns></returns>
bool Minimax::areAllColour(CheckerType& colour, std::array<CheckerType, 3>& arr)
{
	for (CheckerType type : arr)
	{
		if (type != colour) return false;
	}
	return true;
}

void Minimax::SetMaxDepth(int t_maxDepth)
{
	MAX_DEPTH = t_maxDepth;
}