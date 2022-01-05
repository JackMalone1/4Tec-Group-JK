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
	for (int i = 0; i < 64; i++)
	{
		//std::cout << (i >= 4) ? i % 4 : i;
		int boardNumber = (i / 4);
		int columnNumber = (i % 4);
		std::cout << std::endl;
		std::cout << boardNumber << " " << columnNumber << std::endl;
	}
	srand(static_cast<unsigned>(time(nullptr)));
	Game game;
	game.run();
	return 1; // success
}