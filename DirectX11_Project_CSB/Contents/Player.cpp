#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"

// �÷��̾��� FVector�� �ʱ�ȭ ���ش�.
FVector APlayer::PlayerPosZero = FVector::Zero;

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	AttackDir = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	AttackDir->SetupAttachment(Root);
	AttackDir->SetPivot(EPivot::MAX);

	SetRoot(Root);
	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� ĳ���� Ŭ������ ������ �������� ����, ���⿡�� �����غ���.
	// ĳ���� �̸����� �����ϰ� �����ϴ� ���
	CreatePlayerAnimation("Gura");

	
	/*Renderer->CreateAnimation("GuraIdle", "Gura", 0.3f, true, (0,1),(1,2));
	Renderer->CreateAnimation("GuraRun", "Gura", 0.065f, true, (3,4,5),(6,7,8));*/
	
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Player);


	StateUpdate();
	
}

void APlayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);
	
	PlayerPosZero = GetActorLocation();




}

// ���ڿ��� ����� Idle�� Run �ִϸ��̼� ���� �� �ߵ�
void APlayer::CreatePlayerAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.3f, true, (0, 1), (1, 2));
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.065f, true, (3, 4, 5), (6, 7, 8));
}



