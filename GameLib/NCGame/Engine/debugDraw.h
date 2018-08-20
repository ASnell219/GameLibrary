#pragma once
#include "color.h"
#include "aabb.h"
#include "vector2D.h"

namespace Debug
{

#ifdef __cplusplus
	extern "C"
	{
#endif
	ENGINE_API void DrawAABB(const AABB& aabb, Color color = Color::red);
	ENGINE_API void DrawLine(const Vector2D& v1, const Vector2D& v2, const Color& color = Color::red);
	ENGINE_API void DrawCross(const Vector2D& v1, const Vector2D& size, const Color& color = Color::red);
#ifdef __cplusplus
	}
#endif
}

#ifdef _DEBUG
#define DEBUG_DRAW_AABB(aabb, color) Debug::DrawAABB(aabb, color);
#define DEBUG_DRAW_LINE(v1, v2, color) Debug::DrawLine(v1, v2, color);
#define DEBUG_DRAW_CROSS(v1, size, color) Debug::DrawLine(v1, size, color);
#else
#define DEBUG_DRAW_AABB(aabb, color) 
#define DEBUG_DRAW_LINE(v1, v2, color) 
#define DEBUG_DRAW_CROSS(v1, size, color) 
#endif