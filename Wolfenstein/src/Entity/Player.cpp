#include "pch.h"
#include "Player.h"
#include "Level/Level.h"

Player::Player()
	: m_lookSensitivity(0.0f), m_mouseLocked(false)
{ }

void Player::Init(float speed, float lookSensitivity, Level & level, Camera & camera)
{
	GetSpeed() = speed;
	m_lookSensitivity = lookSensitivity;
	m_level = &level;
	m_camera = &camera;

	GetTransform().GetPos() = m_level->GetSpawnPoint();
	GetTransform().Rotate(180.0f, { 0, 1, 0 });
	m_aabb.Init(GetTransform().GetPos(), { 0.25f, 0.5f, 0.25f });

	glm::vec3 camPos = GetTransform().GetPos();
	camPos.y = 0.6f;
	m_camera->GetTransform().GetPos() = camPos;
	m_camera->GetTransform().GetRot() = GetTransform().GetRot();
}

void Player::Update(float delta)
{
	if (m_mouseLocked)
	{
		if (Input::IsKeyDown(KEY_ESCAPE))
		{
			Input::LockCursor(false);
			m_mouseLocked = false;
		}

		Move(delta);
		Look(delta);
	}
	else
	{
		if (Input::IsMouseButtonDown(0))
		{
			Input::LockCursor(true);
			m_mouseLocked = true;
		}
	}

	GetVelocity() *= delta;
}

void Player::CheckCollisions(const glm::vec3 & velDir)
{
	GetTransform().GetPos();
	auto& pos = GetTransform().GetPos();

	for (int x = pos.x - m_aabb.GetExtents().x; x < pos.x + m_aabb.GetExtents().x; x++)
	{
		for (int z = pos.z - m_aabb.GetExtents().z; z < pos.z + m_aabb.GetExtents().z; z++)
		{
			auto& tile = m_level->GetTile(x, z);
			if (tile.GetType() == TILE_EMPTY)
			{
				if (velDir.x > 0)
					pos.x = x - m_aabb.GetExtents().x;
				else if (velDir.x < 0)
					pos.x = x + m_aabb.GetExtents().x + 1;

				if (velDir.z > 0)
					pos.z = z - m_aabb.GetExtents().z;
				else if (velDir.z < 0)
					pos.z = z + m_aabb.GetExtents().z + 1;
			}
		}
	}
}

//void Player::CheckObjectCollisions(const glm::vec3 & velDir)
//{
//	GetTransform().GetPos();
//	auto& pos = GetTransform().GetPos();
//
//	for (int x = pos.x - m_aabb.GetExtents().x; x < pos.x + m_aabb.GetExtents().x; x++)
//	{
//		for (int z = pos.z - m_aabb.GetExtents().z; z < pos.z + m_aabb.GetExtents().z; z++)
//		{
//			auto& objectData = m_level->GetObjectData();
//			for (auto& o : objectData)
//			{
//				// auto& tile = m_level->GetTile(x, z);
//				glm::ivec2 oPos = { o->GetTransform().GetPos().x, o->GetTransform().GetPos().z };
//				bool hasObject = oPos == glm::ivec2(x, z);
//				if (hasObject)
//				{
//					if (velDir.x > 0)
//						pos.x = x - m_aabb.GetExtents().x;
//					else if (velDir.x < 0)
//						pos.x = x + m_aabb.GetExtents().x + 1;
//
//					if (velDir.z > 0)
//						pos.z = z - m_aabb.GetExtents().z;
//					else if (velDir.z < 0)
//						pos.z = z + m_aabb.GetExtents().z + 1;
//				}
//			}
//		}
//	}
//}

void Player::Move(float delta)
{
	if (Input::IsKeyPressed(KEY_W))
		GetVelocity() += GetTransform().GetForward() * -GetSpeed();
	if (Input::IsKeyPressed(KEY_S))
		GetVelocity() += GetTransform().GetForward() * GetSpeed();

	static bool checkCollisions = true;
	if (Input::IsKeyDown(KEY_G))
		checkCollisions = !checkCollisions;

	GetTransform().GetPos().x += GetVelocity().x * delta;
	if (checkCollisions)
		CheckCollisions({ GetVelocity().x, 0, 0 });

	GetTransform().GetPos().z += GetVelocity().z * delta;
	if (checkCollisions)
		CheckCollisions({ 0, 0, GetVelocity().z });

	glm::vec3 camPos = GetTransform().GetPos();
	camPos.y = 0.6f;
	m_camera->GetTransform().GetPos() = camPos;
}

void Player::Look(float delta)
{
	float amount = delta * m_lookSensitivity;

	if (Input::IsKeyPressed(KEY_A))
		GetTransform().GetRot() *= glm::angleAxis(glm::radians(-amount), glm::vec3(0, 1, 0));
	if (Input::IsKeyPressed(KEY_D))
		GetTransform().GetRot() *= glm::angleAxis(glm::radians(amount), glm::vec3(0, 1, 0));

	m_camera->GetTransform().GetRot() = GetTransform().GetRot();
}