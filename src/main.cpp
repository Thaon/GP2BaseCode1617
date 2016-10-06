#include "MyGame.h"
#undef main

int main(int argc, char * arg[])
{
	std::unique_ptr<MyGame> pGame(new MyGame);

	pGame->Init(argc,arg);
	pGame->Run();

	return 0;
}
