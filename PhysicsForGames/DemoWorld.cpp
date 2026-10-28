#include "DemoWorld.h"

#include "PhysObject.h"
#include <cmath>
#include <iostream>


float Wrap(float val, float Limit) 
{
	return std::fmod(std::fmod(val, Limit) + Limit, Limit);
}

void DemoWorld::OnInit()
{
	World::OnInit();
	
	TestPhysObject = SpawnPhysObject();

	if(auto TestPhysObjectReal = TestPhysObject.lock())
	{
		TestPhysObjectReal->SetMass(1.0f);

		TestPhysObjectReal->SetPosition({ 50, 100 });
		TestPhysObjectReal->AddImpulse({ 100, 0 });

		TestPhysObjectReal->SetCircle(20.0f);
		
	}

	auto AnotherObject = SpawnPhysObject();
	if(auto AnotherObjectReal = AnotherObject.lock())
	{
		AnotherObjectReal->SetMass(1.0f);

		AnotherObjectReal->SetPosition({ 700, 90 });
		AnotherObjectReal->AddImpulse({ -100, 0 });

		AnotherObjectReal->SetCircle(20.0f);
		
	}
	GravityY = 0.0f;
}

void DemoWorld::OnTick()
{
	World::OnTick();
	
	/*if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (auto TestPhysObjectReal = TestPhysObject.lock())
		{
			TestPhysObjectReal->SetPosition(GetMousePosition());
		}
	}
	*/
}

void DemoWorld::OnTickFixed()
{
	World::OnTickFixed();
	
	if(bUseScreenWrap)
	{
		for (auto PObj : GetPhysObjects())
		{
			Vector2 NewPosition = PObj->GetPosition();
			NewPosition.x = Wrap(NewPosition.x, (float)GetScreenWidth());
			NewPosition.y = Wrap(NewPosition.y, (float)GetScreenHeight());
			PObj->SetPosition(NewPosition);
		}
	}

	//std::cout << "TickFixed" << std::endl;
}