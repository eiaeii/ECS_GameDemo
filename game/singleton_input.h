#pragma once

namespace terra
{
	enum EInputAction
	{
		EIA_Pressed,
		EIA_Repeat,
		EIA_Released,
	};

	struct InputState
	{
		InputState() :
			axis_right_value(0),
			axis_left_value(0),
			axis_forward_value(0),
			axis_back_value(0),
			is_fired(false)
		{}

		float GetDesiredHorizontalDelta()	const { return axis_right_value - axis_left_value; }
		float GetDesiredVerticalDelta()		const { return axis_forward_value - axis_back_value; }
		bool  IsFired()					const { return is_fired; }

	private:
		friend struct SingletonInput;
		float	axis_right_value, axis_left_value;
		float	axis_forward_value, axis_back_value;
		bool	is_fired;
	};
	

	struct SingletonInput
	{
		InputState current_state;
		void HandleInput(EInputAction input_action, int key_code);
	};
}