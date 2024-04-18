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

// ���ʺ��� �ð��������
enum class EPlayerDir
{
	None,
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W,
	NW,
};

//enum class EActorDir
//{
//	Left,
//	Right,
//};

//enum class EMonsterSpawnOrder
//{
//	FiledSpawnMonster,
//	SuddenSpawnMonster,
//	BossMonster,
//};


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
