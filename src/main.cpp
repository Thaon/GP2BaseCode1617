#include "MyGame.h"
#undef main

int main(int argc, char * arg[])
{
	unique_ptr<MyGame> pGame(new MyGame);

	pGame->init(argc,arg);
	pGame->run();

	return 0;
}
