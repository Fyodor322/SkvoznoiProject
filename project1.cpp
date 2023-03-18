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
void DrawRacingCar(HDC hdc)
{
    HBRUSH hBrush;
    HPEN hPen;
    hBrush = CreateSolidBrush(RGB(237, 28, 36));        //кузов
    SelectObject(hdc, hBrush);
    RECT rect = { 120, 90, 160, 210 };
    FillRect(hdc, &rect, hBrush);


    SelectObject(hdc, hBrush);
    rect = { 80, 60, 200, 90 };         //переднее антикрыло
    FillRect(hdc, &rect, hBrush);

    SelectObject(hdc, hBrush);
    rect = { 120, 230, 160, 245 };         //заднее антикрыло
    FillRect(hdc, &rect, hBrush);

    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, 140, 130, 0);
    LineTo(hdc, 130, 160);              //кабина пилота
    LineTo(hdc, 150, 160);
    LineTo(hdc, 140, 130);

    MoveToEx(hdc, 160, 105, 0);
    LineTo(hdc, 180, 105);
    LineTo(hdc, 160, 120);
    //крепления колёс
    MoveToEx(hdc, 120, 105, 0);
    LineTo(hdc, 100, 105);
    LineTo(hdc, 120, 120);


    HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hBrush2);
    POINT pt[4];
    pt[0].x = 122;
    pt[1].x = 133;
    pt[2].x = 147;                      //задний треугольник
    pt[3].x = 155;
    pt[0].y = 210;
    pt[1].y = 230;
    pt[2].y = 230;
    pt[3].y = 210;

    Polygon(hdc, pt, 4);

    SelectObject(hdc, hPen);
    MoveToEx(hdc, 127, 219, 0);             //левое крепление колеса
    LineTo(hdc, 103, 229);

    MoveToEx(hdc, 155, 219, 0);             //правое крепление колеса
    LineTo(hdc, 177, 229);

}

void DrawWeel(HDC hdc, int x, int y)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));

    SelectObject(hdc, hBrush);
    POINT pt[9];
    pt[0].x = 181 + x;
    pt[1].x = 178 + x;
    pt[2].x = 178 + x;
    pt[3].x = 181 + x;
    pt[4].x = 189 + x;
    pt[5].x = 192 + x;      //функция рисования колёс
    pt[6].x = 192 + x;
    pt[7].x = 189 + x;
    pt[8].x = 181 + x;

    pt[0].y = 92 + y;
    pt[1].y = 95 + y;
    pt[2].y = 118 + y;
    pt[3].y = 122 + y;
    pt[4].y = 122 + y;
    pt[5].y = 118 + y;
    pt[6].y = 95 + y;
    pt[7].y = 92 + y;
    pt[8].y = 92 + y;

    Polygon(hdc, pt, 9);
}

void DrawCar(HDC hdc)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(63, 72, 204));
    SelectObject(hdc, hBrush);

    POINT pt[10];
    pt[0].x = 362;
    pt[1].x = 411;
    pt[2].x = 425;
    pt[3].x = 425;
    pt[4].x = 411;
    pt[5].x = 411;
    pt[6].x = 362;
    pt[7].x = 348;
    pt[8].x = 348;
    pt[9].x = 362;
    //кузов 
    pt[0].y = 48;
    pt[1].y = 48;
    pt[2].y = 62;
    pt[3].y = 187;
    pt[4].y = 201;
    pt[5].y = 201;
    pt[6].y = 201;
    pt[7].y = 187;
    pt[8].y = 62;
    pt[9].y = 48;
    Polygon(hdc, pt, 10);

    int x1 = 427, y1 = 112, x2 = 427, y2 = 98;
    while (y1 >= 106)
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, RGB(63, 72, 204));
        SelectObject(hdc, hPen);
        MoveToEx(hdc, x1, y1, 0);
        LineTo(hdc, x2, y2);
        x1++;
        y1--;
        x2++;
        y2++;
    }
    x1 = 347, y1 = 112, x2 = 347, y2 = 98;      //зеркала заднего вида
    while (x1 >= 339)
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
    RECT rect = { 361, 63, 375, 68 };           //левая фара
    FillRect(hdc, &rect, hBrushs);

    RECT rect2 = { 361 + 38, 63, 375 + 38, 68 };   //правая фара
    FillRect(hdc, &rect2, hBrushs);

    SelectObject(hdc, hBrush2);
    RECT rect3 = { 363, 98, 410, 112 };
    FillRect(hdc, &rect3, hBrush2);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(hdc, hPen);
    MoveToEx(hdc, 366, 97, 0);
    LineTo(hdc, 407, 97);                           //лобовое стекло
    MoveToEx(hdc, 368, 96, 0);
    LineTo(hdc, 404, 96);
    MoveToEx(hdc, 371, 95, 0);
    LineTo(hdc, 401, 95);
    
    HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(153, 217, 234));
    SelectObject(hdc, hPen2);
    MoveToEx(hdc, 353, 112, 0);
    LineTo(hdc, 353, 156);
    MoveToEx(hdc, 354, 114, 0);
    LineTo(hdc, 354, 154);
    MoveToEx(hdc, 355, 116, 0);                                 //левое стекло
    LineTo(hdc, 355, 152);
    MoveToEx(hdc, 356, 118, 0);
    LineTo(hdc, 356, 150);
    MoveToEx(hdc, 357, 120, 0);
    LineTo(hdc, 357, 148);

    MoveToEx(hdc, 421, 112, 0);
    LineTo(hdc, 421, 156);
    MoveToEx(hdc, 420, 114, 0);
    LineTo(hdc, 420, 154);
    MoveToEx(hdc, 419, 116, 0);                                 //правое стекло
    LineTo(hdc, 419, 152);
    MoveToEx(hdc, 418, 118, 0);
    LineTo(hdc, 418, 150);
    MoveToEx(hdc, 417, 120, 0);
    LineTo(hdc, 417, 148);

    SelectObject(hdc, hBrush3);
    RECT rect4 = { 363, 167, 410, 177 };
    FillRect(hdc, &rect4, hBrush3);
    SelectObject(hdc, hPen2);                           //заднее стекло
    x1 = 366, x2 = 406;
    int y = 177;
    while (y <= 184)
    {
        MoveToEx(hdc, x1, y, 0);
        LineTo(hdc, x2, y);
        y++;
        x1++;
        x2--;
    }
}

void DrawRam(HDC hdc)
{
    HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0));        //чёрная
    HBRUSH hBrush = CreateSolidBrush(RGB(185, 122, 87));    //коричневая
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(185, 122, 87));  //коричневая 
    HBRUSH hBrush1 = CreateSolidBrush(RGB(127, 127, 127)); //серая


    SelectObject(hdc, hBrush2);
    POINT pt1[4];
    pt1[0].x = 586;
    pt1[1].x = 586;
    pt1[2].x = 594;                      //левая ручка
    pt1[3].x = 594;

    pt1[0].y = 100;
    pt1[1].y = 148;
    pt1[2].y = 148;
    pt1[3].y = 100;

    Polygon(hdc, pt1, 4);

    POINT pt[4];
    pt[0].x = 586+20;
    pt[1].x = 586+20;
    pt[2].x = 594+20;                      //правая ручка
    pt[3].x = 594+20;

    pt[0].y = 100;
    pt[1].y = 148;
    pt[2].y = 148;
    pt[3].y = 100;

    Polygon(hdc, pt, 4);

    SelectObject(hdc, hBrush);
    RECT rect = { 551, 153, 649, 171 };     //бревно
    FillRect(hdc, &rect, hBrush);

    SelectObject(hdc, hPen);
    int x1 = 552, x2 = 648, y = 152;        //закругление сверху
    while (y >= 148)
    {
        MoveToEx(hdc, x1, y, 0);
        LineTo(hdc, x2, y);
        y--;
        x1++;
        x2--;
    }

    x1 = 552, x2 = 648, y = 171;            //закругление снизу
    while (y <= 176)
    {
        MoveToEx(hdc, x1, y, 0);
        LineTo(hdc, x2, y);
        y++;
        x1++;
        x2--;
    }

    SelectObject(hdc, hBrush1);
    POINT pt2[11];
    pt2[0].x = 558;
    pt2[1].x = 558+8;
    pt2[2].x = 558 + 8*2;
    pt2[3].x = 558 + 8 * 3;
    pt2[4].x = 558 + 8 * 4;
    pt2[5].x = 558 + 8 * 5;
    pt2[6].x = 558 + 8 * 6;
    pt2[7].x = 558 + 8 * 7;             
    pt2[8].x = 558 + 8 * 8;
    pt2[9].x = 558 + 8 * 9;
    pt2[10].x = 558 + 8 * 10;
                                        //шипы
    pt2[0].y = 177;
    pt2[1].y = 192;
    pt2[2].y = 177;
    pt2[3].y = 192;
    pt2[4].y = 177;
    pt2[5].y = 192;
    pt2[6].y = 177;
    pt2[7].y = 192;
    pt2[8].y = 177;
    pt2[9].y = 192;
    pt2[10].y = 177;

    Polygon(hdc, pt2, 11);
}
void DrawWrench(HDC hdc)
{
    HBRUSH hBrush1 = CreateSolidBrush(RGB(127, 127, 127)); //серая
    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

    SelectObject(hdc, hPen);                            //головка 
    Arc(hdc, 729, 66, 766, 109, 730, 93, 752, 67);
    MoveToEx(hdc, 730, 91, 0);
    LineTo(hdc, 750, 91);               
    LineTo(hdc, 750, 66);

    MoveToEx(hdc, 739, 108, 0);
    LineTo(hdc, 739, 176);
    LineTo(hdc, 741, 184);                      //ручка
    LineTo(hdc, 753, 184);
    LineTo(hdc, 756, 176);
    LineTo(hdc, 756, 108);

    Ellipse(hdc, 744, 169, 752, 179);       //крючок

    MoveToEx(hdc, 729, 83, 0);
    LineTo(hdc, 743, 74);
    LineTo(hdc, 743, 70);
    LineTo(hdc, 741, 68);
    LineTo(hdc, 731, 68);
    LineTo(hdc, 729, 71);
    LineTo(hdc, 729, 83);
}
void DrawFuel(HDC hdc)
{
    HPEN hPen = CreatePen(PS_SOLID, 8, RGB(74, 74, 74));
    HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(127, 127, 127));
    HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(142, 28, 36));
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 127, 39));
    
    SelectObject(hdc, hPen);
    Ellipse(hdc, 822, 156, 902, 187);   //обод бочки

    MoveToEx(hdc, 901, 173, 0);
    LineTo(hdc, 901, 283);
    LineTo(hdc, 823, 283);          //обводка корпуса
    LineTo(hdc, 823, 173);

    SelectObject(hdc, hPen1);
    POINT pt[4];
    pt[0].x = 827;
    pt[1].x = 827;
    pt[2].x = 896;
    pt[3].x = 896;
                                    //заливка корпуса
    pt[0].y = 190; 
    pt[1].y = 278;
    pt[2].y = 278;
    pt[3].y = 190;
    Polygon(hdc, pt, 4);

    SelectObject(hdc, hPen1);

    int x1 = 896, x2 = 901 - 27, y = 189;
    while (y>=183)
    {
        MoveToEx(hdc, x1, y, 0);            
        LineTo(hdc, x2, y);
        x2+=2;
        y--;
    }           //дозаливка справа

    SelectObject(hdc, hPen1);

    x1 = 896, x2 = 901 - 27, y = 189;
    while (y >= 183)
    {
        MoveToEx(hdc, x1-48, y, 0);
        LineTo(hdc, x2-48, y);
        x1 -= 2;
        y--;
    }       //дозаливка слева

    RECT rect1 = { 855, 254, 863, 252 };   
    RECT rect2 = { 848, 252, 868, 248 };
    RECT rect3 = { 845, 248, 872, 233 };
    RECT rect4 = { 848, 233, 868, 227 };
    RECT rect5 = { 868, 227, 868 - 3, 227 - 3 };
    RECT rect6 = { 852, 237, 865, 222 };
    RECT rect7 = { 855, 222, 865, 217 };
    RECT rect8 = { 857, 217, 863, 211 };

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
            DrawRacingCar(hdc);
            DrawWeel(hdc, 0, 0);
            DrawWeel(hdc, -90, 0);
            DrawWeel(hdc, 0, 118);
            DrawWeel(hdc, -90, 118);
            DrawCar(hdc);

            DrawRam(hdc);
            DrawWrench(hdc);
            DrawFuel(hdc);
            
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
