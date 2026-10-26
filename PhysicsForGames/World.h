#pragma once

class World
{
public:
	float TargetFixedStep = 1.0f / 30.0f;

private:
	float AccumulatedFixedTime = 0.0f;

public:
	void Init();
	void Tick();
	void TickFixed();
	void Draw();
	void Exit();


	//@brief Returns true if the window should close
	//@return true if the shutdown is requested, false otherwise
	bool ShouldClose() const;


	//@brief indicates we are due for running TickFixed()
	//@return True if we should call TickFixed() this frame, false otherwise
	bool ShouldTickFixed() const
	{
		return AccumulatedFixedTime >= TargetFixedStep;
	}


protected:
	void virtual OnInit() {}
	void virtual OnTick() {}
	void virtual OnTickFixed() {}
	void virtual OnDraw() {}
	void virtual OnExit() {}

private:


};
