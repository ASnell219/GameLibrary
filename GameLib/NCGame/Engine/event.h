#pragma once
#include "id.h"
#include "variant.h"

class Entity;

struct Event
{
	ID eventID;
	Entity* sender;
	Entity* receiver;
	Variant variant[3];

	Event() {}
};