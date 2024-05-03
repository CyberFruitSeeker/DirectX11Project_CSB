#include "PreCompile.h"
#include "Gura.h"

AGura::AGura()
{
	CollisionR0 = CreateDefaultSubObject<UCollision>("Collision");
	CollisionR0->SetScale({ 50.0f * HoloCureConstValue::MultipleSize, 50.f * HoloCureConstValue::MultipleSize });
	//CollisionR0->SetupAttachment(Root);

	CollisionR0->SetCollisionGroup(ECollisionOrder::Weapon);
	CollisionR0->SetCollisionType(ECollisionType::Rect);


}

AGura::~AGura()
{
}

void AGura::BeginPlay()
{
	Super::BeginPlay();


	Name = "GuraTrident";

	Renderer->CreateAnimation("GuraAttack", "GuraAttack", 0.05f);
	Renderer->SetAutoSize(HoloCureConstValue::MultipleSize, true);
	Renderer->ChangeAnimation("GuraAttack");

	SetKnifeTypeMeleeLocation(35.0f);
	CollisionR0->SetActive(false);

}

void AGura::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetKnifeTypeMeleeLocation(35.0f);

	if (true == Renderer->IsActive())
	{
		CollisionR0->SetActive(true);
		CollisionR0->SetPosition(Root->GetLocalPosition());
		CollisionR0->AddPosition(Dir * 50.0f * HoloCureConstValue::MultipleSize);

		CheckHit();
	}
	else
	{
		CollisionR0->SetActive(false);
	}



}

void AGura::CheckHit()
{
	CollisionR0->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			AMonster* Monster = dynamic_cast<AMonster*>(_Collison->GetActor());

			float Hp = Monster->GetHp();
			Hp -= Atk;
			Monster->SetHp(Hp);
		}
	);


}
