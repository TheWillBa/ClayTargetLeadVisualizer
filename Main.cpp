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




Next Steps:
  -> Approximation methods for lead of any type
  -> Expanding to 3D linear and arbitrary targets

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
		if (GetKey(olc::Key::LEFT).bHeld || GetKey(olc::Key::A).bHeld) xOffset += cameraSpeed;
		if (GetKey(olc::Key::RIGHT).bHeld || GetKey(olc::Key::D).bHeld) xOffset -= cameraSpeed;
		if (GetKey(olc::Key::UP).bHeld || GetKey(olc::Key::W).bHeld) yOffset += cameraSpeed;
		if (GetKey(olc::Key::DOWN).bHeld || GetKey(olc::Key::S).bHeld) yOffset -= cameraSpeed;

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

// Override base class with your custom functionality
class FirstPersonTargetVisualizer : public olc::PixelGameEngine
{
	// TODO: allows for the viewer to move the top down camera to move around the world

private:
	LinearTargetStation* station;
	const double TARGET_MAX_HEIGHT = 600;
	const double TARGET_MAX_WIDTH = 1000;


	Vector2D facing;

	float fov = 120;
	float rotation = 3.141592 / 2;
	float rotationSpeed = 4.0f;

	float targetHeight;
	float targetDecsentSpeed = 12.0f;


public:
	FirstPersonTargetVisualizer()
	{
		// Name you application
		sAppName = "First Person Target Visualization";
	}

public:
	bool OnUserCreate() override
	{
		targetHeight = ScreenHeight() / 2;
		LinearTarget t(-20, 0, 40, 0);
		Shooter s(0, -30, 200);

		station = new LinearTargetStation(t, s);


		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Be able to control time flow instead of using fElapsed time?

		if (GetMouseWheel() > 0) rotation -= rotationSpeed * fElapsedTime;
		if (GetMouseWheel() < 0) rotation += rotationSpeed * fElapsedTime;


		Clear(olc::Pixel(154, 203, 255));

		facing = Vector2D(cos(rotation), sin(rotation));
		//targetHeight += fElapsedTime * targetDecsentSpeed;;

		station->tick(fElapsedTime);
		drawStation(station);

		float bottomScreenPercentMax = 0.25;
		FillRect(0, (1 - bottomScreenPercentMax) * ScreenHeight(), ScreenWidth(), ScreenHeight() * bottomScreenPercentMax, olc::DARK_GREEN);

		/*
		Draws gradient
		float bottomScreenPercentMax = 0.25;
		int steps = 10;
		for(float i = bottomScreenPercentMax; i > 0; i -= bottomScreenPercentMax/steps )
			FillRect(0, (1 - i) * ScreenHeight(), ScreenWidth(), ScreenHeight() * i, olc::Pixel(0, (1-i) * 255, 0));
			*/


		
		return true;
	}

	bool OnUserDestroy() override
	{
		delete station;
		return true;
	}

	void drawStation(LinearTargetStation * station) {
		LinearTarget t = station->getTarget();
		Shooter s = station->getShooter();

		DrawTargetWithPerspective(t.currentPosition(), s.getPosition(), olc::Pixel(255, 94, 19));
		DrawTargetWithPerspective(station->currentLeadPosition(), s.getPosition(), olc::GREEN);
	}

	void DrawTargetWithPerspective(const Vector2D& tPosition, const Vector2D& cameraPosition, const olc::Pixel& color) {
		Vector2D shooterToTarget = tPosition - cameraPosition;


		double angleOffFromCenter = acos(shooterToTarget.cosAngleBetween(facing));

		// Currently can see in front and behind targets
		if (angleOffFromCenter > fov / 2) return; // out of view

		double distanceToTarget = shooterToTarget.magnitude();
		double d = distanceToTarget * tan(angleOffFromCenter);

		double perpDistance = shooterToTarget * facing;
		double p = perpDistance * tan(fov / 2);

		double percentFromCenter = d / p;

		int side;
		if (shooterToTarget.polarAngle() > facing.polarAngle()) side = -1;
		else side = 1;

		double xPos = ScreenWidth() / 2 + side * (ScreenWidth() / 2) * percentFromCenter;

		double distance = cameraPosition.distance(tPosition);
		double height = TARGET_MAX_HEIGHT * (1 / distance);
		double width = TARGET_MAX_WIDTH * (1 / distance);

		FillRect(xPos - width / 2, targetHeight - height / 2, width, height, color);
	}



};

int main()
{
	FirstPersonTargetVisualizer demo;
	if (demo.Construct(600, 600, 1, 1))
		demo.Start();
	return 0;
}