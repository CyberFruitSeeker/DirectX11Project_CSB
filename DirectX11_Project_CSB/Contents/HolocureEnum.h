#pragma once

enum class ECollisionOrder
{
	Player,
	MapObject,
	Items,
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
	MouseCursor,
	FiledSpawnMonster,
	SuddenSpawnMonster,
	BossMonster,
	Item,
	Object,
};

enum class EPlayerDir
{
	S,
	SW,
	W,
	NW,
	N,
	NE,
	E,
	SE,
};

//enum class EMonsterSpawnOrder
//{
//	FiledSpawnMonster,
//	SuddenSpawnMonster,
//	BossMonster,
//};

enum class EActorDir
{
	Left,
	Right,
};

//enum class EFieldDropItemOrder
//{
//	Hamberger,
//	HoloBox,
//	UpgradeAnvil,
//};

//enum class ECameraViewOrder
//{
//	Front,
//	Back,
//};
