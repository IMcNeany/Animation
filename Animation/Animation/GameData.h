#pragma once
#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include <dinput.h>

struct GameData
{
	float frameTick;
	unsigned char* m_prevKeyboardState;
	unsigned char* m_keyboardState;
	DIMOUSESTATE* m_mouseState;
};

#endif