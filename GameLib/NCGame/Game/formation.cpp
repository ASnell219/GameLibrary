#include "formation.h"
#include "timer.h"

void Formation::Create()
{
	m_enterPaths[0] = { Vector2D(-200.0f, 400.0f), Vector2D(-300.0f, 300.0f), Vector2D(-200.0f, 200.0f), Vector2D(-100.0f, 300.0f), Vector2D(-200.0f, 400.0f) };
	m_enterPaths[1] = { Vector2D(850.0f, 400.0f), Vector2D(850.0f, 300.0f), Vector2D(900.0f, 200.0f), Vector2D(900.0f, 300.0f), Vector2D(900.0f, 400.0f) };

	m_enterPaths[2] = { Vector2D(500.0f, -64.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f) };
	m_enterPaths[3] = { Vector2D(300.0f, -64.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f) };

	m_attackPaths =
	{ { Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f), Vector2D(650.0f, 850.0f) },
	{ Vector2D(100.0f, 200.0f), Vector2D(300.0f, 300.0f), Vector2D(400.0f, 400.0f), Vector2D(250.0f, 350.0f), Vector2D(-200.0f, 50.0f) },
	{ Vector2D(200.0f, 400.0f), Vector2D(600.0f, 600.0f), Vector2D(700.0f, 700.0f), Vector2D(350.0f, 450.0f), Vector2D(650.0f, 650.0f) },
	{ Vector2D(500.0f, 700.0f), Vector2D(200.0f, 200.0f), Vector2D(300.0f, 300.0f), Vector2D(650.0f, 550.0f), Vector2D(-550.0f, 250.0f) },
	{ Vector2D(600.0f, 600.0f), Vector2D(100.0f, 100.0f), Vector2D(200.0f, 200.0f), Vector2D(450.0f, 550.0f), Vector2D(750.0f, 650.0f) },
	};

	m_formation =
	{ { { Enemy::BEE, Enemy::TOPLEFT, 300.0f, Vector2D(100.0f, 160.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::BOTTOMLEFT, 300.0f, Vector2D(140.0f, 160.0f), this }, 0.35f, false },
	{ { Enemy::BEE, Enemy::TOPLEFT, 300.0f, Vector2D(700.0f, 160.0f), this }, 0.7f, false },
	{ { Enemy::BEE, Enemy::BOTTOMLEFT, 300.0f, Vector2D(660.0f, 200.0f), this }, 1.05f, false },
	{ { Enemy::BUG, Enemy::TOPRIGHT, 300.0f, Vector2D(100.0f, 80.0f), this }, 0.0f, false },
	{ { Enemy::BUG, Enemy::BOTTOMRIGHT, 300.0f, Vector2D(140.0f, 80.0f), this }, 0.35f, false },
	{ { Enemy::BUG, Enemy::TOPRIGHT, 300.0f, Vector2D(700.0f, 120.0f), this }, 0.7f, false },
	{ { Enemy::BUG, Enemy::BOTTOMRIGHT, 300.0f, Vector2D(660.0f, 120.0f), this }, 1.05f, false },
	{ { Enemy::BOSS, Enemy::BOTTOMLEFT, 300.0f, Vector2D(140.0f, 220.0f), this }, 0.05f, false },
	{ { Enemy::BOSS, Enemy::TOPRIGHT, 300.0f, Vector2D(700.0f, 80.0f), this }, 1.05f, false },
	{ { Enemy::BOSS, Enemy::TOPRIGHT, 300.0f, Vector2D(700.0f, 220.0f), this }, 0.35f, false },
	{ { Enemy::BOSS, Enemy::BOTTOMRIGHT, 300.0f, Vector2D(660.0f, 100.0f), this }, 0.07f, false },
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
