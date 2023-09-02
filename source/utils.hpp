#pragma once
/* @NOTE: Sorry if it's a mess, I don't really feel like doing something hyper-structured and clean, again I share for those who want to understand the reasoning. Use what I've done as you wish no matter what. */

HWND hwnd = NULL;
HWND hwnd_active = NULL;
HWND OverlayWindow = NULL;
bool showmenu = true;
bool rendering = true;
int frame = 0;
FOverlay* g_overlay;

vec3 screensize;
float ScreenCenterX;
float ScreenCenterY;

auto CrosshairColor = D2D1::ColorF(0, 100, 255, 255);

struct view_matrix_t {
    float* operator[ ](int index) {
        return matrix[index];
    }

    float matrix[4][4];
};

bool world_to_screen(const vec3& screen_size, const vec3& pos, vec3& out, view_matrix_t matrix) {
    out.x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
    out.y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];

    float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

    if (w < 0.01f)
        return false;

    float inv_w = 1.f / w;
    out.x *= inv_w;
    out.y *= inv_w;

    float x = screen_size.x * .5f;
    float y = screen_size.y * .5f;

    x += 0.5f * out.x * screen_size.x + 0.5f;
    y -= 0.5f * out.y * screen_size.y + 0.5f;

    out.x = x;
    out.y = y;

    return true;
}

namespace detail
{
    inline HWND window = 0;

    BOOL CALLBACK enum_windows(HWND hwnd, LPARAM param)
    {
        DWORD process_id;
        GetWindowThreadProcessId(hwnd, &process_id);
        if (process_id == param)
        {
            window = hwnd;
            return false;
        }
        return true;
    }
}

namespace esp
{
    inline bool box = true;

    inline bool health = true;
    inline bool healthT = true;

    inline bool distance = true;

    inline bool team = true;

    inline bool crosshair = true;

    inline bool FPS = true;
}

void DrawFilledRectangle(int x, int y, int w, int h, D2D1::ColorF color)
{
    D2D1_RECT_F rect = { x, y, x + w, y + h };
    g_overlay->draw_box(rect, color);
}


void DrawBorderBox(int x, int y, int x2, int y2, int thickness, D2D1::ColorF color)
{
    DrawFilledRectangle(x, y, x2, thickness, color); // top
    DrawFilledRectangle(x, y + y2, x2, thickness, color); // bottom
    DrawFilledRectangle(x, y, thickness, y2, color); // left
    DrawFilledRectangle(x + x2, y, thickness, y2 + thickness, color); // right
}


void DrawHealthbars(float x, float y, float width, float height, int thickness, int health)
{
    DrawFilledRectangle(x - (thickness + 5), y, thickness, height, D2D1::ColorF(0, 255, 0, 255));
    DrawFilledRectangle(x - (thickness + 5), y, thickness, height - ((height / 100) * health), D2D1::ColorF(255, 0, 0, 120));
    DrawBorderBox(x - (thickness + 5) - 1, y - 1, thickness + 1, height + 1, 1, D2D1::ColorF(0, 0, 0, 255));
}