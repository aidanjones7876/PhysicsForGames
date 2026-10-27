#include "World.h"

#include "raylib.h"

#include "PhysObject.h"

void World::Init()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second	


	OnInit();
}

void World::Tick()
{
	//incrementing the fixed tick timer
	AccumulatedFixedTime += GetFrameTime();

	//call our tick
	OnTick();
}

void World::TickFixed()
{
	AccumulatedFixedTime -= TargetFixedStep;

	for(auto Pobj : PhysObjects)
	{
		Pobj->TickPhys(TargetFixedStep);
	}

	OnTickFixed();
}

void World::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	for (auto const PObj : PhysObjects)
	{
		PObj->Draw();
	}

	OnDraw();

	EndDrawing();
}

void World::Exit()
{
	OnExit();

	CloseWindow();        // Close window and OpenGL context
}

bool World::ShouldClose() const
{
	return WindowShouldClose();
}

std::weak_ptr<PhysObject> World::SpawnPhysObject()
{
	PhysObjects.emplace_back(std::make_shared<PhysObject>());

	return PhysObjects[PhysObjects.size() - 1];
}