#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(350.0f, 350.0f, 100.0f));

	// PlayGameMode ���� �ε� �������� ���⼭ ��������Ʈ�� �Ѵ�.
	//Renderer->SetSprite("Gura_Idle_0.png");

	
}

void APlayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);

	


}

void APlayer::StateUpdate()
{
	//PlayerMove();


}

// Ű�Է½� �÷��̾� ������ �� ���� �ִϸ��̼� �ߵ�
void APlayer::PlayerMove(float _DeltaTime)
{

	// ���� �̵� : WASD
	{
		float Speed = 277.7f;

		if (true == IsPress('A'))
		{
			AddActorLocation(FVector::Left * _DeltaTime * Speed);
		}

		if (true == IsPress('D'))
		{
			AddActorLocation(FVector::Right * _DeltaTime * Speed);
		}

		if (true == IsPress('W'))
		{
			AddActorLocation(FVector::Up * _DeltaTime * Speed);
		}

		if (true == IsPress('S'))
		{
			AddActorLocation(FVector::Down * _DeltaTime * Speed);
		}

	}


	// ȸ��???
	{
		// �÷��̾�Դ� �ʿ� ���� ȸ�� ���
		// but, ���� & ��ų ����Ʈ���� �ʿ��� ���̴�.
		if (true == IsPress(VK_NUMPAD1))
		{
			AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
			Color.X += _DeltaTime;
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
