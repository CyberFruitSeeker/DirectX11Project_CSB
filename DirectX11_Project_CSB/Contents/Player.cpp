#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

// 플레이어의 FVector를 초기화 해준다.
FVector APlayer::PlayerPosZero = FVector::Zero;

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	InputOn();
	SetRoot(Renderer);
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	
	Renderer->CreateAnimation("GuraIdle", "Gura", 0.1f, true, 0, 2);
	Renderer->CreateAnimation("GuraRun", "Gura", 0.1f, true, 5, 8);
	

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

//void APlayer::StateUpdate()
//{
//	PlayerMove();
//
//
//}

// 키입력시 플레이어 움직임 및 각종 애니메이션 발동
//void APlayer::PlayerMove(float _DeltaTime)
//{
//
//	// 방향 이동 : WASD
//	{
//		float Speed = 277.7f;
//
//		if (true == IsPress('A'))
//		{
//			AddActorLocation(FVector::Left * _DeltaTime * Speed);
//		}
//
//		if (true == IsPress('D'))
//		{
//			AddActorLocation(FVector::Right * _DeltaTime * Speed);
//		}
//
//		if (true == IsPress('W'))
//		{
//			AddActorLocation(FVector::Up * _DeltaTime * Speed);
//		}
//
//		if (true == IsPress('S'))
//		{
//			AddActorLocation(FVector::Down * _DeltaTime * Speed);
//		}
//
//	}


	//// 회전, 자전 같은거 테스트용 키들
	//{
	//	// 플레이어에게는 필요 없는 회전 기능
	//	// but, 공격 & 스킬 이펙트에는 필요할 것이다.
	//	if (true == IsPress(VK_NUMPAD1))
	//	{
	//		AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
	//		Color.X += _DeltaTime;
	//	}

	//	if (true == IsPress(VK_NUMPAD2))
	//	{
	//		Color.X -= _DeltaTime;
	//	}

	//	if (true == IsPress(VK_NUMPAD4))
	//	{
	//		Color.Y += _DeltaTime;
	//	}

	//	if (true == IsPress(VK_NUMPAD5))
	//	{
	//		Color.Y -= _DeltaTime;
	//	}

	//	if (true == IsPress(VK_NUMPAD7))
	//	{
	//		Color.Z += _DeltaTime;
	//	}

	//	if (true == IsPress(VK_NUMPAD8))
	//	{
	//		Color.Z -= _DeltaTime;
	//	}

	//}

//}
