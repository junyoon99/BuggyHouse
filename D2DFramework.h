#pragma once
#include <d2d1.h>
#include <wincodec.h>
#include <wrl/client.h>
#include "ComException.h"

class D2DFramework
{
public:
	virtual HRESULT Init(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework",
UINT width = 1024, UINT height = 768);
	virtual void Release();
	virtual void Render();
	virtual int GameLoop();

public:
	ID2D1Factory* GetD2DFactory() { return mpD2dFactory.Get(); }
	ID2D1HwndRenderTarget* GetRenderTarget() { return mspRenderTarget.Get(); }
	HWND GetWindowHandle() { return mHwnd; }

protected:
	Microsoft::WRL::ComPtr<ID2D1Factory> mpD2dFactory{};
	Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> mspRenderTarget{};

	HRESULT InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height);
	HRESULT InitD2D();

	virtual HRESULT CreateDeviceResources();

protected:
	HWND mHwnd;

private:
	//헤더는 컴파일 대상이 아니기 때문에 int values[]{1,2,3,4,5} 같은 추측해야하는 코드는 사용 불가능
	const wchar_t* CLASS_NAME{ L"Direct2DSampleClass" };	//때문에 포인터로 두고 초기화식으로 정해주면 가능


};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
