#pragma once

#include <core/types.h>
#include <core/ecs.h>

public enum LightType {
	Point,
	Spot
};

class Light : public Component {

public:

	LightType Type;

	PointLightData Point;
	SpotLightData Spot;

	void init() override;


	void update() override;


	void render(Renderer* ren) override;

};