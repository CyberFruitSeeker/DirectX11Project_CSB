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

// 배치 되는 높이? : 위로 올라갈수록 더 아래에다 배치된다.
// 즉, "아래로 갈수록 위로 배치됨"
enum class ERenderingOrder
{
	//Title,
	//TitleF,
	Skill,
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
	Title,
	TitleF,
};

// 북쪽부터 시계방향으로
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
