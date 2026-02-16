#pragma once
#include <eng.h>
#include <iostream>

class Game : public eng::Application
{
public:
	/// <summary>
	/// The `Init()` separates "object exists" from "object ready for use"
	/// </summary>
	/// <returns></returns>
	bool Init() 					override;
	void Update(float deltaTime) 	override;
	void Destroy() 					override;
};