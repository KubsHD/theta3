#pragma once

#include <core/types.h>

class Tool {
public:
	virtual void init() = 0;
	virtual void render() = 0;
};