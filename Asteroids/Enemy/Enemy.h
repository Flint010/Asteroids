#pragma once

#include "../Entity.h"
#include "../Configuration/Configuration.h"
#include "../World/World.h"

class Enemy: public Entity
{
public:
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	Enemy(Configuration::Texture tex_id, World* world);

	virtual void onDestroy();

	virtual int getPoints() const = 0;		
};

