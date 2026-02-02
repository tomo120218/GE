#include "Input.h"
#include <cassert>
//#define DIRECTINPUT_VERSION 0x0800
//#include <dinput.h>
//#include <wrl.h>
//using namespace Microsoft::WRL;

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

void Input::Initialize(WinApp* winApp)
{
    this->winApp_ = winApp;
    HRESULT result;
    // DirectInputのインスタンス生成
    ComPtr<IDirectInput8> directInput = nullptr;
    result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // キーボードデバイス生成
    //ComPtr<IDirectInputDevice8> keyboard;
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    assert(SUCCEEDED(result));

    // 入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard);
    assert(SUCCEEDED(result));

    // 協調レベルのセット
    result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{
    HRESULT result;
    memcpy(keyPre, key, sizeof(key));
    result = keyboard->Acquire();
    //BYTE key[256] = {};
    result = keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber) {
    if (key[keyNumber] && !keyPre[keyNumber]) {
        return true;
    }
    return false;
}

bool Input::TriggerKey(BYTE keyNumber) {
    if (key[keyNumber] && !keyPre[keyNumber]) {
        return true;
    }
    return false;
}

