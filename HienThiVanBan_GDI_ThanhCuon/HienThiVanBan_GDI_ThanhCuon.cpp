

#include "framework.h"
#include "HienThiVanBan_GDI_ThanhCuon.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HIENTHIVANBANGDITHANHCUON, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HIENTHIVANBANGDITHANHCUON));

    MSG msg;

    // Main message loop:
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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HIENTHIVANBANGDITHANHCUON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HIENTHIVANBANGDITHANHCUON);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int width, height, x, y, n = 0, x1,y1;
    HDC hdc;

    switch (message)
    {
    case WM_LBUTTONDOWN:    // Chuột
        // Lấy vị trí hiện tại
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        hdc = GetDC(hWnd);
        SetPixel(hdc, x, y, RGB(255, 0, 0));    // Vẽ một điểm
        if (n > 0)
        {
            MoveToEx(hdc, x1, y1, NULL);        // Đặt điểm bắt đầu
            LineTo(hdc, x, y);                  // Nối tới điểm kết thúc
        }
        ReleaseDC(hWnd, hdc);
        x1 = x; y1 = y; // Lưu lại tọa độ cuối
        n++;
        break;
    case WM_SIZE:   // Lấy kích thước miền thao tác
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            // TODO: Add any drawing code that uses hdc here...

            // Hiển thị văn bản: TextOut (hdc, x, y, psText, iLength)

            // Các thuộc tính của DC (ngưc cảnh thiết bị) xác định:
            /*
            * Màu văn bản:      SetTextColor(HDC hdc,COLORREF color)
                - Màu hiện tại: GetTextColor(HDC hDC) -> COLORREF
            * Màu nền văn bản:  SetBKColor(HDC hdc,COLORREF color)
                - Màu nền hiện tại:
                                GetBkColor(HDC hDC) -> COLORREF
                - Chế độ màu nền:
                                SetBKMode(HDC hdc,int mode)
                - Chế độ màu hiện hành:
                                GetBkMode(HDC hDC) -> int
            * Căn lề văn bản:
                - SetTextAlign(HDC hDC, UINT fMode) -> UNIT
                        fMode:  TA_LEFT, TA_RIGHT, TA_CENTER, TA_TOP, TA_BOTTOM, TA_BASELINE, TA_UPDATE
                - Chế độ căn lề hiện hành:
                        GetTextAlign(HDC hDC) -> UNIT
            * Khoảng cách giữa các kí tự:
                SetTextCharacterExtra(HDChDC, int nCharExtra) -> int
                GetTextCharacterExtra(HDChDC, int nCharExtra) -> int
            * font (mặc định: SYSTEM_FONT):
            * 
            */


            TextOut(hdc, 100, 100, TEXT("Thu Hien Vu"), 12);
            SetTextColor(hdc, RGB(255, 220, 202));
            TextOut(hdc, 100, 200, L"R6 Dung Nguyen", 15);
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

// Message handler for about box.
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
