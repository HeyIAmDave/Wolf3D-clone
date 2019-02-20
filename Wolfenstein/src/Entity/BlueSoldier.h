#pragma once
#include "Character.h"
#include "AABB.h"

class Level;
class Player;

class BlueSoldier : public Character
{
public:
	BlueSoldier();
	
	void Init(float speed, Player& player, Level& level, TextureAtlas& textureAtlas);
	virtual void Update(float delta) override;
	virtual void Render() override;
	virtual void CleanUp() override;
private:
	Sprite m_sprite;
	Level* m_level;
	Player* m_player;
	AABB m_aabb;
	float m_distanceTillStop;

private:
	void Move(float delta);
	void PlayAnimation(unsigned int anim, float delta);

	void CheckCollisions(const glm::vec3& velDir);
};