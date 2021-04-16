#pragma once

namespace HyEngine
{
	__interface IUserInterface 
	{
		virtual void Update() = 0;
		virtual void Render() = 0;
	};

}