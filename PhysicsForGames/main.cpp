#include "DemoWorld.h"

#include <raylib.h>
#include <raymath.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	World* Game = new DemoWorld();


	Game->Init();

	//Main Game Loop
	while (!Game->ShouldClose())
	{
		Game->Tick();

		while(Game->ShouldTickFixed())
		{
			Game->TickFixed();
		}

		Game->Draw();
	}

	Game->Exit();

	delete Game;

    return 0;
}