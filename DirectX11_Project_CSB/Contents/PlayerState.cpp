#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Camera.h>
#include "HoloMouse.h"


// ĳ����(�÷��̾�)���� ������, �ִϸ��̼��� �������� ����� �̰����ٰ� �����Ѵ�.
void APlayer::StateUpdate()
{
	

	// �÷��̾� ������Ʈ ����
	PlayerState.CreateState("Idle");
	PlayerState.CreateState("Run");
	PlayerState.CreateState("Die");


	// Idle, Run, Die ���� �Լ����� ����
	PlayerState.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));

	// Idle ���·� ��ȭ�ϱ� ���� �͵�
	//USpriteRenderer* PlayerRender = Renderer;

	// �ݹ� ����� ����غ���.
	//PlayerState.SetStartFunction("Idle", [=]
	//	{
	//		PlayerRender->ChangeAnimation(Name + "_Idle");
	//	});


	PlayerState.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));

	// Die�� ���Ŀ� ����

	//Renderer->SetAutoSize(1.0f, true);

	// �̵�Ű�� �Է����� ������, ���� Idle ���·� ü����
	PlayerState.ChangeState("Idle");


	// ī�޶� ����
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
	// Idle ���¿��� Run ���·� ��ȯ�ϱ� ���� ��
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

	// ����Ű �Է¿� ���� ī�޶� ���� ���
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();

	// ���� �̵� WASD�� ���� Run�� Idle ��ȯ
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




