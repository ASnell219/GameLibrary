#pragma once
#include "id.h"

class Entity;

struct Event
{
	ID eventID;
	Entity* sender;
	Entity* receiver;

	Event() {}
};