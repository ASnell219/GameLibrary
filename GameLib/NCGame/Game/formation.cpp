#include "formation.h"
#include "timer.h"

void Formation::Create()
{
	m_enterPaths[0] = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };
	m_enterPaths[1] = { Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f), Vector2D(600.0f, 200.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f) };

	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });

	m_formation =
	{ { { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(100.0f, 100.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f, Vector2D(140.0f, 100.0f), this }, 0.35f, false },
	{ { Enemy::BOSS, Enemy::LEFT, 300.0f, Vector2D(180.0f, 100.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::RIGHT, 300.0f, Vector2D(700.0f, 100.0f), this }, 3.0f, false },
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f, Vector2D(660.0f, 100.0f), this }, 3.35f, false },
	};

	m_timer = 0.0f;
}

void Formation::Destroy()
{

}

void Formation::Update()
{
	m_timer += Timer::Instance()->DeltaTime();
	for (Info& info : m_formation)
	{
		if (info.isActive == false && m_timer > info.enterTime)
		{
			info.isActive = true;
			Enemy* enemy = m_scene->AddEntity<Enemy>();
			enemy->Create(info.enemyInfo);

		}
	}
}

const Formation::Path& Formation::GetRandomAttackPath()
{
	size_t index = rand() % m_attackPaths.size();
	return m_attackPaths[index];
}
