#pragma once

#include "Gemstone/Core/Input.h"

namespace Gemstone
{
	class WindowsInput : public Input
	{
	protected:
		// Keyboard
		virtual bool IsKeyPressedImpl(int keycode) override;
		// Mouse
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	};

}

