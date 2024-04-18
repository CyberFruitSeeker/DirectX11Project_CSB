#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"

// 플레이어의 FVector를 초기화 해준다.
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

	// 플레이어 캐릭터 클래스를 여러개 생성하지 말고, 여기에다 구현해본다.

	
	Renderer->CreateAnimation("GuraIdle", "Gura", 0.3f, true, (0,1),(1,2));
	Renderer->CreateAnimation("GuraRun", "Gura", 0.065f, true, (3,4,5),(6,7,8));
	

	StateUpdate();
	Renderer->SetOrder(ERenderingOrder::Player);
	
}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);
	
	PlayerPosZero = GetActorLocation();

	


}


