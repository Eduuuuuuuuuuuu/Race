#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define MAX_DEACCELERATION -500.0f
#define TURN_DEGREES 30.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define FRICCION_COEFICIENT 0.01f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;
	bool CleanUp();
	void ActivateBoost();
	int lap = 0;
	bool meta = false;
public:
	VehicleInfo car;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float deacceleration = 0;
	float brake;
	float friccion;

	vec3 initialPosition;

	bool isBoosting;
};