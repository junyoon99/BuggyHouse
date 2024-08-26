#pragma once
#include <exception>
#include <cassert>
#include <stdio.h>
#include <winerror.h>

class com_exception : public std::exception
{
public:
	com_exception(HRESULT hr) : result(hr) {}
	virtual const char* what() const override
	{
		static char str[64]{};

		sprintf_s(str, "Fail with HRESULT code : %X", (unsigned int)result);
		return str;
	}

private:

	HRESULT result;
};

inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		assert(false);	//에러창을 띄우고 다시시도를 누르면 디버깅
		throw com_exception(hr);
	}
}