#include "Manager.h"

Manager::Manager(Texture &t)
{
	ParticleSystem *particles1 = new ParticleSystem(100);
	// create the particle system
	particles1->setEmitter(Vector2f(350, 500));
	particles1->texture = t;
	particles1->velocityStrategy = new LinearInStrategy();

	ParticleSystem *particles2 = new ParticleSystem(100);
	particles2->setEmitter(Vector2f(700, 500));
	particles2->texture = t;
	particles2->velocityStrategy = new exponentialInStrategy();

	ParticleSystem *particles3 = new ParticleSystem(100);
	particles3->setEmitter(Vector2f(1050, 500));
	particles3->texture = t;
	particles3->velocityStrategy = new sinInStrategy();

	PSList.push_back(particles1);
	PSList.push_back(particles2);
	PSList.push_back(particles3);

}
void Manager::changeStage(int stage, Window &window)
{
	for (int i = 0; i<PSList.size(); i++)
	{
		delete(PSList[i]->velocityStrategy);
		PSList[i]->velocityStrategy = nullptr;

		delete(PSList[i]->angleStrategy);
		PSList[i]->angleStrategy = nullptr;

		delete(PSList[i]->sizeStrategy);
		PSList[i]->sizeStrategy = nullptr;

		delete(PSList[i]->rotateStrategy);
		PSList[i]->rotateStrategy = nullptr;
	}
	if (stage == 0)
	{
		for (ParticleSystem *ps : PSList)
		{
			ps->angleRand = 360;
			ps->velocityRand = 1;
			ps->rotationRand = 1;
			ps->sizeRand = 1;
			ps->rotateSpeedRand = 1;
		}
	}
	else if (stage == 1) {
		for (ParticleSystem *ps : PSList)
		{
			ps->angleRand = 90;
			ps->velocityRand = 1;
			ps->rotationRand = 1;
			ps->sizeRand = 1;
			ps->rotateSpeedRand = 1;
		}
	}
	else if (stage == 2) {
		for (ParticleSystem *ps : PSList)
		{
			ps->angleRand = 90;
			ps->velocityRand = 200;
			ps->rotationRand = 1;
			ps->sizeRand = 1;
			ps->rotateSpeedRand = 1;
		}
	}
	else if (stage == 3) {
		for (ParticleSystem *ps : PSList)
		{
			ps->angleRand = 90;
			ps->velocityRand = 200;
			ps->rotationRand = 60;
			ps->sizeRand = 1;
			ps->rotateSpeedRand = 1;
		}

	}
	else if (stage == 4) {
		for (ParticleSystem *ps : PSList)
		{
			ps->angleRand = 90;
			ps->velocityRand = 200;
			ps->rotationRand = 60;
			ps->sizeRand = 80;
			ps->rotateSpeedRand = 1;
		}

	}
	else if (stage == 5) {
		for (ParticleSystem *ps : PSList)
		{
			ps->angleRand = 90;
			ps->velocityRand = 200;
			ps->rotationRand = 360;
			ps->sizeRand = 80;
			ps->rotateSpeedRand = 360;
		}

	}
	else if (stage == 6) {
			PSList[0]->velocityStrategy = new LinearInStrategy();
			PSList[1]->velocityStrategy = new exponentialInStrategy();
			PSList[2]->velocityStrategy = new sinInStrategy();

	}
	else if (stage == 7)
	{
		for (ParticleSystem *ps : PSList)
		{
			ps->startVelocity = 300;
			ps->velocityRand = 100;
			ps->rotationRand = 1;
			ps->sizeRand = 80;
			ps->rotateSpeedRand = 360;
		}
			PSList[0]->angleStrategy = new LinearInStrategy();
			PSList[1]->angleStrategy = new exponentialInStrategy();
			PSList[2]->angleStrategy = new sinInStrategy();
	}
	else if (stage == 8)
	{
		for (ParticleSystem *ps : PSList)
		{
			ps->startVelocity = 150;
			ps->velocityRand = 100;
			ps->rotationRand = 360;
			ps->sizeRand = 80;
			ps->rotateSpeedRand = 360;
		}
			PSList[0]->sizeStrategy = new LinearInStrategy();
			PSList[1]->sizeStrategy = new exponentialInStrategy();
			PSList[2]->sizeStrategy = new sinInStrategy();
	}
	else if (stage == 9)
	{
			PSList[0]->rotateStrategy = new LinearInStrategy();
			PSList[1]->rotateStrategy = new exponentialInStrategy();
			PSList[2]->rotateStrategy = new sinInStrategy();
	}


}