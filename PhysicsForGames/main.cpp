#include <memory>

#include "DemoWorld.h"


#include <raylib.h>
#include <raymath.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	auto Game = std::make_unique<DemoWorld>();


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


    return 0;
}