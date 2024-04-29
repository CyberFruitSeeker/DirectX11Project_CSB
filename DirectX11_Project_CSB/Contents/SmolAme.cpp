#include "PreCompile.h"
#include "SmolAme.h"

ASmolAme::ASmolAme()
{
}

ASmolAme::~ASmolAme()
{
}

void ASmolAme::BeginPlay()
{
}

void ASmolAme::Tick(float _DeltaTime)
{
}


// 스몰 아메의 패턴 상태변화 :
// Walk => Jump => Jumping(circle shadow) => GroundPound => Walk

void ASmolAme::SmolAmeWalk(std::string _Name)
{
}

void ASmolAme::SmolAmeJumpStart()
{
}

void ASmolAme::SmolAmeJump(std::string _Name)
{
}

void ASmolAme::SmolAmeJumping(std::string _Name)
{
}

void ASmolAme::SmolAmeGroundPound(std::string _Name)
{
}

void ASmolAme::SmolAmeWalkStart()
{
}

void ASmolAme::CreateSmolAmeAnimation(std::string _Name)
{

}

void ASmolAme::Move(float _DeltaTime, EMonsterMoveType _MoveType)
{

}

