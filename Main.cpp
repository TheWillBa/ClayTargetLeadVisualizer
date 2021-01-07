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
		sAppName = "Lead Visualization";
	}

public:
	bool OnUserCreate() override
	{

		t = new Target(0, ScreenHeight() / 2);
		//olc::Pixel p(olc::BLACK);
		//prevColor = p;
	
		std::vector path = flightpath(*t, 0, 1500, 0.005);
		drawFlightpathCircle(path);
		
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Vector2D oldPos = t->position();
		t->update(fElapsedTime);
		Vector2D pos = t->position();

		FillCircle(oldPos.X(), oldPos.Y(), 10, olc::RED);
		FillCircle(pos.X(), pos.Y(), 10);




		return true;
		
	}

	bool OnUserDestroy() override
	{
		// Called when window is closed
		delete t;
		return true;
	}

	/*
	Draws a flight path by drawing a circle at each point on it
	*/
	void drawFlightpathCircle(const std::vector<Vector2D>& path) {
		for (int i = 0; i < path.size(); ++i) {
			Vector2D cpos = path[i];
			FillCircle(cpos.X(), cpos.Y(), 10, olc::RED);
		}
	}

	/*
	Draws a flight path by connecting each point with a line
	*/
	void drawFlightpathLine(const std::vector<Vector2D>& path) {
		for (int i = 0; i < path.size() - 1; ++i) {
			Vector2D cpos = path[i];
			Vector2D npos = path[i + 1];
			DrawLine(cpos.X(), cpos.Y(), npos.X(), npos.Y(), olc::RED);
		}
	}
};

int main()
{
	LeadVisualizer demo;
	if (demo.Construct(600, 600, 1, 1))
		demo.Start();
	return 0;
}