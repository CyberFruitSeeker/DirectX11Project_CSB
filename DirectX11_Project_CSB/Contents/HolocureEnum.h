#pragma once

enum class ECollisionOrder
{
	Player,
	MapObject,
	Weapon,
	Items,
	Monster,
	//BossMonster,
	SmolAme,
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
	Title,
	Back,
	Front,
	Player,
	Mouse,
	Attack,
	MonsterUp,
	MonsterDown,
	MonsterUIUp,
	MonsterUIDown,
	Shadow,
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

enum class EActorDir
{
	Left,
	Right,
};

enum class EMonsterMoveType
{
	Follow,
	StraightToPlayer,
	StraightToUp,
	StraightToDown,
	StraightToRight,
	StraightToLeft,
	Stop,
};

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
