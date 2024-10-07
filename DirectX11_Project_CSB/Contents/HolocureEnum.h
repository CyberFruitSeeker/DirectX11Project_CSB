#pragma once

enum class ECollisionOrder
{
	Player,
	Menu,
	LevelMenu,
	Mouse,
	MapObject,
	Weapon,
	Items,
	Monster,
	SmolAme,
};

enum class ELayerOrder
{
	BackLayer,
	FrontLayer,
	EffectLayer,
	UILayer,
};

// ��ġ �Ǵ� ����? : ���� �ö󰥼��� �� �Ʒ����� ��ġ�ȴ�.
// ��, "�Ʒ��� ������ ���� ��ġ��"
enum class ERenderingOrder
{
	//Title,
	//TitleF,
	Back,
	Title,
	Menu,
	TitleF,
	Skill,
	Front,
	Mouse,
	Attack,
	Player,
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
