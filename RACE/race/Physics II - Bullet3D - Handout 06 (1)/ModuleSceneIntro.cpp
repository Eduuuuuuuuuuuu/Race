#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 10.0f, -20.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	 /*Create sensor cube (will trigger with car)*/

	

	
	

	sensor_cube = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->SetPos(0, 3, 0);
	

	
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	
	p.Render();

	Cube a(10, 2, 4);

	a.SetPos(-5, 1, 0);
	a.SetRotation(20, { 0, 0, 1 });
	a.color = { 200,200,200 };
	a.Render();

	for (int i = 0; i < 5; i++)
	{
		Cube c(10, 2, 4);
		
		c.SetPos(i * 5, 1, 0);
		c.color = { 200,200,200 };
		c.Render();
	}
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

