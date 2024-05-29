#pragma once

#include "Meteor.h"

class World;
class BigMeteor: public Meteor
{
public:
	explicit BigMeteor(World* world);

	void onDestroy() override;

	int getPoints() const override;
};

