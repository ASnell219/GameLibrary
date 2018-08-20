#include "debugDraw.h"
#include "renderer.h"

void Debug::DrawAABB(const AABB & aabb, Color color)
{
	float minx = aabb.Min().x;
	float miny = aabb.Min().y;
	float maxx = aabb.Max().x;
	float maxy = aabb.Max().y;

	Renderer::Instance()->DebugDrawLine(Vector2D(minx, miny), Vector2D(maxx, miny));
	Renderer::Instance()->DebugDrawLine(Vector2D(maxx, miny), Vector2D(maxx, maxy));
	Renderer::Instance()->DebugDrawLine(Vector2D(maxx, maxy), Vector2D(minx, maxy));
	Renderer::Instance()->DebugDrawLine(Vector2D(minx, maxy), Vector2D(minx, miny));
}

void Debug::DrawLine(const Vector2D & v1, const Vector2D & v2, const Color & color)
{
	Renderer::Instance()->DebugDrawLine(v1, v2, color);
}

void Debug::DrawCross(const Vector2D & v1, const Vector2D & size, const Color & color)
{
	Renderer::Instance()->DebugDrawLine(v1 - Vector2D(size.x * 0.5f, 0.0f), v1 + Vector2D(size.x * 0.5f, 0.0f), color);
	Renderer::Instance()->DebugDrawLine(v1 - Vector2D(0.0f, size.y * 0.5f), v1 + Vector2D(0.0f, size.y * 0.5f), color);
}
