#include "aabbComponent.h"
#include "transform.h"
#include "entity.h"
#include "spriteComponent.h"
#include "texture.h"

void AABBComponent::Create()
{
}

void AABBComponent::Destroy()
{
}

void AABBComponent::Update()
{
	Transform transform = m_owner->GetTransform();
	Vector2D position = transform.position;
	Vector2D size = transform.scale;

	SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
	if (spriteComponent)
	{
		size = size * spriteComponent->GetTexture()->GetSize();
		position = position - (size * spriteComponent->GetOrigin());
	}

	m_aabb.Build(position, size* 0.5f);
}

bool AABBComponent::Intersects(ICollisionComponent * other)
{
	bool intersects = false;

	AABBComponent* aabbComponent = dynamic_cast<AABBComponent*>(other);
	if (aabbComponent)
	{
		intersects = m_aabb.Intersects(aabbComponent->m_aabb);
	}

	return false;
}
