#pragma once

#include "Meteor.h"

class World;
class SmallMeteor: public Meteor
{
public:
	explicit SmallMeteor(World* world);

	void onDestroy() override;

	int getPoints() const override;
};

