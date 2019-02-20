#include "pch.h"
#include "BlueSoldier.h"
#include "Level/Level.h"
#include "Player.h"

BlueSoldier::BlueSoldier()
	: m_distanceTillStop(1.0f)
{ }

void BlueSoldier::Init(float speed, Player& player, Level& level, TextureAtlas& textureAtlas)
{
	GetSpeed() = speed;
	m_player = &player;
	m_level = &level;
	m_sprite = GetInstance(Loader).CreateSprite("BlueSoldier", 244, textureAtlas);
	m_aabb.Init(GetTransform().GetPos(), { 0.25f, 0.5f, 0.25f });
}

void BlueSoldier::Update(float delta)
{
	Move(delta);
	GetVelocity() *= delta;
}

void BlueSoldier::Render()
{
	m_sprite.Render();
}

void BlueSoldier::CleanUp()
{ }

void BlueSoldier::Move(float delta)
{
	glm::vec3 targetPos = m_player->GetTransform().GetPos();
	glm::vec3 dir = targetPos - GetTransform().GetPos();

	float dstToTarget = glm::distance(GetTransform().GetPos(), targetPos);
	static bool shouldFollow = false;
	if (Input::IsKeyDown(KEY_F))
		shouldFollow = !shouldFollow;

	if (dstToTarget >= m_distanceTillStop && shouldFollow)
		GetVelocity() += dir * GetSpeed();

	if (glm::length(GetVelocity()) > 0.0f)
		PlayAnimation(1, delta);
	else
		PlayAnimation(0, delta);

	if (Input::IsKeyPressed(KEY_UP))
		GetVelocity() += GetTransform().GetForward() * -GetSpeed();
	if (Input::IsKeyPressed(KEY_DOWN))
		GetVelocity() += GetTransform().GetForward() * GetSpeed();
	if (Input::IsKeyPressed(KEY_LEFT))
		GetVelocity() += GetTransform().GetRight() * -GetSpeed();
	if (Input::IsKeyPressed(KEY_RIGHT))
		GetVelocity() += GetTransform().GetRight() * GetSpeed();

	GetTransform().GetPos().x += GetVelocity().x * delta;
	CheckCollisions({ GetVelocity().x, 0, 0 });

	GetTransform().GetPos().z += GetVelocity().z * delta;
	CheckCollisions({ 0, 0, GetVelocity().z });
}

void BlueSoldier::PlayAnimation(unsigned int anim, float delta)
{
	switch (anim)
	{
	case 0:
		m_sprite.UpdateTexCoords(244);
		return;
	case 1:
		unsigned int index = 245;
		unsigned int animFrames = 2;
		static float animTime = 0.0f;

		animTime += 3.0f * delta;
		unsigned int frame = (int)animTime % animFrames;
		index += frame;

		m_sprite.UpdateTexCoords(index);
		return;
	}
}

void BlueSoldier::CheckCollisions(const glm::vec3 & velDir)
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