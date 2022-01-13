#pragma once

/// <summary>
/// the width and height of the window
/// </summary>
const int G_WINDOW_WIDTH = 900;
const int G_WINDOW_HEIGHT = 980;

/// <summary>
/// width of the grids used to display the board
/// </summary>
const int G_GRID_WIDTH = 208;
/// <summary>
/// used to store how big each board is, how many boards we have and the size of the rows and cols
/// </summary>
static constexpr size_t BOARD_SIZE = 16;
static constexpr size_t NUM_BOARDS = 4;
static constexpr size_t ROW_SIZE = 4;
static constexpr size_t COL_SIZE = 4;
/// <summary>
/// The different types of checkers that can be placed on the board
/// </summary>
enum class CheckerType
{
	None = 0,
	Yellow,
	Red
};