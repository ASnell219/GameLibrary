#pragma once

#include "engine.h"
#include "id.h"

class ENGINE_API Object
{
public:
	Object(const ID& id = ID()) : m_id(id) {}
	virtual ~Object() {}

protected:
	ID m_id;
};
