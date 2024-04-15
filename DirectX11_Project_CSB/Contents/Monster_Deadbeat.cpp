#include "PreCompile.h"
#include "Monster_Deadbeat.h"
#include <EngineCore/DefaultSceneComponent.h>


Monster_Deadbeat::Monster_Deadbeat()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

Monster_Deadbeat::~Monster_Deadbeat()
{



}

void Monster_Deadbeat::BeginPlay()
{
}

void Monster_Deadbeat::Tick(float _DeltaTime)
{
}


