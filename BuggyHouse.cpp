#include "BuggyHouse.h"
#include "Bug.h"

HRESULT BuggyHouse::Init(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	HRESULT hr = D2DFramework::Init(hInstance, title, width, height);
	ThrowIfFailed(hr);

	mspBackground = std::make_unique<Actor>(this, L"Images/Back1_1024.png");

	for (int i{}; i < 400; ++i) 
	{
		mBugs.push_back(
			std::make_shared<Bug>(this)
		);
	}

	return S_OK;
}

void BuggyHouse::Release()
{
	for (auto& bug : mBugs) 
	{
		bug.reset();
	}
	mBugs.clear();
	mspBackground.reset();
	D2DFramework::Release();
}

void BuggyHouse::Render()
{
	// 3. �׸���
	mspRenderTarget->BeginDraw();

	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
	mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	CheckBugs();
	mspBackground->Draw();

	for (auto& bug : mBugs) 
	{
		bug->Draw();
	}


	HRESULT hr = mspRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}

void BuggyHouse::CheckBugs()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) 
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(mHwnd, &pt);

		// remove�� �����̳� �ڷ� �̷�δ� �� {1,2,4,5} 3
		// erase�� ����� �޸� �������� �ϴ� �� {1,2, ,4,5}
		// erase�� �������� ���� �����͸� ��ȯ
		// �׷��� remove�� ����͵��� �� �ڷ� �̷���� erase�� �ڿ��ִ� �ֵ��� �� �����ֱ�
		
		//erase-remove idiom
		auto it = std::remove_if(mBugs.begin(), mBugs.end(),
			[&](auto& bug) { return bug.get()->IsClicked(pt); }
		);

		mBugs.erase(it, mBugs.end());
	}
}
