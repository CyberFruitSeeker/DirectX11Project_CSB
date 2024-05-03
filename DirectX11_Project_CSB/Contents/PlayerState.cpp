#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Camera.h>
#include "HoloMouse.h"
#include "HolocureEnum.h"


// 캐릭터(플레이어)들의 움직임, 애니메이션의 실질적인 기능은 이곳에다가 구현한다.
void APlayer::StateUpdate()
{
	// 플레이어 스테이트 세팅
	PlayerState.CreateState("Idle");
	PlayerState.CreateState("Run");
	PlayerState.CreateState("Die");


	// Idle, Run, Die 같은 애니메이션 함수들을 세팅
	PlayerState.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));

	// Idle 상태로 변화하기 위한 것들
	PlayerState.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));

	// Die는 추후에 구현

	// 이동키를 입력하지 않을때, 구라(캐릭터)를 Idle 상태로 체인지
	Renderer->SetAutoSize(1.3f, true);
	PlayerState.ChangeState("Idle");


	// 카메라 세팅
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
}

void APlayer::Die(float _DeltaTime)
{

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

void APlayer::Run(float _DeltaTime)
{

	// 방향키 입력에 따라서 카메라가 따라가줘야 하니깐
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();



	if (true == IsPress('W') && true == IsPress('A'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Left);
		AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		DirState = EPlayerDir::NW;
	}
	else if (true == IsPress('W') && true == IsPress('D'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Up * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Right);
		AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		DirState = EPlayerDir::NE;
	}
	else if (true == IsPress('S') && true == IsPress('A'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Left);
		AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * LineSpeed);
		DirState = EPlayerDir::SW;
	}
	else if (true == IsPress('S') && true == IsPress('D'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Down * _DeltaTime * LineSpeed);
		Renderer->SetDir(EEngineDir::Right);
		AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * LineSpeed);
		DirState = EPlayerDir::SE;
	}

	else if (true == IsPress('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * Speed);
		DirState = EPlayerDir::W;

	}
	else if (true == IsUp('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
		PlayerState.ChangeState("Idle");
	}

	else if (true == IsPress('D'))
	{
		Renderer->SetDir(EEngineDir::Right);
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Right * _DeltaTime * Speed);
		DirState = EPlayerDir::E;
	}
	else if (true == IsUp('D'))
	{
		Renderer->SetDir(EEngineDir::Right);
		PlayerState.ChangeState("Idle");
	}

	else if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Up * _DeltaTime * Speed);
		DirState = EPlayerDir::N;
	}
	else if (true == IsUp('W'))
	{
		PlayerState.ChangeState("Idle");
	}

	else if (true == IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
		Camera->AddActorLocation(FVector::Down * _DeltaTime * Speed);
		DirState = EPlayerDir::S;
	}
	else if (true == IsUp('S'))
	{
		PlayerState.ChangeState("Idle");
	}

}


void APlayer::KeyMove(float _DeltaTime, float4 _Dir, float _Speed)
{
	AddActorLocation(_Dir * _DeltaTime * _Speed);
	Camera->AddActorLocation(_Dir * _DeltaTime * _Speed);
}

void APlayer::KeyLineMove(float _DeltaTime, float4 _Dir1, float4 _Dir2)
{
	KeyMove(_DeltaTime, _Dir1, LineSpeed);
	KeyMove(_DeltaTime, _Dir2, LineSpeed);
}




