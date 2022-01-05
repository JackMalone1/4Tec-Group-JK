#pragma once

const int G_WINDOW_WIDTH = 900;
const int G_WINDOW_HEIGHT = 980;
const int G_CHECKER_COUNT = 21;

const int G_GRID_WIDTH = 208;

static constexpr size_t BOARD_SIZE = 16;
static constexpr size_t NUM_BOARDS = 4;
static constexpr size_t ROW_SIZE = 4;
static constexpr size_t COL_SIZE = 4;

enum class CheckerType
{
	None = 0,
	Yellow,
	Red
};