#pragma once

enum class CollisionOrder
{
	Player,
	MapObject,
	Monster,
	BossMonster,
};

enum class RenderingOrder
{
	Stage,
	Player,
	Item,
	FiledSpawnMonster,
	SuddenSpawnMonster,
	BossMonster,
};

enum class FieldDropItem
{
	Hamberger,
	HoloBox,
	UpgradeAnvil,
};

enum class CameraView
{
	Front,
	Back,
};
