#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 64; i++)
	{
		//std::cout << i << ": " << (i % 16) /*% 4*/ << std::endl;
		int boardNumber = i / 16;
		int diagonalCheck = (boardNumber > 0) ? i % 16 : i;
		if (diagonalCheck % 5 == 0)
		{
			std::cout << "Diagonal found on board: " << boardNumber << " for index: " << i << std::endl;
		}
		if (diagonalCheck % 3 == 0 && diagonalCheck % 5 != 0)
		{
			std::cout << "Other Diagonal found on board: " << boardNumber << " for index: " << i << std::endl;
		}
	}
	Game game;
	game.run();

	return 1; // success
}