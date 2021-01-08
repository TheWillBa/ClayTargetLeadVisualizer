#pragma once

#include "LinearTarget.h";
#include "Shooter.h"

class LinearTargetStation
{
private:
	LinearTarget target;
	Shooter shooter;

public:
	LinearTargetStation(LinearTarget target, const Shooter shooter) : target(target), shooter(shooter) {};

	const LinearTarget& getTarget() { return target; };
	Shooter& getShooter() { return shooter; };

	void tick(double dtime) {
		target.update(dtime);
	}

	Vector2D currentLeadPosition() {
		Vector2D shooterPos = shooter.getPosition();
		Vector2D targetPos = target.currentPosition();
		Vector2D targetVel = target.getVelocity();

		double D = shooterPos.distance(targetPos);
		Vector2D shooterToTarget = shooterPos - targetPos;
		double cosa = shooterPos.cosAngleBetween(target.getVelocity());

		double targetVelocityMag = target.getVelocityMagitude();
		double shotVelocityMag = shooter.getShotSpeed();

		double a = (shotVelocityMag * shotVelocityMag) - (targetVelocityMag * targetVelocityMag);
		double b = 2 * D * targetVelocityMag * cosa;
		double c = -D * D;

		// Pick between the two solutions?
		double timePassed = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

		return target.position(target.time() + timePassed);
	}


};

