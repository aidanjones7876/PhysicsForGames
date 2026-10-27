#include "PhysObject.h"

#include <raymath.h>

void PhysObject::TickPhys(float Delta)
{
	//integrate impulses into velocity
	Velocity += PendingImpulses;
	PendingImpulses = {}; //zero out after applying


	//integrate forces into velocity
	Velocity += PendingForces * Delta;
		PendingForces = {}; //zero out after applying
	//integrate velocity into pos
	Position += Velocity * Delta;
}

void PhysObject::Draw()
{
	Vector2 XRay = Position + Vector2{ 50, 0 };
	Vector2 YRay = Position + Vector2{ 0, 50 };

	DrawLineV(Position, XRay, RED);
	DrawLineV(Position, YRay, GREEN);
}

void PhysObject::SetPosition(const Vector2 NewPosition)
{

	Position = NewPosition;
}

Vector2 PhysObject::GetPosition() const
{
	return Position;
}

void PhysObject::SetVelocity(const Vector2 NewVelocity)
{
	Velocity = NewVelocity;
}

Vector2 PhysObject::GetVelocity() const
{
	return Velocity;
}
void PhysObject::SetMass(float NewMass)
{
	Mass = NewMass;
}
void PhysObject::AddForce(const Vector2& Force)
{
	PendingForces += Force / Mass;
}

void PhysObject::AddAccel(const Vector2& Accel)
{
	PendingForces += Accel;
}

void PhysObject::AddImpulse(const Vector2& Impulse)
{
	PendingImpulses += Impulse / Mass;
}

void PhysObject::AddVelocityChange(const Vector2& VelChange)
{
}
