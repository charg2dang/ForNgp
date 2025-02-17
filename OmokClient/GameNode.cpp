#include "stdafx.h"
#include "GameNode.h"

GameNode::GameNode() {

}

GameNode::~GameNode() {}

Image* GameNode::m_backBuffer = NULL;

Image* GameNode::SetBackBuffer() {
	// �� ������ �̱���
	if (m_backBuffer == NULL) {
		m_backBuffer = new Image;
		m_backBuffer->Init(WINSIZEX, WINSIZEY);
	}

	return m_backBuffer;
}

HRESULT GameNode::Init() {
	SetBackBuffer();
	_hdc = GetDC(g_hWnd);
	SetTimer(g_hWnd, 1, 10, NULL);
	return S_OK;
}

void GameNode::Release() {
	KillTimer(g_hWnd, 1);

	SAFE_DELETE(m_backBuffer);

	INPUT->GetSingleton();
}

void GameNode::Update() 
{
	InvalidateRect(g_hWnd, NULL, FALSE);
}

void GameNode::Render() {}

LRESULT GameNode::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg) 
	{
		case WM_TIMER:
			this->Update();
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			this->Render();
			EndPaint(hWnd, &ps);
			break;
		case WM_MOUSEMOVE:
			g_ptMouse.x = LOWORD(lParam);
			g_ptMouse.y = HIWORD(lParam);
			break;
		case WM_KEYDOWN:
			switch (wParam) 
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return (DefWindowProc(hWnd, msg, wParam, lParam));
}