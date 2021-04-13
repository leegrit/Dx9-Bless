#pragma once


__interface ISkybox
{
	virtual void Update() = 0;
	virtual void Render() = 0;
};