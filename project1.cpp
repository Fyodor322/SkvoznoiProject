// project1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "project1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int Racing_x = 0;
int Racing_y = 0;

void DrawWeel(HDC hdc, int x, int y, int x1, int y1)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));

    SelectObject(hdc, hBrush);
    POINT pt[9];
    pt[0].x = 181 + x + x1;
    pt[1].x = 178 + x + x1;
    pt[2].x = 178 + x + x1;
    pt[3].x = 181 + x + x1;
    pt[4].x = 189 + x + x1;
    pt[5].x = 192 + x + x1;       //функция рисования колёс
    pt[6].x = 192 + x + x1;
    pt[7].x = 189 + x + x1;
    pt[8].x = 181 + x + x1;

    pt[0].y = 92 + y + y1;
    pt[1].y = 95 + y + y1;
    pt[2].y = 118 + y + y1;
    pt[3].y = 122 + y + y1;
    pt[4].y = 122 + y + y1;
    pt[5].y = 118 + y + y1;
    pt[6].y = 95 + y + y1;
    pt[7].y = 92 + y + y1;
    pt[8].y = 92 + y + y1;

    Polygon(hdc, pt, 9);
}
void DrawRacingCar(HDC hdc, int x, int y)
{
    HBRUSH hBrush;
    HPEN hPen;
    hBrush = CreateSolidBrush(RGB(237, 28, 36));        //кузов
    SelectObject(hdc, hBrush);
    RECT rect = { 120 + x, 90 + y, 160 + x, 210 + y }; 
    FillRect(hdc, &rect, hBrush);


    SelectObject(hdc, hBrush);
    rect = { 80 + x, 60 + y, 200 + x, 90 + y };         //переднее антикрыло
    FillRect(hdc, &rect, hBrush);

    SelectObject(hdc, hBrush);
    rect = { 120 + x, 230 + y, 160 + x, 245 + y };         //заднее антикрыло
    FillRect(hdc, &rect, hBrush);

    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, 140 + x, 130 + y, 0);
    LineTo(hdc, 130 + x, 160 + y);              //кабина пилота
    LineTo(hdc, 150 + x, 160 + y);
    LineTo(hdc, 140 + x, 130 + y);

    MoveToEx(hdc, 160 + x, 105 + y, 0);
    LineTo(hdc, 180 + x, 105 + y);
    LineTo(hdc, 160 + x, 120 + y);
    //крепления колёс
    MoveToEx(hdc, 120 + x, 105 + y, 0);
    LineTo(hdc, 100 + x, 105 + y);
    LineTo(hdc, 120 + x, 120 + y);


    HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hBrush2);
    POINT pt[4];
    pt[0].x = 122 + x;
    pt[1].x = 133 + x;
    pt[2].x = 147 + x;                      //задний треугольник
    pt[3].x = 155 + x;
    pt[0].y = 210 + y;
    pt[1].y = 230 + y;
    pt[2].y = 230 + y;
    pt[3].y = 210 + y;

    Polygon(hdc, pt, 4);

    SelectObject(hdc, hPen);
    MoveToEx(hdc, 127 + x, 219 + y, 0);             //левое крепление колеса
    LineTo(hdc, 103 + x, 229 + y);

    MoveToEx(hdc, 155 + x, 219 + y, 0);             //правое крепление колеса
    LineTo(hdc, 177 + x, 229 + y);

    DrawWeel(hdc, 0, 0, x, y);
    DrawWeel(hdc, -90, 0, x, y);                    //колёса
    DrawWeel(hdc, 0, 118, x, y);
    DrawWeel(hdc, -90, 118, x, y);
}

void DrawCar(HDC hdc, int x, int y)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(63, 72, 204));
    SelectObject(hdc, hBrush);

    POINT pt[10];
    pt[0].x = 362 + x;
    pt[1].x = 411 + x;
    pt[2].x = 425 + x;
    pt[3].x = 425 + x;
    pt[4].x = 411 + x;
    pt[5].x = 411 + x;
    pt[6].x = 362 + x;
    pt[7].x = 348 + x;
    pt[8].x = 348 + x;
    pt[9].x = 362 + x;
    //кузов 
    pt[0].y = 48 + y;
    pt[1].y = 48 + y;
    pt[2].y = 62 + y;
    pt[3].y = 187 + y;
    pt[4].y = 201 + y;
    pt[5].y = 201 + y;
    pt[6].y = 201 + y;
    pt[7].y = 187 + y;
    pt[8].y = 62 + y;
    pt[9].y = 48 + y;
    Polygon(hdc, pt, 10);

    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, hPen);

    MoveToEx(hdc, 362 + x, 48 + y, 0);
    LineTo(hdc, 411 + x, 48 + y);
    LineTo(hdc, 425 + x, 62 + y);
    LineTo(hdc, 425 + x, 187 + y);
    LineTo(hdc, 411 + x, 201 + y);
    LineTo(hdc, 411 + x, 201 + y);
    LineTo(hdc, 362 + x, 201 + y);
    LineTo(hdc, 348 + x, 187 + y);
    LineTo(hdc, 348 + x, 62 + y);
    LineTo(hdc, 362 + x, 48 + y);

    int x1 = 427 + x, y1 = 112 + y, x2 = 427 + x, y2 = 98 + y;
    while (y1 >= 106 + y)
    {
        hPen = CreatePen(PS_SOLID, 1, RGB(63, 72, 204));
        SelectObject(hdc, hPen);
        MoveToEx(hdc, x1, y1, 0);
        LineTo(hdc, x2, y2);
        x1++;
        y1--;
        x2++;
        y2++;
    }
    x1 = 347 + x, y1 = 112 + y, x2 = 347 + x, y2 = 98 + y;      //зеркала заднего вида
    while (x1 >= 339 + x)
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(63, 72, 204));
        SelectObject(hdc, hPen);
        MoveToEx(hdc, x1, y1, 0);
        LineTo(hdc, x2, y2);
        x1--;
        y1--;
        x2--;
        y2++;
    }
    HBRUSH hBrushs, hBrush2, hBrush3;
    hBrushs = CreateSolidBrush(RGB(255, 242, 0));
    hBrush2 = CreateSolidBrush(RGB(0, 0, 0));
    hBrush3 = CreateSolidBrush(RGB(153, 217, 234));

    SelectObject(hdc, hBrushs);
    RECT rect = { 361 + x, 63 + y, 375 + x, 68 + y };           //левая фара
    FillRect(hdc, &rect, hBrushs);

    RECT rect2 = { 361 + 38 + x, 63 + y, 375 + 38 + x, 68 + y };   //правая фара
    FillRect(hdc, &rect2, hBrushs);

    SelectObject(hdc, hBrush2);
    RECT rect3 = { 363 + x, 98 + y, 410 + x, 112 + y };
    FillRect(hdc, &rect3, hBrush2);
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, 366 + x, 97 + y, 0);
    LineTo(hdc, 407 + x, 97 + y);                           //лобовое стекло
    MoveToEx(hdc, 368 + x, 96 + y, 0);
    LineTo(hdc, 404 + x, 96 + y);
    MoveToEx(hdc, 371 + x, 95 + y, 0);
    LineTo(hdc, 401 + x, 95 + y);
    
    HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(153, 217, 234));
    SelectObject(hdc, hPen2);
    MoveToEx(hdc, 353 + x, 112 + y, 0);
    LineTo(hdc, 353 + x, 156 + y);
    MoveToEx(hdc, 354 + x, 114 + y, 0);
    LineTo(hdc, 354 + x, 154 + y);
    MoveToEx(hdc, 355 + x, 116 + y, 0);                                 //левое стекло
    LineTo(hdc, 355 + x, 152 + y);
    MoveToEx(hdc, 356 + x, 118 + y, 0);
    LineTo(hdc, 356 + x, 150 + y);
    MoveToEx(hdc, 357 + x, 120 + y, 0);
    LineTo(hdc, 357 + x, 148 + y);

    MoveToEx(hdc, 421 + x, 112 + y, 0);
    LineTo(hdc, 421 + x, 156 + y);
    MoveToEx(hdc, 420 + x, 114 + y, 0);
    LineTo(hdc, 420 + x, 154 + y);
    MoveToEx(hdc, 419 + x, 116 + y, 0);                                 //правое стекло
    LineTo(hdc, 419 + x, 152 + y);
    MoveToEx(hdc, 418 + x, 118 + y, 0);
    LineTo(hdc, 418 + x, 150 + y);
    MoveToEx(hdc, 417 + x, 120 + y, 0);
    LineTo(hdc, 417 + x, 148 + y);

    SelectObject(hdc, hBrush3);
    RECT rect4 = { 363 + x, 167 + y, 410 + x, 177 + y };
    FillRect(hdc, &rect4, hBrush3);
    SelectObject(hdc, hPen2);                           //заднее стекло
    x1 = 366 + x, x2 = 406 + x;
    int yf = 177 + y;
    while (yf <= 184 + y)
    {
        MoveToEx(hdc, x1, yf, 0);
        LineTo(hdc, x2, yf);
        yf++;
        x1++;
        x2--;
    }
}
void DrawRam(HDC hdc, int x, int y)
{
    HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0));        //чёрная
    HBRUSH hBrush = CreateSolidBrush(RGB(185, 122, 87));    //коричневая
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(185, 122, 87));  //коричневая 
    HBRUSH hBrush1 = CreateSolidBrush(RGB(127, 127, 127)); //серая


    SelectObject(hdc, hBrush2);
    POINT pt1[4];
    pt1[0].x = 586 + x;
    pt1[1].x = 586 + x;
    pt1[2].x = 594 + x;                      //левая ручка
    pt1[3].x = 594 + x;

    pt1[0].y = 100 + y;
    pt1[1].y = 148 + y;
    pt1[2].y = 148 + y;
    pt1[3].y = 100 + y;

    Polygon(hdc, pt1, 4);

    POINT pt[4];
    pt[0].x = 586+20 + x;
    pt[1].x = 586+20 + x;
    pt[2].x = 594+20 + x;                      //правая ручка
    pt[3].x = 594+20 + x;

    pt[0].y = 100 + y;
    pt[1].y = 148 + y;
    pt[2].y = 148 + y;
    pt[3].y = 100 + y;

    Polygon(hdc, pt, 4);

    SelectObject(hdc, hBrush);
    RECT rect = { 551 + x, 153 + y, 649 + x, 171 + y };     //бревно
    FillRect(hdc, &rect, hBrush);

    SelectObject(hdc, hPen);
    int x1 = 552 + x, x2 = 648 + x, yf = 152 + y;        //закругление сверху
    while (yf >= 148 + y)
    {
        MoveToEx(hdc, x1, yf, 0);
        LineTo(hdc, x2, yf);
        yf--;
        x1++;
        x2--;
    }

    x1 = 552 + x, x2 = 648 + x, yf = 171 + y;            //закругление снизу
    while (yf <= 176 + y)
    {
        MoveToEx(hdc, x1, yf, 0);
        LineTo(hdc, x2, yf);
        yf++;
        x1++;
        x2--;
    }

    SelectObject(hdc, hBrush1);
    POINT pt2[11];
    pt2[0].x = 558 + x;
    pt2[1].x = 558+8 + x;
    pt2[2].x = 558 + 8*2 + x;
    pt2[3].x = 558 + 8 * 3 + x;
    pt2[4].x = 558 + 8 * 4 + x;
    pt2[5].x = 558 + 8 * 5 + x;
    pt2[6].x = 558 + 8 * 6 + x;
    pt2[7].x = 558 + 8 * 7 + x;
    pt2[8].x = 558 + 8 * 8 + x;
    pt2[9].x = 558 + 8 * 9 + x;
    pt2[10].x = 558 + 8 * 10 + x;
                                        //шипы
    pt2[0].y = 177 + y;
    pt2[1].y = 192 + y;
    pt2[2].y = 177 + y;
    pt2[3].y = 192 + y;
    pt2[4].y = 177 + y;
    pt2[5].y = 192 + y;
    pt2[6].y = 177 + y;
    pt2[7].y = 192 + y;
    pt2[8].y = 177 + y;
    pt2[9].y = 192 + y;
    pt2[10].y = 177 + y;

    Polygon(hdc, pt2, 11);
}
void DrawWrench(HDC hdc, int x, int y)
{
    HBRUSH hBrush1 = CreateSolidBrush(RGB(127, 127, 127)); //серая
    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

    SelectObject(hdc, hPen);                            //головка 
    Arc(hdc, 729 + x, 66 + y, 766 + x, 109 + y, 730 + x, 93 + y, 752 + x, 67 + y);
    MoveToEx(hdc, 730 + x, 91 + y, 0);
    LineTo(hdc, 750 + x, 91 + y);
    LineTo(hdc, 750 + x, 66 + y);

    MoveToEx(hdc, 739 + x, 108 + y, 0);
    LineTo(hdc, 739 + x, 176 + y);
    LineTo(hdc, 741 + x, 184 + y);                      //ручка
    LineTo(hdc, 753 + x, 184 + y);
    LineTo(hdc, 756 + x, 176 + y);
    LineTo(hdc, 756 + x, 108 + y);

    Ellipse(hdc, 744 + x, 169 + y, 752 + x, 179 + y);       //крючок

    MoveToEx(hdc, 729 + x, 83 + y, 0);
    LineTo(hdc, 743 + x, 74 + y);
    LineTo(hdc, 743 + x, 70 + y);
    LineTo(hdc, 741 + x, 68 + y);
    LineTo(hdc, 731 + x, 68 + y);
    LineTo(hdc, 729 + x, 71 + y);
    LineTo(hdc, 729 + x, 83 + y);
}
void DrawFuel(HDC hdc, int x, int y)
{
    HPEN hPen = CreatePen(PS_SOLID, 8, RGB(74, 74, 74));
    HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(127, 127, 127));
    HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(142, 28, 36));
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 127, 39));
    
    SelectObject(hdc, hPen);
    Ellipse(hdc, 822 + x, 156 + y, 902 + x, 187 + y);   //обод бочки

    MoveToEx(hdc, 901 + x, 173 + y, 0);
    LineTo(hdc, 901 + x, 283 + y);
    LineTo(hdc, 823 + x, 283 + y);          //обводка корпуса
    LineTo(hdc, 823 + x, 173 + y);

    SelectObject(hdc, hPen1);
    POINT pt[4];
    pt[0].x = 827 + x;
    pt[1].x = 827 + x;
    pt[2].x = 896 + x;
    pt[3].x = 896 + x;
                                    //заливка корпуса
    pt[0].y = 190 + y; 
    pt[1].y = 278 + y;
    pt[2].y = 278 + y;
    pt[3].y = 190 + y;
    Polygon(hdc, pt, 4);

    SelectObject(hdc, hPen1);

    int x1 = 896 + x, x2 = 901 - 27 + x, yf = 189 + y;
    while (yf>=183 + y)
    {
        MoveToEx(hdc, x1, yf, 0);            
        LineTo(hdc, x2, yf);
        x2+=2;
        yf--;
    }           //дозаливка справа

    SelectObject(hdc, hPen1);

    x1 = 896 + x, x2 = 901 - 27 + x, yf = 189 + y;
    while (yf >= 183 + y)
    {
        MoveToEx(hdc, x1-48, yf, 0);
        LineTo(hdc, x2-48, yf);
        x1 -= 2;
        yf--;
    }       //дозаливка слева

    RECT rect1 = { 855 + x, 254 + y, 863 + x, 252 + y };
    RECT rect2 = { 848 + x, 252 + y, 868 + x, 248 + y };
    RECT rect3 = { 845 + x, 248 + y, 872 + x, 233 + y };
    RECT rect4 = { 848 + x, 233 + y, 868 + x, 227 + y };
    RECT rect5 = { 868 + x, 227 + y, 868 - 3 + x, 227 - 3 + y };
    RECT rect6 = { 852 + x, 237 + y, 865 + x, 222 + y };
    RECT rect7 = { 855 + x, 222 + y, 865 + x, 217 + y };
    RECT rect8 = { 857 + x, 217 + y, 863 + x, 211 + y };

    FillRect(hdc, &rect1, hBrush);
    FillRect(hdc, &rect2, hBrush);
    FillRect(hdc, &rect3, hBrush);
    FillRect(hdc, &rect4, hBrush);
    FillRect(hdc, &rect5, hBrush);
    FillRect(hdc, &rect6, hBrush);
    FillRect(hdc, &rect7, hBrush);
    FillRect(hdc, &rect8, hBrush);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            Racing_x -= 10;
            InvalidateRect(hWnd, 0, 1);
            break;
        case VK_RIGHT:
            Racing_x += 10;
            InvalidateRect(hWnd, 0, 1);
            break;
        case VK_DOWN:
            Racing_y += 10;
            InvalidateRect(hWnd, 0, 1);
            break;
        case VK_UP:
            Racing_y -= 10;
            InvalidateRect(hWnd, 0, 1);
            break;
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DrawRacingCar(hdc, Racing_x, Racing_y);

            DrawCar(hdc,0,0);
            DrawCar(hdc, 0, 300);

            DrawRam(hdc, 0,300);
            DrawRam(hdc, 0, 0);

            DrawWrench(hdc, 0,300);
            DrawWrench(hdc, 0, 0);

            DrawFuel(hdc, 0,300);
            DrawFuel(hdc, 0, 0);
            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
