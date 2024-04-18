#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>
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
	// 캐릭터 이름으로 간단하게 변경하는 방식
	CreatePlayerAnimation("Gura");

	
	/*Renderer->CreateAnimation("GuraIdle", "Gura", 0.3f, true, (0,1),(1,2));
	Renderer->CreateAnimation("GuraRun", "Gura", 0.065f, true, (3,4,5),(6,7,8));*/
	
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Player);


	StateUpdate();
	
}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);
	
	PlayerPosZero = GetActorLocation();




}

// 문자열을 사용한 Idle과 Run 애니메이션 구분 및 발동
void APlayer::CreatePlayerAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.3f, true, (0, 1), (1, 2));
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.065f, true, (3, 4, 5), (6, 7, 8));
}



