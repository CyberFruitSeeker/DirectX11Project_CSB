#pragma once

enum class ELayerOrder
{
	BackGround,
	PlayerMonster,
	Effect,
	UILayer,
};

enum class ECollisionOrder
{
	Player,
	MapObject,
	Monster,
	BossMonster,
};

enum class ERenderingOrder
{
	Stage,
	Player,
	Item,
	FiledSpawnMonster,
	SuddenSpawnMonster,
	BossMonster,
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EFieldDropItem
{
	Hamberger,
	HoloBox,
	UpgradeAnvil,
};

enum class ECameraView
{
	Front,
	Back,
};
