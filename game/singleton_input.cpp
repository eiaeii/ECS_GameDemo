#include "singleton_input.h"
#include <cassert>
using namespace terra;

namespace
{
	inline void UpdateDesireVariableFromKey(EInputAction input_action, bool& io_var)
	{
		if (input_action == EIA_Pressed)
		{
			io_var = true;
		}
		else if (input_action == EIA_Released)
		{
			io_var = false;
		}
	}

	inline void UpdateDesireFloatFromKey(EInputAction input_action, float& io_var)
	{
		if (input_action == EIA_Pressed)
		{
			io_var = 1.f;
		}
		else if (input_action == EIA_Released)
		{
			io_var = 0.f;
		}
	}
}

//void SingletonInput::HandleInput(EInputAction input_action, int key_code)
//{
//	switch (key_code)
//	{
//	case 'a':
//		UpdateDesireFloatFromKey(input_action, current_state.axis_left_value);
//		break;
//	case 'd':
//		UpdateDesireFloatFromKey(input_action, current_state.axis_right_value);
//		break;
//	case 'w':
//		UpdateDesireFloatFromKey(input_action, current_state.axis_forward_value);
//		break;
//	case 's':
//		UpdateDesireFloatFromKey(input_action, current_state.axis_back_value);
//		break;
//	case 'k':
//		UpdateDesireVariableFromKey(input_action, current_state.is_fired);
//		break;
//	default:
//		break;
//	}
//}

void SingletonInput::OnKeyDownEvent(int key_code)
{
	assert(key_code >= 0 && key_code < 0xFF);
	key_state_[key_code] = true;
}

void SingletonInput::OnKeyUpEvent(int key_code)
{
	assert(key_code >= 0 && key_code < 0xFF);
	key_state_[key_code] = false;
}

bool SingletonInput::IsKeyDown(int key_code)
{
	assert(key_code >= 0 && key_code < 0xFF);
	return key_state_[key_code];
}
