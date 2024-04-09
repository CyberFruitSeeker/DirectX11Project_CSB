#pragma once

enum class CollisionOrder
{
	Player,
	Object,
	Monster,

};

enum class RenderingOrder
{
	Stage,
	Player,
	Item,
	Monster,
	SuddenMonster,
	BossMonster,
};

enum class CameraView
{
	Front,
	Back,
};
