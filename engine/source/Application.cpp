#include "Application.h"

namespace eng
{
	void Application::SetNeedsToBeClosed(bool value)
	{
		m_needsToBeClosed = value;
	}

	const bool Application::NeedsToBeClosed() const
	{
		return m_needsToBeClosed;
	}
}