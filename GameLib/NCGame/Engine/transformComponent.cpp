#include "transformComponent.h"

void TransformComponent::Create(const Vector2D& position, float rotation, float scale )
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void TransformComponent::Destroy()
{
	//
}

void TransformComponent::Update()
{
	Matrix33 mxs; mxs.Scale(scale);
	Matrix33 mxr; mxr.Rotate(rotation * Math::DegreesToRadians);
	Matrix33 mxt; mxt.Translate(position);

	matrix = mxs * mxr * mxt;
}
