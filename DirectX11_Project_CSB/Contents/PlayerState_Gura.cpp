#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>

// ������ ������, �ִϸ��̼��� �������� ����� �̰����ٰ� �����Ѵ�.

void APlayer::StateUpdate()
{
	// ���� ������Ʈ ����
	GuraState.CreateState("Idle");
	GuraState.CreateState("Run");
	GuraState.CreateState("Die");


	// �Լ����� ����
	GuraState.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	// �ݹ��� �迭 ó�� �����ϰ� �ҷ��´�.
	// ex) �ݹ�[0] �ݹ�[1] �ݹ�[2][3][4][5][6]...[8]
	
	Renderer->SetFrameCallback("Run", 0, [=] 
		{
			int a = 0; 
		});


	// ���� �Լ�(ĸ��) ��� �غ���.
	GuraState.SetStartFunction("Idle", [this]()
		{
			this->Renderer->ChangeAnimation("GuraIdle");
		});

	GuraState.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	GuraState.SetUpdateFunction("Run", std::bind(&APlayer::RunStart, this));


	GuraState.ChangeState("Idle");
}



