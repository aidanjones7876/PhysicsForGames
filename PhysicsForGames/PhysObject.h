#pragma once

#include <raylib.h>
#include <raymath.h>

#include "Shapes.h"

//A -glm
//B -Raylib



class PhysObject
{
private:
	Vector2 Position;
	Vector2 Velocity;

	float Mass = 1.0f;

	Shape Collider;

	Vector2 PendingForces = {};
	Vector2 PendingImpulses = {};


public:
	void TickPhys(float Delta);

	void Draw();

	void SetPosition(const Vector2 NewPosition);
	Vector2 GetPosition() const;

	void SetVelocity(const Vector2 NewVelocity);
	Vector2 GetVelocity() const;

	void SetMass(float NewMass);
	float GetMass() const { return Mass; };

	void SetCircle(float Radius);
	const Shape& GetShape() const;

	void AddForce(const Vector2& Force);
	void AddAccel(const Vector2& Accel);
	void AddImpulse(const Vector2& Impulse);
	void AddVelocityChange(const Vector2& VelChange);

	
};

float ResolveCollision(const Vector2& VelA, float MassA,
					   const Vector2& VelB, float MassB, float Elasticity, const Vector2& Normal);

void ResolvePhysBodies(PhysObject& Lhs, PhysObject& Rhs, float Elasticity, const Vector2& Normal, float Pen);

