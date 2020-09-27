#pragma once

#include <memory>

class Window;
enum class Key;
enum class Button;

class Input
{
public:
	Input(const std::shared_ptr<Window>& window);

	bool IsKeyPressed(const Key& key) const;
	bool IsButtonPressed(const Button& button) const;
private:
	std::shared_ptr<Window> window;
};

enum class Key
{ // glfw key codes
	// printable keys
	Unknown = -1,
	Space = 32,
	Apostrophe = 39, // '
	Comma = 44, // ,
	Minus, // -
	Period, // .
	Slash, // /
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	Semicolon = 59, // ;
	Equal = 61, // =
	A = 65,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	LBracket, // [
	Backslash, // \ 
	RBracket, // ]
	GraveAccent = 96, // `
	World1 = 161, // WTF is that
	World2 = 162, // WTF is that
	// function keys
	Escape = 256,
	Enter,
	Tab,
	Backspace,
	Insert,
	Delete,
	Right,
	Left,
	Down,
	Up,
	PageUp,
	PageDown,
	Home,
	End,
	CapsLock,
	ScrollLock,
	NumLock,
	PrintScreen,
	Pause,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	F25, // but why so many f's?
	KP0 = 320,
	KP1,
	KP2,
	KP3,
	KP4,
	KP5,
	KP6,
	KP7,
	KP8,
	KP9,
	KPDecimal,
	KPDivide,
	KPMultiply,
	KPSubtract,
	KPAdd,
	KPEqual,
	LShift,
	LControl,
	LAlt,
	LSuper,
	RShift,
	RControl,
	RAlt,
	RSuper,
	Menu
};

enum class Button
{
	Left = 0,
	Right,
	Middle,
	_4,
	_5,
	_6,
	_7,
	_8
};