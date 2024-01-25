/*
 *	@File	XController.h
 *	@Brief	Xboxコントローラー。
 *	@Date	2023-12-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef XCONTROLLER
#define XCONTROLLER

#include <GamePad.h>

class XController
{
private:
    std::unique_ptr<DirectX::GamePad> m_gamePad;
    DirectX::GamePad::ButtonStateTracker m_padTracker;

private:
    XController();

public:
    static XController* GetInstance()
    {
        static XController x;
        return &x;
    }

    ~XController();

    void Update();

    const DirectX::GamePad::ButtonStateTracker& GetPadTrack();
};

#endif // XCONTROLLER