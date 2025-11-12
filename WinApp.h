#pragma once
#include <Windows.h>
#include <cstdint>
class WinApp
{
public:
	void Initialize();

	void Update();

	void Finalize();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//クライアント両雨域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	HWND GetHwnd() const { return hwnd; }

	HINSTANCE GetHInstance() const { return wc.hInstance; }

	bool ProcessMessage();

private:
	HWND hwnd = nullptr;

	WNDCLASS wc{};
};

