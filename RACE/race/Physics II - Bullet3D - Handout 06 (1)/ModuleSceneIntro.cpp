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



	meta = App->physics->AddBody(Cube(5, 5, 20), 0.0);
	meta->SetAsSensor(true);
	meta->SetPos(30, 3, 6);

	sensor_cube1 = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube1->SetAsSensor(true);
	sensor_cube1->SetPos(0, 3, 6);

	sensor_cube2 = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube2->SetAsSensor(true);
	sensor_cube2->SetPos(10, 3, 6);

	sensor_cube3 = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube3->SetAsSensor(true);
	sensor_cube3->SetPos(20, 3, 6);

	d.Scale(5, 5, 5);
	d.SetPos(0, 3, 6);

	aa.Scale(5, 5, 5);

	aa.SetPos(10, 3, 6);

	aaa.Scale(5, 5, 5);

	aaa.SetPos(20, 3, 6);

	metaColor.Scale(5, 5, 20);
	metaColor.SetPos(30, 3, 6);

	cube3 = App->physics->AddBody(Cube(30, 5, 8), 0.0);
	cube3->SetPos(15, 1, 0);
	cube3 = App->physics->AddBody(Cube(30, 5, 8), 0.0);
	cube3->SetPos(42, 1, 2);
	cube3 = App->physics->AddBody(Cube(8, 5, 30), 0.0);
	cube3->SetPos(53, 1, 20);
	cube3 = App->physics->AddBody(Cube(15, 5, 8), 0.0);
	cube3->SetPos(42, 1, 28);
	cube3 = App->physics->AddBody(Cube(8, 5, 20), 0.0);
	cube3->SetPos(32, 1, 34);
	cube3 = App->physics->AddBody(Cube(18, 5, 8), 0.0);
	cube3->SetPos(25, 1, 42);
	cube3 = App->physics->AddBody(Cube(8, 4, 15), 0.0);
	cube3->SetPos(17, 1, 30);
	cube3 = App->physics->AddBody(Cube(15, 3, 8), 0.0);
	cube3->SetPos(10, 1, 25);
	cube3 = App->physics->AddBody(Cube(8, 3, 20), 0.0);
	cube3->SetPos(5, 1, 38);
	cube3 = App->physics->AddBody(Cube(40, 3, 8), 0.0);
	cube3->SetPos(-10, 1, 52);
	cube3 = App->physics->AddBody(Cube(8, 3, 40), 0.0);
	cube3->SetPos(-30, 1, 37);


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
	//plano 
	Plane p(0, 1, 0, 0);
	p.axis = true;

	p.Render();

	Cube a(10, 2, 4);

	//rampa para subir
	a.SetPos(-5, 1, 0);
	a.SetRotation(20, { 0, 0, 1 });
	a.color = { 200,200,200 };
	a.Render();

	//path
	for (int i = 0; i < 5; i++)
	{
		Cube c(10, 2, 8);

		c.SetPos(i * 5, 1, 0);
		c.color = { 200,200,200 };
		c.Render();
	}

	//checkpoints

	d.color = { 0, 255, 0 };
	d.Render();


	if (sensor_cube1->GetPosition().y == 1000)
	{
		d.SetPos(1000, 1000, 1000);
	}
	else {
		d.SetPos(0, 3, 6);
	}

	aa.color = { 0, 255, 0 };
	aa.Render();

	if (sensor_cube2->GetPosition().y == 1000)
	{
		aa.SetPos(1000, 1000, 1000);
	}
	else {
		aa.SetPos(10, 3, 6);
	}


	aaa.color = { 0, 255, 0 };
	aaa.Render();
	if (sensor_cube3->GetPosition().y == 1000)
	{
		aaa.SetPos(1000, 1000, 1000);
	}
	else {
		aaa.SetPos(20, 3, 6);
	}
	// color meta
	metaColor.color = { 0, 255, 0 };
	metaColor.Render();


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

