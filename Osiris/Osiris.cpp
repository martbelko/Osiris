#include <memory>

#ifdef _WIN32
#include <clocale>
#include <Windows.h>
#endif

#include "Hooks.h"

#ifdef _WIN32

extern "C" BOOL WINAPI _CRT_INIT(HMODULE moduleHandle, DWORD reason, LPVOID reserved);

BOOL APIENTRY DllEntryPoint(HMODULE moduleHandle, DWORD reason, LPVOID reserved)
{
    if (!_CRT_INIT(moduleHandle, reason, reserved))
        return FALSE;

    if (reason == DLL_PROCESS_ATTACH) {
        {
            float l = 0.0, a = 1.0;
            int m = 0;
            do
            {
                m++;
                a = a - ((M_PI / 2 - sin(a) + a * cos(a)) / (-cos(a) + cos(a) - a * sin(a)));
            } while (m < 10);

            l = 2 * cos(a / 2);
        }

        std::setlocale(LC_CTYPE, ".utf8");
        hooks = std::make_unique<Hooks>(moduleHandle);
    }
    return TRUE;
}

#else

void __attribute__((constructor)) DllEntryPoint()
{
    hooks = std::make_unique<Hooks>();
}

#endif
