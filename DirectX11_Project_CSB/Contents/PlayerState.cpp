#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Camera.h>
#include "HoloMouse.h"


// 캐릭터(플레이어)들의 움직임, 애니메이션의 실질적인 기능은 이곳에다가 구현한다.
void APlayer::StateUpdate()
{
	

	// 플레이어 스테이트 세팅
	PlayerState.CreateState("Idle");
	PlayerState.CreateState("Run");
	PlayerState.CreateState("Die");


	// Idle, Run, Die 같은 함수들을 세팅
	PlayerState.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));

	// Idle 상태로 변화하기 위한 것들
	//USpriteRenderer* PlayerRender = Renderer;

	// 콜백 방식을 사용해본다.
	//PlayerState.SetStartFunction("Idle", [=]
	//	{
	//		PlayerRender->ChangeAnimation(Name + "_Idle");
	//	});


	PlayerState.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));

	// Die는 추후에 구현

	//Renderer->SetAutoSize(1.0f, true);

	// 이동키를 입력하지 않을때, 구라를 Idle 상태로 체인지
	PlayerState.ChangeState("Idle");


	// 카메라 세팅
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
}

void APlayer::IdleStart()
{
	Renderer->ChangeAnimation(Name + "_Idle");
}

void APlayer::RunStart()
{
	Renderer->ChangeAnimation(Name + "_Run");
	
}

void APlayer::Idle(float _DeltaTime)
{
	// Idle 상태에서 Run 상태로 전환하기 위한 것
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		PlayerState.ChangeState("Run");
		return;
	}

}

void APlayer::Die(float _DeltaTime)
{

}


void APlayer::Run(float _DeltaTime)
{

	// 방향키 입력에 따른 카메라 추적 기능
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();

	// 방향 이동 WASD에 따른 Run과 Idle 전환
	float Speed = 255.5f;

	if (true == IsPress('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * Speed);
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
		PlayerDir = EPlayerDir::W;
	}

	if (true == IsUp('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
		PlayerState.ChangeState("Idle");
	}

	if (true == IsPress('D'))
	{
		Renderer->SetDir(EEngineDir::Right);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * Speed);
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
		
	}

	if (true == IsUp('D'))
	{
		
		Renderer->SetDir(EEngineDir::Right);
		PlayerState.ChangeState("Idle");
	}

	if (true == IsPress('W'))
	{
		Camera->AddActorLocation(FVector::Up * _DeltaTime * Speed);
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == IsUp('W'))
	{
		PlayerState.ChangeState("Idle");
	}

	if (true == IsPress('S'))
	{
		Camera->AddActorLocation(FVector::Down * _DeltaTime * Speed);
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (true == IsUp('S'))
	{
		PlayerState.ChangeState("Idle");
	}

	// 회전, 자전 같은거 테스트용 키들
	//{
	//	// 플레이어에게는 필요 없는 회전 기능
	//	// but, 공격 & 스킬 이펙트에는 필요할 것이다.
	//	// 우선 여기에다 둔다.
	//	if (true == IsPress(VK_NUMPAD1))
	//	{
	//		//AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
	//		//Color.X += _DeltaTime;
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


}




