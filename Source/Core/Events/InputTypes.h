#pragma once

enum class EKey
{
	Unknown = -1,
	Spacebar = 32,
	Apostrophe = 39,
	Comma = 44,
	Minus,
	Period,
	Slash,
	N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
	Semicolon,
	Equal = 61,
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	LeftBracket,
	BackSlash,
	RightBracket,
	GraveAccent = 96,
	World1 = 161, World2,
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
	RageUp,
	RageDown,
	Home,
	End,
	CapsLock,
	ScrollLock,
	NumLock,
	PrintScreen,
	KeyPause,
	F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, 
	F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,
	F21, F22, F23, F24, F25,
	KP0 = 320, KP1, KP2, KP3, KP4, KP5, KP6, KP7, KP8, KP9,
	KPDecimal,
	KPDivide,
	KPMultiply,
	KPSubtract,
	KPAdd,
	KPEnter,
	KPEqual,
	LeftShift = 340,
	LeftControl,
	LeftAlt,
	LeftSuper,
	RightShift,
	RightControl,
	RightAlt,
	RightSuper,
	Menu
};

enum class EMouseButton
{
	Unknown = -1,
	Left,
	Right,
	Middle
};

enum class EKeyState
{
	Release,
	Press,
	Repeat
};