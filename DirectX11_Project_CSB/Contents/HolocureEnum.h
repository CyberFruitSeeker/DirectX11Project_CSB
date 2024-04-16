#pragma once

enum class ECollisionOrder
{
	Player,
	MapObject,
	Monster,
	BossMonster,
};

enum class ELayerOrder
{
	BackLayer,
	FrontLayer,
	EffectLayer,
	UILayer,
};

enum class ERenderingOrder
{
	Back,
	Front,
	Player,
	Item,
};

enum class EMonsterSpawnOrder
{
	FiledSpawnMonster,
	SuddenSpawnMonster,
	BossMonster,
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EFieldItemDropOrder
{
	Hamberger,
	HoloBox,
	UpgradeAnvil,
};

enum class ECameraViewOrder
{
	Front,
	Back,
};
