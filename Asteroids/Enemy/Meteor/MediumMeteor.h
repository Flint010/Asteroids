#pragma once

#include "Meteor.h"

class World;
class MediumMeteor: public Meteor
{
public:
	explicit MediumMeteor(World* world);

	void onDestroy() override;

	int getPoints() const override;
};

