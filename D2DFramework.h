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
	//����� ������ ����� �ƴϱ� ������ int values[]{1,2,3,4,5} ���� �����ؾ��ϴ� �ڵ�� ��� �Ұ���
	const wchar_t* CLASS_NAME{ L"Direct2DSampleClass" };	//������ �����ͷ� �ΰ� �ʱ�ȭ������ �����ָ� ����


};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
