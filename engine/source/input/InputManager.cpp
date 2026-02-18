#include "input/InputManager.h"

namespace eng
{
	void InputManager::SetKeyPressed(int key, bool pressed)
	{
		if (key < 0 || key >= m_keysSize)
			return;

		m_keys[key] = pressed;
	}

	const bool InputManager::IsKeyPressed(int key)
	{
		if (key < 0 || key >= m_keysSize)
			return false;

		return m_keys[key];
	}
}