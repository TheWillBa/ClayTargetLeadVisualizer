// ClayTargetLeadVisualizer.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
Let's start simple with a 2D topdown view of a flatland.

We will draw the 'target' flight path as time passes in the 2D plane
(There will be no up or down to start, so no 'height')

We will draw the shooter in relation to the target, and his shot path to the target with the calculated lead

________________
|  s           | 
|   \          | 
|    **        | 
|   T  *       | 
|  *    *      | 
________________

s = shooter location
* = projected flight path over time
T = the current location of the target
\ = the shot path

Center the world at (0,0)?

*/


#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include "Target.h"

// Override base class with your custom functionality
class LeadVisualizer : public olc::PixelGameEngine
{
private:
	Target* t;


public:
	LeadVisualizer()
	{
		// Name you application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{

		t = new Target(0, ScreenHeight() / 2);
		
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		
		t->update(fElapsedTime);
		Vector2D pos = t->position();
		Draw(pos.X(), pos.Y());

		return true;
		
	}

	bool OnUserDestroy() override
	{
		// Called when window is closed
		delete t;
		return true;
	}
};

int main()
{
	LeadVisualizer demo;
	if (demo.Construct(50, 50, 4, 4))
		demo.Start();
	return 0;
}