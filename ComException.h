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
		assert(false);	//����â�� ���� �ٽýõ��� ������ �����
		throw com_exception(hr);
	}
}