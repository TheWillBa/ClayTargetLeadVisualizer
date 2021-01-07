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
#include "LinearTargetStation.h"

// Override base class with your custom functionality
class LeadVisualizer : public olc::PixelGameEngine
{
	// TODO: allows for the viewer to move the top down camera to move around the world

private:
	LinearTargetStation* station;
	float xOffset = 0;
	float yOffset = 0;
	float cameraSpeed = 0.5f;


public:
	LeadVisualizer()
	{
		// Name you application
		sAppName = "Lead Visualization";
	}

public:
	bool OnUserCreate() override
	{

		LinearTarget t(0, 30, 70, 0);
		Shooter s(ScreenWidth() / 2, ScreenHeight() / 2, 300);

		station = new LinearTargetStation(t, s);

		
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::LEFT).bHeld) xOffset += cameraSpeed;
		if (GetKey(olc::Key::RIGHT).bHeld) xOffset -= cameraSpeed;
		if (GetKey(olc::Key::UP).bHeld) yOffset += cameraSpeed;
		if (GetKey(olc::Key::DOWN).bHeld) yOffset -= cameraSpeed;

		if (GetMouseWheel() > 0) cameraSpeed += 0.5f;
		if (GetMouseWheel() < 0) cameraSpeed -= 0.5f;
		if (cameraSpeed < 0) cameraSpeed = 0;


		LinearTarget t = station->getTarget();
		Clear(olc::Pixel(154, 203, 255));
		drawFlightpathLine(t.flightpath(0, 1500, 1));

		station->tick(fElapsedTime);

		Vector2D pos = worldToScreenCoords(t.currentPosition());
		Vector2D leadPos = worldToScreenCoords(station->currentLeadPosition());
		Vector2D shooterPos = worldToScreenCoords(station->getShooter().getPosition());

		DrawLine(shooterPos.X(), shooterPos.Y(), leadPos.X(), leadPos.Y(), olc::MAGENTA);
		FillCircle(pos.X(), pos.Y(), 10, olc::Pixel(255,94,19));
		FillCircle(leadPos.X(), leadPos.Y(), 10, olc::GREEN);
		FillCircle(shooterPos.X(), shooterPos.Y(), 10, olc::DARK_GREY);



		return true;		
	}

	bool OnUserDestroy() override
	{
		// Called when window is closed
		delete station;
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
			Vector2D cpos = worldToScreenCoords(path[i]);
			Vector2D npos = worldToScreenCoords(path[i + 1]);
			DrawLine(cpos.X(), cpos.Y(), npos.X(), npos.Y(), olc::RED);
		}
	}

	Vector2D worldToScreenCoords(const Vector2D& worldCoords) {
		// TODO implement this to map the world coords centered at 0,0 to screen coords
		// and account for camera motion
		return worldCoords + Vector2D(xOffset, yOffset);
	}

};

int main()
{
	LeadVisualizer demo;
	if (demo.Construct(600, 600, 1, 1))
		demo.Start();
	return 0;
}