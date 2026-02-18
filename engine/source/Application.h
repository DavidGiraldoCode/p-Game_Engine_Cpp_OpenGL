#pragma once

namespace eng
{
	class Application
	{
	public:
		/*
		* Implicit default constructor
		**/
		virtual ~Application() = default;

		virtual bool Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Destroy() = 0;

				void SetNeedsToBeClosed(bool value);
		const	bool NeedsToBeClosed() const;
		
	private:
		bool m_needsToBeClosed = false;
	};
}