#include "PhysObject.h"
#include <cassert>
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

	switch (Collider.Type)
	{
	case ShapeType::NONE:
		DrawPixelV(Position, BLACK);
		break;
	case ShapeType::CIRCLE:
		DrawCircleLinesV(Position, Collider.CircleData.Radius, PURPLE);
		break;
	default:
		assert(false && "This should not happen");
	}
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

void PhysObject::SetCircle(float Radius)
{
	Collider.Type = ShapeType::CIRCLE;
	Collider.CircleData.Radius = Radius;
}

const Shape& PhysObject::GetShape() const
{
	return Collider;
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

float ResolveCollision(const Vector2& VelA, float MassA, const Vector2& VelB, float MassB, float Elasticity, const Vector2& Normal)
{
	//calculate relative velocity
	Vector2 RelativeVel = VelA - VelB;

	//calculate the impulse magnitude
	float ImpulseMag = Vector2DotProduct(-(1.f + Elasticity) * RelativeVel, Normal) /
					   Vector2DotProduct(Normal, Normal * (1.f / MassA + 1.f / MassB));

	//return how strong these things should fly off
	return ImpulseMag;
}

void ResolvePhysBodies(PhysObject& Lhs, PhysObject& Rhs, float Elasticity, const Vector2& Normal, float Pen)
{
	//Depenetrate the objects
	Pen /= 2.0f;

	Pen += 0.001f;
	
	Vector2 LhsNewPosition = Lhs.GetPosition() + Normal * Pen;
	Vector2 RhsNewPosition = Rhs.GetPosition() - Normal * Pen;

	Lhs.SetPosition(LhsNewPosition);
	Rhs.SetPosition(RhsNewPosition);

	//Calculate (and apply) the resolution impulse
	float ImpulseMag = ResolveCollision(Lhs.GetVelocity(), Lhs.GetMass(), Rhs.GetVelocity(), Rhs.GetMass(), Elasticity, Normal);

	Vector2 Impulse = ImpulseMag * Normal;
	Lhs.AddImpulse(Impulse);
	Rhs.AddImpulse(Impulse * -1.f);
}
