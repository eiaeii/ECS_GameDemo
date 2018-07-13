#pragma once

#include "core.h"
#include "component.h"

namespace terra
{
	enum class EInputEvent
	{
		IE_Pressed = 0,
		IE_Released = 1,
		IE_Repeat = 2,
		IE_DoubleClick = 3,
		IE_Axis = 4,
		IE_MAX = 5,
	};

	using ActionDelegate = std::function<void()>;
	struct ActionBinding
	{
		ActionBinding(int in_key_code, EInputEvent in_input_event, const ActionDelegate& func)
			: key_code(in_key_code)
			, input_event(in_input_event)
			, action_delegate(func)
		{}
		ActionBinding(int in_key_code, EInputEvent in_input_event, ActionDelegate&& func)
			: key_code(in_key_code)
			, input_event(in_input_event)
			, action_delegate(std::move(func))
		{}
		int key_code;
		EInputEvent input_event;
		ActionDelegate action_delegate;
	};

	class PlayerInputComponent : public BaseComponent
	{
	private:
		std::vector<ActionBinding> action_bindings_;
	public:
		using BaseComponent::BaseComponent;
		void Reset() override
		{
			ClearActionBindings();
		}

		void BindAction(int key_code, EInputEvent input_event, const ActionDelegate& func)
		{
			action_bindings_.emplace_back(key_code, input_event, func);
		}
		void BindAction(int key_code, EInputEvent input_event, ActionDelegate&& func)
		{
			action_bindings_.emplace_back(key_code, input_event, std::move(func));
		}
		void ClearActionBindings() { action_bindings_.clear(); }

		void ProcessInputEvent(int key_code, EInputEvent input_event) const
		{
			for (auto& e : action_bindings_)
			{
				if (e.key_code == key_code && e.input_event == input_event)
				{
					e.action_delegate();
				}
			}
		}
	};
}