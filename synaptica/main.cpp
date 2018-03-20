#include <QGuiApplication>
#include <QClipboard>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <qqmlcontext.h>
#include <QDebug>
#include <QObject>
#include <windows.h>
#include "clipboardManage.h"

/*
 * Keytrace
 * */
#pragma comment( lib, "user32.lib")

HHOOK hHook = NULL;

void UpdateKeyState(BYTE *keystate, int keycode) {
    keystate[keycode] = GetKeyState(keycode);
}

LRESULT CALLBACK Tracker(int nCode, WPARAM wParam, LPARAM lParam) {
    //qDebug() << "Key Pressed";
    //WPARAM is WM_KEYDOWN, WM_KEYUO, WM_SYSKEYDOWN, or WM_SYSKEYUP;
    //LPARAM is the key information
    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
    wchar_t buffer[5];

    BYTE keyboard_state[256];
    GetKeyboardState(keyboard_state);
    UpdateKeyState(keyboard_state, VK_SHIFT);
    UpdateKeyState(keyboard_state, VK_CAPITAL);
    UpdateKeyState(keyboard_state, VK_CONTROL);
    UpdateKeyState(keyboard_state, VK_MENU);

    //Get Keyboard Layout
    HKL keyboard_layout = GetKeyboardLayout(0);

    //Get the name
    char lpszName[0x100] = {0};
    DWORD dwMsg = 1;
    dwMsg += cKey.scanCode << 16;
    dwMsg += cKey.flags << 24;
    int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName, 255);
    int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode,
        keyboard_state, buffer, 4, 0, keyboard_layout);
    buffer[4] = L'\0';
    // Print the output
    qDebug() << "Key: " << cKey.vkCode << " "
             << QString::fromUtf16((ushort*)buffer)
             << " " << QString::fromUtf16((ushort*)lpszName);

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
/*
 * End Keytrace
 * */

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    ClipboardManage *clipboardInstance = new ClipboardManage();

    QQmlApplicationEngine engine;
    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty("clipboardManage", clipboardInstance);

    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, Tracker, NULL, 0);
    if ( hHook == NULL ) {
        qDebug() << "Hook failed";
    }

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
