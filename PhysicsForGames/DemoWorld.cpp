#include "DemoWorld.h"

#include "PhysObject.h"

#include <iostream>

void DemoWorld::OnInit()
{
	World::OnInit();
	
	TestPhysObject = SpawnPhysObject();

	if(auto TestPhysObjectReal = TestPhysObject.lock())
	{
		TestPhysObjectReal->SetPosition({ 250, 250 });
		TestPhysObjectReal->SetVelocity({ 50, 0 });
		TestPhysObjectReal->SetMass(2.0f);
	}

}

void DemoWorld::OnTick()
{
	World::OnTick();
	//std::cout << "Tick" << std::endl;
}

void DemoWorld::OnTickFixed()
{
	World::OnTickFixed();

	if (auto TestPhysObjectReal = TestPhysObject.lock())
	{
		TestPhysObjectReal->AddAccel({ 0, 9.0f });
		TestPhysObjectReal->AddForce({ -50, 0.0f });
	}

	//std::cout << "TickFixed" << std::endl;
}