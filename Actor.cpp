#include "Actor.h"
#include "BitmapManager.h"

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename) :
	mpFramework(pFramework),
	mX(), mY(), mOpacity(1.0f)
{
	if (!pFramework)
	{
		ThrowIfFailed(E_INVALIDARG);
	}

	mpBitmap = BitmapManager::Instance().LoadBitmap(filename);
}

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity) :
	Actor(pFramework, filename)
{
	mX = x;
	mY = y;
	mOpacity = opacity;
}

Actor::~Actor()
{
}

void Actor::Draw()
{
	Draw(mX, mY, mOpacity);
}

void Actor::Draw(float x, float y, float opacity)
{
	auto size{ mpBitmap->GetPixelSize() };

	D2D1_RECT_F rct{
		x, y,
		(float)(x + size.width),
		(float)(y + size.height)
	};

	mpFramework->GetRenderTarget()->DrawBitmap(
		mpBitmap,
		rct,
		opacity
	);
}
