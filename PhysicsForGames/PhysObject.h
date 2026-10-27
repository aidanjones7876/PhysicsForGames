#pragma once

#include <raylib.h>
#include <raymath.h>

//A -glm
//B -Raylib

class PhysObject
{
private:
	Vector2 Position;
	Vector2 Velocity;

	float Mass = 1.0f;

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

	void AddForce(const Vector2& Force);
	void AddAccel(const Vector2& Accel);
	void AddImpulse(const Vector2& Impulse);
	void AddVelocityChange(const Vector2& VelChange);

};
