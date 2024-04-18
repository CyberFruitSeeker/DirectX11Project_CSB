#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>


// ĳ����(�÷��̾�)���� ������, �ִϸ��̼��� �������� ����� �̰����ٰ� �����Ѵ�.
void APlayer::StateUpdate()
{
	// ī�޶� ����
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();

	// ���� ������Ʈ ����
	PlayerState.CreateState("Idle");
	PlayerState.CreateState("Run");
	PlayerState.CreateState("Die");


	// Idle, Run, Die ���� �Լ����� ����
	PlayerState.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	//PlayerState.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));

	// Idle ���·� ��ȭ�ϱ� ���� �͵�
	USpriteRenderer* HoloRender = Renderer;

	// �ݹ� ����� ����غ���.
	PlayerState.SetStartFunction("Idle", [=]
		{
			HoloRender->ChangeAnimation(Name + "_Idle");
		});


	PlayerState.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	PlayerState.SetStartFunction("Run", std::bind(&APlayer::RunStart, this));

	// Die�� ���Ŀ� ����

	//Renderer->SetAutoSize(1.0f, true);

	// �̵�Ű�� �Է����� ������, ���� Idle ���·� ü����
	PlayerState.ChangeState("Idle");

}

void APlayer::IdleStart()
{
	Renderer->ChangeAnimation("GuraIdle");
}

void APlayer::Idle(float _DeltaTime)
{
	// ||(OR) �����ڸ� �̿��Ͽ� WASD �Է½�, Idle ���¿��� Run ���·� ��ȯ�� �� �ְ� ������.
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		PlayerState.ChangeState("Run");
		return;
	}
	

}

void APlayer::Die(float _DeltaTime)
{

}



void APlayer::RunStart()
{
	Renderer->ChangeAnimation(Name + "_Run");
	
}

void APlayer::Run(float _DeltaTime)
{
	


	// ����Ű �Է¿� ���� ī�޶� ���� ���
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();

	// ���� �̵� WASD�� ���� Run�� Idle ��ȯ
	float Speed = 200.5f;

	if (true == IsPress('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
		Camera->AddActorLocation(FVector::Left * _DeltaTime * Speed);
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
		//SetActorScale3D(FVector(-160.0f, 160.0f, 100.0f));
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
		//SetActorScale3D(FVector(160.0f, 160.0f, 100.0f));
	}

	if (true == IsUp('D'))
	{
		//SetActorScale3D(FVector(256.0f, 256.0f, 100.0f));
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
	{
		// �÷��̾�Դ� �ʿ� ���� ȸ�� ���
		// but, ���� & ��ų ����Ʈ���� �ʿ��� ���̴�.
		// �켱 ���⿡�� �д�.
		if (true == IsPress(VK_NUMPAD1))
		{
			//AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
			//Color.X += _DeltaTime;
		}

		if (true == IsPress(VK_NUMPAD2))
		{
			Color.X -= _DeltaTime;
		}

		if (true == IsPress(VK_NUMPAD4))
		{
			Color.Y += _DeltaTime;
		}

		if (true == IsPress(VK_NUMPAD5))
		{
			Color.Y -= _DeltaTime;
		}

		if (true == IsPress(VK_NUMPAD7))
		{
			Color.Z += _DeltaTime;
		}

		if (true == IsPress(VK_NUMPAD8))
		{
			Color.Z -= _DeltaTime;
		}

	}


}




