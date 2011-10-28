/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 2000 Microsoft Corp.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/****************************************************************************

    PROGRAM: Cursor.c

    PURPOSE: Demonstrates how to manipulate a cursor and select a region

    FUNCTIONS:

        WinMain() - calls initialization function, processes message loop
        InitApplication() - initializes window data and registers window
        InitInstance() - saves instance handle and creates main window
        MainWndProc() - processes messages
        About() - processes messages for "About" dialog box
        sieve() - time consuming function, generates primes

****************************************************************************/
#include <windows.h>

#include "cursor.h"

#include "base/at_exit.h"
#include "base/command_line.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"
#include "views/widget/widget.h"
#include "views/widget/widget_delegate.h"

HINSTANCE hInst = NULL;
HCURSOR hSaveCursor = NULL;                 /* handle to current cursor      */
HCURSOR hHourGlass = NULL;                  /* handle to hourglass cursor    */

BOOL bTrack = FALSE;                        /* TRUE if left button clicked   */
INT OrgX = 0, OrgY = 0;                     /* original cursor position      */
INT PrevX = 0, PrevY = 0;                   /* current cursor position       */
INT X = 0, Y = 0;                           /* last cursor position          */
RECT Rect;                                  /* selection rectangle           */

MPOINT ptCursor;                            /* x and y coordinates of cursor */
INT repeat = 1;                             /* repeat count of keystroke     */

class ExampleView : public views::WidgetDelegate {
public:
    ExampleView();
    virtual ~ExampleView() {};

    // Creates all the examples and shows the window.
    void Init(gfx::NativeWindow parent);

private:
    // views::WidgetDelegate implementation:
    virtual bool CanResize() const OVERRIDE;
    virtual bool CanMaximize() const OVERRIDE;
    virtual std::wstring GetWindowTitle() const OVERRIDE;
    virtual views::View* GetContentsView() OVERRIDE;
    virtual void WindowClosing() OVERRIDE;
    virtual views::Widget* GetWidget() OVERRIDE;
    virtual const views::Widget* GetWidget() const OVERRIDE;
    virtual views::NonClientFrameView* CreateNonClientFrameView() OVERRIDE;
    views::View* contents_;

    DISALLOW_COPY_AND_ASSIGN(ExampleView);
};

ExampleView::ExampleView() : contents_(NULL) {}

void ExampleView::Init(gfx::NativeWindow parent) {
    using namespace views;
    DCHECK(contents_ == NULL) << "Run called more than once.";
    contents_ = new View();
    contents_->set_background(
        Background::CreateSolidBackground(125, 25, 25));
    contents_->SetSize(gfx::Size(200, 200));
    Widget* widget = new Widget;
    Widget::InitParams params;
    params.delegate = this;
    params.parent = parent;
    params.child = true;
    params.top_level = false;
    params.type = Widget::InitParams::TYPE_CONTROL; // only this type can be add as child View
    widget->Init(params);
    widget->SetContentsView(contents_); // must after Init because it use root_view
    widget->SetSize(gfx::Size(200, 200));
    widget->Show();
}

bool ExampleView::CanResize() const {
    return false;
}

bool ExampleView::CanMaximize() const {
    return true;
}

std::wstring ExampleView::GetWindowTitle() const {
    return L"";
}

views::View* ExampleView::GetContentsView() {
    return contents_;
}

void ExampleView::WindowClosing() {
}

views::Widget* ExampleView::GetWidget() {
    return contents_->GetWidget();
}

const views::Widget* ExampleView::GetWidget() const {
    return contents_->GetWidget();
}

views::NonClientFrameView* ExampleView::CreateNonClientFrameView(){
    return NULL;
}

ExampleView* gView  = NULL;
/****************************************************************************

    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)

    PURPOSE: calls initialization function, processes message loop

****************************************************************************/
int WINAPI WinMain (
       __in HINSTANCE hInstance,
       __in_opt HINSTANCE hPrevInstance,
       __in_opt LPSTR lpCmdLine,
       __in int nCmdShow )
{
    MSG msg;                                 /* message                      */
    BOOL bRet = FALSE;                     /* TRUE if getmessage failed    */
    
    OleInitialize(NULL);
    CommandLine::Init(0, NULL);
    // The exit manager is in charge of calling the dtors of singleton objects.
    base::AtExitManager exit_manager;
    ui::RegisterPathProvider();
    ui::ResourceBundle::InitSharedInstance("en-US");
    
    gView = new ExampleView();

    if (!InitApplication(hInstance))
    {
        return FALSE;
    }

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) !=0)
    {
        if (bRet == -1)
        {
            // Possibly handle the error
            return FALSE;
        }
        else
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

    delete gView;
    OleUninitialize();

    return (int) msg.wParam;
}

/****************************************************************************

    FUNCTION: InitApplication(HANDLE)

    PURPOSE: Initializes window data and registers window class

****************************************************************************/
BOOL InitApplication (
    HINSTANCE hInstance)
{
    WNDCLASS wc = {0};

    wc.lpfnWndProc = (WNDPROC) MainWndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (hInstance, TEXT("bullseye"));
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); 
    wc.lpszMenuName =  TEXT("CursorMenu");
    wc.lpszClassName = TEXT("CursorWClass");

    return (RegisterClass(&wc));
}

/****************************************************************************

    FUNCTION:  InitInstance(HANDLE, int)

    PURPOSE:  Saves instance handle and creates main window

****************************************************************************/
BOOL InitInstance(
    HINSTANCE hInstance,
    INT nCmdShow)
{
    BOOL bSuccess = FALSE;
    HWND hWnd = NULL;

    hInst = hInstance;

    hHourGlass = LoadCursor(NULL, IDC_WAIT);  

    hWnd = CreateWindowW (
        TEXT ("CursorWClass"),
        TEXT ("Cursor Sample Application"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0,
        CW_USEDEFAULT, 0,
        NULL, NULL, hInstance, NULL);
    
    if (hWnd)
    {
        gView->Init(hWnd);
        ShowWindow (hWnd, nCmdShow);
        bSuccess = UpdateWindow(hWnd);
    }

    return bSuccess;
}

/****************************************************************************

    FUNCTION: MainWndProc(HWND, unsigned, WPARAM, LPARAM)

    PURPOSE:  Processes messages

    MESSAGES:

        WM_COMMAND     - application menu (About dialog box)
        WM_CHAR        - ASCII key value received
        WM_LBUTTONDOWN - left mouse button
        WM_MOUSEMOVE   - mouse movement
        WM_LBUTTONUP   - left button released
        WM_KEYDOWN     - key pressed
        WM_KEYUPS      - key released
        WM_PAINT       - update window
        WM_DESTROY     - destroy window

    COMMENTS:

        When the left mouse button is pressed, btrack is set to TRUE so that
        the code for WM_MOUSEMOVE will keep track of the mouse and update
        the box accordingly.  Once the button is released, btrack is set to
        FALSE, and the current position is saved.  Holding the SHIFT key
        while pressing the left button will extend the current box rather
        then erasing it and starting a new one.

        When an arrow key is pressed, the cursor is repositioned in the
        direction of the arrow key.  A repeat count is kept so that the
        longer the user holds down the arrow key, the faster it will move.
        As soon as the key is released, the repeat count is set to 1 for
        normal cursor movement.

****************************************************************************/
LRESULT CALLBACK MainWndProc(
    HWND hWnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam)
{
    POINT pt = {0};
    HDC hDC = NULL;
    BOOL bRetDWP = FALSE;        // return DefWindowProc(...)
    static TCHAR str[255] = {0}; // general-purpose string buffer 
    size_t strSize = ARRAYSIZE(str);

    switch (message)
    {
        case WM_COMMAND:
            // LOWORD added for portability
            if (LOWORD(wParam) == IDM_ABOUT)
            {
                DialogBox(hInst,
                          TEXT("AboutBox"),
                          hWnd,
                          (DLGPROC)About);
                break;
            }
            else
            {
                bRetDWP = TRUE;
                goto exit_func;
                break;
            }

        case WM_MOUSEMOVE:
            {
                RECT rectClient = {0};
                INT  NextX = 0;
                INT  NextY = 0;

                if (bTrack)
                {
                    NextX = (SHORT)LOWORD(lParam);
                    NextY = (SHORT)HIWORD(lParam);

                    /* Do not draw outside the window's client area */

                    GetClientRect (hWnd, &rectClient);
                    if (NextX < rectClient.left)
                    {
                        NextX = rectClient.left;
                    }
                    else if (NextX >= rectClient.right)
                    {
                        NextX = rectClient.right - 1;
                    }
                    if (NextY < rectClient.top)
                    {
                        NextY = rectClient.top;
                    }
                    else if (NextY >= rectClient.bottom)
                    {
                        NextY = rectClient.bottom - 1;
                    }

                    /* If the mouse position has changed, then clear the */
                    /* previous rectangle and draw the new one.          */

                    if ((NextX != PrevX) || (NextY != PrevY))
                    {
                        hDC = GetDC(hWnd);
                        SetROP2(hDC, R2_NOT);          /* Erases the previous box */
                        MoveToEx(hDC, OrgX, OrgY, NULL);
                        LineTo(hDC, OrgX, PrevY);
                        LineTo(hDC, PrevX, PrevY);
                        LineTo(hDC, PrevX, OrgY);
                        LineTo(hDC, OrgX, OrgY);

                        /* Get the current mouse position */

                        PrevX = NextX;
                        PrevY = NextY;
                        MoveToEx(hDC, OrgX, OrgY, NULL); /* Draws the new box */
                        LineTo(hDC, OrgX, PrevY);
                        LineTo(hDC, PrevX, PrevY);
                        LineTo(hDC, PrevX, OrgY);
                        LineTo(hDC, OrgX, OrgY);
                        ReleaseDC(hWnd, hDC);
                    }
                }
            }
            break;

        case WM_LBUTTONUP:
            bTrack = FALSE;                 /* No longer creating a selection */
            ReleaseCapture();               /* Releases hold on mouse input */

            X = LOWORD(lParam);             /* Saves the current value      */
            Y = HIWORD(lParam);
            break;

        case WM_KEYDOWN:
            if (wParam != VK_LEFT && wParam != VK_RIGHT
                && wParam != VK_UP && wParam != VK_DOWN)
                break;

            MPOINT2POINT(ptCursor, pt);
            GetCursorPos(&pt);

            /* Convert screen coordinates to client coordinates */

            ScreenToClient(hWnd, &pt);
            POINT2MPOINT(pt, ptCursor);
            repeat++;                           /* Increases the repeat rate */

            switch (wParam)
            {

                /* Adjust cursor position according to which key was pressed. */
                
                case VK_LEFT:
                    ptCursor.x = ptCursor.x - (SHORT) repeat;
                    break;

                case VK_RIGHT:
                    ptCursor.x = ptCursor.x + (SHORT) repeat;
                    break;

                case VK_UP:
                    ptCursor.y = ptCursor.y - (SHORT) repeat;
                    break;

                case VK_DOWN:
                    ptCursor.y = ptCursor.y + (SHORT) repeat;
                    break;
            }

            /* Get the client boundaries */

            GetClientRect(hWnd, &Rect);

            /* Do not draw outside the window's client area */

            MPOINT2POINT(ptCursor, pt);
            if (pt.x >= Rect.right)
                pt.x = Rect.right - 1;
            else if (pt.x < Rect.left)
                pt.x = Rect.left;
            if (pt.y >= Rect.bottom)
                pt.y = Rect.bottom - 1;
            else if (pt.y < Rect.top)
                pt.y = Rect.top;

            /* Convert the coordinates to screen coordinates */

            ClientToScreen(hWnd, &pt);
            SetCursorPos(pt.x, pt.y);
            break;

        case WM_KEYUP:
            repeat = 1;                          /* Clears the repeat count. */
            break;

        case WM_ACTIVATE:
            if (!GetSystemMetrics(SM_MOUSEPRESENT))
            {
                if (!HIWORD(wParam))
                {
                    // LOWORD added for portability
                    if (LOWORD(wParam))
                    {
                        SetCursor(LoadCursor(hInst, TEXT("bullseye")));
                        pt.x = X;
                        pt.y = Y;
                        ClientToScreen(hWnd, &pt);
                        SetCursorPos(pt.x, pt.y);
                    }
                    if (wParam)
                    {
                        ShowCursor(TRUE);
                    }
                    else
                    {
                        ShowCursor(FALSE);
                    }
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            bRetDWP = TRUE;
            goto exit_func;
            break;
    }

exit_func:
    if (bRetDWP)
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    else
    {
        return 0;
    }
}


/****************************************************************************

    FUNCTION: About(HWND, unsigned, WPARAM, LPARAM)

    PURPOSE:  Processes messages for "About" dialog box

    MESSAGES:

        WM_INITDIALOG - initialize dialog box
        WM_COMMAND    - Input received

****************************************************************************/
INT_PTR CALLBACK About(
    HWND hDlg, 
    UINT message, 
    WPARAM wParam,
    LPARAM lParam)
{
    BOOL bProcessedMsg = FALSE;
    
    switch (message) 
    {
        case WM_INITDIALOG:
            bProcessedMsg = TRUE;
            break;

        case WM_COMMAND:
            // LOWORD added for portability
            if (LOWORD(wParam) == IDOK
                || LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, TRUE);
                bProcessedMsg = TRUE;
            }
            break;

    }
    
    return bProcessedMsg;
}


/****************************************************************************

    FUNCTION: Sieve()

    PURPOSE:  Example of time consuming process

    COMMENTS:

        Sieve of Eratosthenes, BYTE, Volume 8, Number 1, by Jim Gilbreath
        and Gary Gilbreath.  Code changed to give correct results.

        One could return the count, and after restoring the cursor, use
        sprintf() to copy the information to a string which could then be
        put up in a MessageBox().

****************************************************************************/
#define NITER   20                                 /* number of iterations */
#define SIZE    81900

CHAR flags [SIZE+1] = {0};

INT sieve () 
{
    INT i,k;
    INT iter, count = 0;

    for (iter = 1; iter <= NITER; iter++)
    {      /* Do sieve NITER times */
        count = 0;
        for (i = 0; i <= SIZE; i++)              /* Sets all flags TRUE    */
            flags[i] = TRUE;

        for (i = 2; i <= SIZE; i++)
        {
            if (flags[i] )
            {                        /* Found a prime?       */
                for (k = i + i; k <= SIZE; k += i)
                    flags[k] = FALSE;              /* Cancels its multiples */
                count++;
            }
        }
    }
    return (count);
}
