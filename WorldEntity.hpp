#pragma once
#include "Common.hpp"

class WorldEntity {
public:
	bool IsEnabled();
	void SetEnabled(bool val);
	virtual bool IsRenderable() = 0;
	virtual bool IsCollidable() = 0;
	virtual bool IsGravitated() = 0;
	virtual void RenderEntity() = 0;

	NO_CCTOR(WorldEntity);
protected:
	bool enabled;
};