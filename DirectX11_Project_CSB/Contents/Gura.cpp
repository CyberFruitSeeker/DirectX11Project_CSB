#include "PreCompile.h"
#include "Gura.h"
#include "EngineCore/Actor.h"

AGura::AGura()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Collision");
	
	// 구라의 삼치창 파도 공격 콜리전

	CollisionR0 = CreateDefaultSubObject<UCollision>("Collision");
	CollisionR0->SetScale({ 30.0f * HoloCureConstValue::MultipleSize, 50.f * HoloCureConstValue::MultipleSize });
	CollisionR0->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR0->SetCollisionType(ECollisionType::CirCle);
	CollisionR0->SetupAttachment(Root);

	CollisionR1 = CreateDefaultSubObject<UCollision>("Collision");
	CollisionR1->SetScale({ 40.0f * HoloCureConstValue::MultipleSize, 50.f * HoloCureConstValue::MultipleSize });
	CollisionR1->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR1->SetCollisionType(ECollisionType::CirCle);
	CollisionR1->SetupAttachment(Root);

	CollisionR2 = CreateDefaultSubObject<UCollision>("Collision");
	CollisionR2->SetScale({ 50.0f * HoloCureConstValue::MultipleSize, 50.f * HoloCureConstValue::MultipleSize });
	CollisionR2->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR2->SetCollisionType(ECollisionType::CirCle);
	CollisionR2->SetupAttachment(Root);

	CollisionR3 = CreateDefaultSubObject<UCollision>("Collision");
	CollisionR3->SetScale({ 55.0f * HoloCureConstValue::MultipleSize, 50.f * HoloCureConstValue::MultipleSize });
	CollisionR3->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR3->SetCollisionType(ECollisionType::CirCle);
	CollisionR3->SetupAttachment(Root);

	//POARenderer->SetupAttachment(Root);


	


}

AGura::~AGura()
{
}

void AGura::BeginPlay()
{
	Super::BeginPlay();

	POARenderer->CreateAnimation("PowerOfAtlantis", "PowerOfAtlantis", 0.05f);
	POARenderer->SetAutoSize(4.0f, true);
	POARenderer->ChangeAnimation("PowerOfAtlantis");
	//POARenderer->SetOrder(ERenderingOrder::Skill);


	//Name = "GuraTridentAttack";

	Renderer->CreateAnimation("GuraAttack", "GuraAttack", 0.05f);
	Renderer->SetAutoSize(HoloCureConstValue::MultipleSize * 1.0f, true);
	Renderer->ChangeAnimation("GuraAttack");



	// 구라의 기본공격은 검 타입인가? or 거리(reach) 타입인가?
	// => 거리 타입이다.
	SetReachTypeMeleeLocation(50.0f);
	CollisionR0->SetActive(false);
	CollisionR1->SetActive(false);
	CollisionR2->SetActive(false);
	CollisionR3->SetActive(false);


	// 스킬 : 파워 오브 아틀란티스
	//POARenderer->CreateAnimation("PowerOfAtlantis", "PowerOfAtlantis", 0.05f);
	//POARenderer->SetAutoSize(4.0f, true);
	//POARenderer->ChangeAnimation("PowerOfAtlantis");


}

void AGura::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetReachTypeMeleeLocation(50.0f);

	if (true == Renderer->IsActive())
	{
		CollisionR0->SetActive(true);
		CollisionR1->SetRotationDeg(FVector(Root->GetLocalRotation().X, Root->GetLocalRotation().Y, Root->GetLocalRotation().Z + 45.f));
		CollisionR0->SetPosition(Root->GetLocalPosition());
		CollisionR0->AddPosition(Dir * 45.0f * HoloCureConstValue::MultipleSize);

		CollisionR1->SetActive(true);
		CollisionR1->SetRotationDeg(FVector(Root->GetLocalRotation().X, Root->GetLocalRotation().Y, Root->GetLocalRotation().Z + 45.f));
		CollisionR1->SetPosition(FVector(Root->GetLocalPosition().X, Root->GetLocalPosition().Y, Root->GetLocalPosition().Z));
		CollisionR1->AddPosition(Dir * 20.0f * HoloCureConstValue::MultipleSize);

		CollisionR2->SetActive(true);
		CollisionR2->SetRotationDeg(FVector(Root->GetLocalRotation().X, Root->GetLocalRotation().Y, Root->GetLocalRotation().Z + 45.f));
		CollisionR2->SetPosition(FVector(Root->GetLocalPosition().X, Root->GetLocalPosition().Y, Root->GetLocalPosition().Z));
		CollisionR2->AddPosition(Dir * -10.0f * HoloCureConstValue::MultipleSize);

		CollisionR3->SetActive(true);
		CollisionR3->SetRotationDeg(FVector(Root->GetLocalRotation().X, Root->GetLocalRotation().Y, Root->GetLocalRotation().Z + 45.f));
		CollisionR3->SetPosition(FVector(Root->GetLocalPosition().X, Root->GetLocalPosition().Y, Root->GetLocalPosition().Z));
		CollisionR3->AddPosition(Dir * -35.0f * HoloCureConstValue::MultipleSize);


		CheckHit();
	}
	else
	{
		CollisionR0->SetActive(false);
		CollisionR1->SetActive(false);
		CollisionR2->SetActive(false);
		CollisionR3->SetActive(false);
	}

	{

		FVector Pos = Root->GetLocalPosition() * Dir;
		UEngineDebugMsgWindow::PushMsg(std::format("RootPos : {}", Pos.ToString()));
	}



}

void AGura::CheckHit()
{
	{
		CollisionR0->
			CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
				{
					AMonster* Monster = dynamic_cast<AMonster*>(_Collison->GetActor());

					float Hp = Monster->GetHp();
					Hp -= Atk;
					Monster->SetHp(Hp);
				}
		);
	}

	{
		CollisionR1->
			CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
				{
					AMonster* Monster = dynamic_cast<AMonster*>(_Collison->GetActor());

					float Hp = Monster->GetHp();
					Hp -= Atk;
					Monster->SetHp(Hp);
				}
		);
	}

	{
		CollisionR2->
			CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
				{
					AMonster* Monster = dynamic_cast<AMonster*>(_Collison->GetActor());

					float Hp = Monster->GetHp();
					Hp -= Atk;
					Monster->SetHp(Hp);
				}
		);
	}

	{
		CollisionR3->
			CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
				{
					AMonster* Monster = dynamic_cast<AMonster*>(_Collison->GetActor());

					float Hp = Monster->GetHp();
					Hp -= Atk;
					Monster->SetHp(Hp);
				}
		);
	}


}

// 파워 오브 아틀란티스
void AGura::POARandomSpawn()
{
	



}

void AGura::POARandomLocation()
{

}


