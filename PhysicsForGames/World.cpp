#include "World.h"
#include <iostream>
#include <unordered_map>

#include "raylib.h"
#include "EnumUtils.h"

#include "PhysObject.h"



//function pointers

//Function pointer to a shape-shape collision detection function
using CollisionFunc = bool(*)(const Vector2&, const Shape&, const Vector2&, const Shape&);
//lookup table for pairs of shapes (and get its collision detection function back)
using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;
//Function pointer to a shape-shape depenetration function
using DepenetrationFunc = Vector2(*)(const Vector2&, const Shape&, const Vector2&, const Shape&, float&);
//Lookup table for pairs of shapes (and get its depenetration function back)
using DepenetrationMap = std::unordered_map<ShapeType, DepenetrationFunc>;
//local linkage (only available here

//lookup map for collision detection functions
CollisionMap CollisionCheckers;
//lookup map for depenetration functions
DepenetrationMap CollisionDepenetrators;

void World::Init()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second	

	//setup collision detection functions
	CollisionCheckers[ShapeType::CIRCLE | ShapeType::CIRCLE] = CheckCircleCircle;
	CollisionDepenetrators[ShapeType::CIRCLE | ShapeType::CIRCLE] = DepenetrateCircleCircle;

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

	for(auto const PObj : PhysObjects)
	{
		PObj->AddAccel({ 0.0f, GravityY });
		PObj->TickPhys(TargetFixedStep);
	}

	//check for collisions
	for (auto PObjA : PhysObjects)
	{
		for (auto PObjB : PhysObjects)
		{
			//skip self collision
			if (PObjA == PObjB) { continue; }
			if (PObjA->GetShape().Type == ShapeType::NONE || PObjB->GetShape().Type == ShapeType::NONE) { continue; }
			
			//reorder my pointers so the lower type always first
			std::shared_ptr<PhysObject> Lhs = PObjA;
			std::shared_ptr<PhysObject> Rhs = PObjB;

			//HACK: check the type and swap if necessary
			if(PObjA->GetShape().Type > PObjB->GetShape().Type)
			{
				Lhs = PObjB;
				Rhs = PObjA;
			}


			ShapeType PairType = Lhs->GetShape().Type | Rhs->GetShape().Type;
			bool bIsColliding = CollisionCheckers[PairType](Lhs->GetPosition(), Lhs->GetShape(), 
															Rhs->GetPosition(), Rhs->GetShape());
			if(bIsColliding)
			{
				float Pen = 0.0f;

				Vector2 Dir = CollisionDepenetrators[PairType](Lhs->GetPosition(), Lhs->GetShape(),
															   Rhs->GetPosition(), Rhs->GetShape(), Pen);
				
				ResolvePhysBodies(*Lhs, *Rhs, 1.0f, Dir, Pen);

				
				//TODO: we need to separate them
				//TODO: we also need them to bounce off each other
			}

		}
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