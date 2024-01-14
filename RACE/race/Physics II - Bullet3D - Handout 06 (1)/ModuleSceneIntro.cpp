#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"

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

	// Big plane as ground
	{
		btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

		btDefaultMotionState* myMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);

		btRigidBody* body = new btRigidBody(rbInfo);
		App->physics->world->addRigidBody(body);
	}

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

	cube3 = App->physics->AddBody(Cube(30, 5, 8), 0.0);   //cube3 = circuit platform
	cube3->SetPos(15, 1, 0); 
	cube3 = App->physics->AddBody(Cube(30, 5, 8), 0.0);
	cube3->SetPos(42, 1, 2);
	wall = App->physics->AddBody(Cube(2, 10, 10), 0.0);
	wall->SetPos(58, 1, 2);
	cube3 = App->physics->AddBody(Cube(14, 5, 34), 0.0);
	cube3->SetPos(53, 1, 20);
	cube3 = App->physics->AddBody(Cube(15, 5, 8), 0.0);
	cube3->SetPos(42, 1, 28);
	wall = App->physics->AddBody(Cube(2, 10, 8), 0.0);
	wall->SetPos(27, 1, 28);
	cube3 = App->physics->AddBody(Cube(8, 5, 20), 0.0);
	cube3->SetPos(32, 1, 34);
	cube3 = App->physics->AddBody(Cube(24, 5, 18), 0.0);
	cube3->SetPos(25, 1, 45);
	wall = App->physics->AddBody(Cube(10, 10, 2), 0.0);
	wall->SetPos(27, 1, 47);
	cube3 = App->physics->AddBody(Cube(8, 4, 16), 0.0);
	cube3->SetPos(17, 1, 30);
	wall = App->physics->AddBody(Cube(4, 10, 10), 0.0);
	wall->SetPos(11, 1, 34);
	cube3 = App->physics->AddBody(Cube(15, 3, 8), 0.0);
	cube3->SetPos(10, 1, 25);
	wall = App->physics->AddBody(Cube(2, 10, 6), 0.0);
	wall->SetPos(1.5, 1, 25);
	wall = App->physics->AddBody(Cube(6, 10, 2), 0.0);
	wall->SetPos(4, 1, 20);
	cube3 = App->physics->AddBody(Cube(8, 3, 20), 0.0);
	cube3->SetPos(5, 1, 38);
	cube3 = App->physics->AddBody(Cube(40, 3, 8), 0.0);
	cube3->SetPos(-10, 1, 52);
	cube3 = App->physics->AddBody(Cube(30, 3, 40), 0.0);
	cube3->SetPos(-35, 1, 42);
	wall = App->physics->AddBody(Cube(20, 8, 2), 0.0);
	wall->SetPos(-15, 1, 47);
	wall = App->physics->AddBody(Cube(26, 8, 2), 0.0);
	wall->SetPos(-3, 1, 57);
	cube3 = App->physics->AddBody(Cube(8, 3, 8), 0.0);
	cube3->SetPos(-35, 1, 18);

	stadium = App->physics->AddBody(Cube(150, 5, 1), 0.0);
	stadium->SetPos(10, 2 , 70 );
	stadium = App->physics->AddBody(Cube(150, 5, 1), 0.0);
	stadium->SetPos(10, 2, -25);
	stadium = App->physics->AddBody(Cube(1, 5, 95), 0.0);
	stadium->SetPos(85, 2, 22);
	stadium = App->physics->AddBody(Cube(1, 5, 95), 0.0);
	stadium->SetPos(-65, 2, 22);

	for (int i = 0; i < 10; i++)
	{
		stadium = App->physics->AddBody(Cube(150,2, 3), 0.0);
		stadium->SetPos(10, 4 + 2 * i, 73 + i * 2);
		stadium = App->physics->AddBody(Cube(150, 2, 3), 0.0);
		stadium->SetPos(10, 4 + 2 * i, -28 + i * -2);
		stadium = App->physics->AddBody(Cube(3, 2, 95), 0.0);
		stadium->SetPos(88 + i * 2, 4 + 2 * i, 22);
		stadium = App->physics->AddBody(Cube(3, 2, 95), 0.0);
		stadium->SetPos(-68 + i * -2, 4 + 2 * i, 22);
	}
;
	

	// Crear una pelota con fricci�n
	btCollisionShape* ballShape = new btSphereShape(1.5); // Ajusta el radio seg�n sea necesario

	btTransform ballTransform;
	ballTransform.setIdentity();
	ballTransform.setOrigin(btVector3(0, 10, 0)); // Ajusta la posici�n inicial de la pelota

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(ballTransform);
	btRigidBody::btRigidBodyConstructionInfo ballRbInfo(1.0f, ballMotionState, ballShape); // Establece una masa diferente de 0.0f

	ballBody = new btRigidBody(ballRbInfo);
	ballBody->setFriction(0.5f); // Ajusta el coeficiente de fricci�n seg�n sea necesario
	App->physics->world->addRigidBody(ballBody);



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
	//for (int i = 0; i < 5; i++)
	//{
	//	Cube c(10, 2, 8);

	//	c.SetPos(i * 5, 1, 0);
	//	c.color = { 200,200,200 };
	//	c.Render();
	//}

	//Circuit
	Cube q(30, 5, 8);
	q.SetPos(15, 1, 0);
	q.color = { 200,200,200 };
	q.Render();

	Cube q1(30, 5, 8);
	q1.SetPos(42, 1, 2);
	q1.color = { 200,200,200 };
	q1.Render();

	Cube q2(14, 5, 34);
	q2.SetPos(53, 1, 20);
	q2.color = { 200,200,200 };
	q2.Render();

	Cube q3(15, 5, 8);
	q3.SetPos(42, 1, 28);
	q3.color = { 200,200,200 };
	q3.Render();

	Cube q4(8, 5, 20);
	q4.SetPos(32, 1, 34);
	q4.color = { 200,200,200 };
	q4.Render();
	
	Cube q5(24, 5, 18);
	q5.SetPos(25, 1, 45);
	q5.color = { 200,200,200 };
	q5.Render();
	
	Cube q6(8, 4, 15);
	q6.SetPos(17, 1, 30);
	q6.color = { 200,200,200 };
	q6.Render();

	Cube q7(15, 3, 8);
	q7.SetPos(10, 1, 25);
	q7.color = { 200,200,200 };
	q7.Render();
	
	Cube q8(8, 3, 20);
	q8.SetPos(5, 1, 38);
	q8.color = { 200,200,200 };
	q8.Render();

	Cube q9(40, 3, 8);
	q9.SetPos(-10, 1, 52);
	q9.color = { 200,200,200 };
	q9.Render();
	
	Cube q10(30, 3, 40);
	q10.SetPos(-35, 1, 42);
	q10.color = { 200,200,200 };
	q10.Render();

	Cube q11(8, 3, 8);   //finish line
	q11.SetPos(-35, 1, 18);
	q11.color = { 200,0,0 };
	q11.Render();

	//walls
	Cube e(20, 8, 2);
	e.SetPos(-15, 1, 47);
	e.color = { 200,200,0 };
	e.Render();

	Cube e1(26, 8, 2);
	e1.SetPos(-3, 1, 57);
	e1.color = { 200,200,0 };
	e1.Render();
	
	Cube e2(2, 10, 6);
	e2.SetPos(1.5, 1, 25);
	e2.color = { 200,200,0 };
	e2.Render();

	Cube e3(6, 10, 2);
	e3.SetPos(4, 1, 20);
	e3.color = { 200,200,0 };
	e3.Render();

	Cube e4(4, 10, 10);
	e4.SetPos(11, 1, 34);
	e4.color = { 200,200,0 };
	e4.Render();
	
	Cube e5(10, 10, 2);
	e5.SetPos(27, 1, 47);
	e5.color = { 200,200,0 };
	e5.Render();

	Cube e6(2, 10, 8);
	e6.SetPos(27, 1, 28);
	e6.color = { 200,200,0 };
	e6.Render();
	
	Cube e7(2, 10, 10);
	e7.SetPos(58, 1, 2);
	e7.color = { 200,200,0 };
	e7.Render();
	//limits border
	Cube s(150, 5, 1);
	s.SetPos(10, 2, 70);
	s.color = { 65,65,65 };
	s.Render();

	Cube s1(150, 5, 1);
	s1.SetPos(10, 2, -25);
	s1.color = { 65,65,65 };
	s1.Render();

	Cube s2(1, 5, 95);
	s2.SetPos(85, 2, 22);
	s2.color = { 65,65,65 };
	s2.Render();

	Cube s3(1, 5, 95);
	s3.SetPos(-65, 2, 22);
	s3.color = { 65,65,65 };
	s3.Render();
	//Stadium
	for (int i = 0; i < 10; i++)
	{
		Cube w(150, 2, 3);

		w.SetPos(10, 4+2*i, 73+i*2);
		w.color = { 0,100,200 };
		w.Render();
	}

	for (int i = 0; i < 10; i++)
	{
		Cube w(150, 2, 3);

		w.SetPos(10, 4 + 2 * i, -28 + i * -2);
		w.color = { 0,200,200 };
		w.Render();
	}

		for (int i = 0; i < 10; i++)
	{
		Cube w(3, 2, 95);

		w.SetPos(88+i*2, 4+ 2 * i, 22);
		w.color = { 0,200,200 };
		w.Render();
	}

		for (int i = 0; i < 10; i++)
		{
			Cube w(3, 2, 95);

			w.SetPos(-68 + i * -2, 4 + 2 * i, 22);
			w.color = { 0,200,200 };
			w.Render();
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

	btTransform transform;
	ballBody->getMotionState()->getWorldTransform(transform);

	btVector3 position = transform.getOrigin();

	// Ahora 'position' contiene las coordenadas x, y, z de la posici�n actual de ballBody
	
	float y = position.getY();
	float z = position.getZ();
	
	if (y < 2)
	{
		restart = true;
		float newX = 0;
		float newY = 10;
		float newZ = 0;

		ballBody->setLinearVelocity(btVector3(0, 0, 0));
		ballBody->setAngularVelocity(btVector3(0, 0, 0));

		btTransform newTransform;
		newTransform.setIdentity();
		newTransform.setOrigin(btVector3(newX, newY, newZ));

		// Establecer la nueva transformaci�n para el MotionState
		ballBody->getMotionState()->setWorldTransform(newTransform);

		// Notificar al mundo de f�sica que la transformaci�n ha cambiado
		ballBody->setWorldTransform(newTransform);
	}
		

	return UPDATE_CONTINUE;
}



