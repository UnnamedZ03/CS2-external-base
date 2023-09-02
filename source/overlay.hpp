#define _CRT_SECURE_NO_WARNINGS

#ifndef FOverlay_H
#define FOverlay_H
#define M_PI 3.14159265
#include <windows.h>
#include <stdio.h>
#include <dwmapi.h> 
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <random>
#pragma comment(lib, "Dwrite")

#pragma comment(lib, "Dwmapi.lib") 
#pragma comment(lib, "d2d1.lib")

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

class FOverlay
{
public:
	static int ScreenHeight;
	static int ScreenWidth;
	auto window_set_style()-> void;
	auto window_set_transparency()-> void;
	auto window_set_top_most()-> void;
	auto retrieve_window()->HWND;
	void create_window();
	auto window_init()->BOOL;
	auto d2d_shutdown()-> void;
	auto init_d2d()->BOOL;
	auto begin_scene()-> void;
	auto end_scene()-> void;
	auto clear_scene()-> void;
	auto clear_screen()-> void;
	auto draw_text(int x, int y, D2D1::ColorF color, const char* str, ...) -> void;
	auto draw_line(int x1, int y1, int x2, int y2, D2D1::ColorF color) -> void;
	auto draw_box(D2D1_RECT_F rect, D2D1::ColorF color) -> void;
	auto draw_boxnew(int x, int y, float width, float height, D2D1::ColorF color) -> void;
	auto draw_circle(float x, float y, float r, float s, D2D1::ColorF color) -> void;

};

#endif