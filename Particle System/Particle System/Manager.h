#pragma once
#include "ParticleSystem.h"

class Manager
{
public:
	vector<ParticleSystem*> PSList;
	Manager(Texture &t);
	void changeStage(int stage, Window &window);

};

