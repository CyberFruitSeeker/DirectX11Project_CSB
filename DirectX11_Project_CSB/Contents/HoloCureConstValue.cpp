#include "PreCompile.h"
#include "HoloCureConstValue.h"

//const float4 HoloCureConstValue::GroundTileSize = { 3840.0f,3840.0f };
float HoloCureConstValue::MultipleSize = 2.0f;

const float4 HoloCureConstValue::GroundTileSize = { 2560.0f * MultipleSize, 2560.0f * MultipleSize };

float4 HoloCureConstValue::PlayLevelMousePos = float4::Zero;

const float HoloCureConstValue::BaseSpeed = 200.0f;
const float HoloCureConstValue::BaseHaste = 1.0f;
const float HoloCureConstValue::BasePUR = 40.0f;

