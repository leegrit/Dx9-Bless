#pragma once

template <typename T>
struct ArrayDeleter
{
	void operator() (T* ptr)
	{
		delete[] ptr;
	}
};