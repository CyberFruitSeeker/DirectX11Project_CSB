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
	PlayerMonsterLayer,
	EffectLayer,
	UILayer,
};

enum class ERenderingOrder
{
	Back,
	StageMap,
	Front,
	Player,
	Item,
};

enum class ESpawnOrder
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
