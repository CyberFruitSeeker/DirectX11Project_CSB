#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Camera.h>
#include "HoloMouse.h"
#include "HolocureEnum.h"


// ĳ����(�÷��̾�)���� ������, �ִϸ��̼��� �������� ����� �̰����ٰ� �����Ѵ�.
void APlayer::StateUpdate()
{
	// �÷��̾� ������Ʈ ����
	PlayerState.CreateState("Idle");
	PlayerState.CreateState("Run");
	PlayerState.CreateState("Die");


	// Idle, Run, Die ���� �ִϸ��̼� �Լ����� ����
	PlayerState.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));

	// Idle ���·� ��ȭ�ϱ� ���� �͵�
	PlayerState.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));

	// Die�� ���Ŀ� ����

	// �̵�Ű�� �Է����� ������, ����(ĳ����)�� Idle ���·� ü����
	Renderer->SetAutoSize(1.5f, true);
	PlayerState.ChangeState("Idle");


	// ī�޶� ����
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
	// Idle ���¿��� Run ���·� ��ȯ�ϱ� ���� ��
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		PlayerState.ChangeState("Run");
		return;
	}

}

void APlayer::Run(float _DeltaTime)
{

	// ����Ű �Է¿� ���� ī�޶� ������� �ϴϱ�
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

	// ȸ��, ���� ������ �׽�Ʈ�� Ű��
	//{
	//	// �÷��̾�Դ� �ʿ� ���� ȸ�� ���
	//	// but, ���� & ��ų ����Ʈ���� �ʿ��� ���̴�.
	//	// �켱 ���⿡�� �д�.
	//	if (true == IsPress(VK_NUMPAD1))
	//	{
	//		//AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
	//		//Color.X += _DeltaTime;
	//	}
	//
	// �䷱������ ȸ�� ����� �ʿ��Ҷ� �߰��غ���.



}




