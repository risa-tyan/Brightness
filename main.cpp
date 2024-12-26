#include <iostream> 
#include <iomanip>
#include <typeinfo>
#include <Windows.h>
#include <winuser.h>
#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <dxva2api.h>
#include <string.h>
#include <stdlib.h>
//#pragma comment(lib, "Dxva2.lib")


using namespace std;


class MonOptions {
    public:
        DWORD MaxBrightness, MinBrightness, CurrentBrightness;
        HMONITOR hMonitor;
        PHYSICAL_MONITOR phm[1];

        MonOptions(HWND hWnd) {
            hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY); // windows.h
            GetPhysicalMonitorsFromHMONITOR(hMonitor, 1, phm);
            GetBrightness();
            //std::cout << "\nUse monitor";
        }

        int GetBrightness() {
            if(GetMonitorBrightness(phm[0].hPhysicalMonitor, &MinBrightness, &CurrentBrightness, &MaxBrightness)) {
                return 0;
            }
            return 10; // GetBrightness error
        }

        int SetBrightness(DWORD bright_level) {
            GetBrightness();
            if (bright_level >= MinBrightness && bright_level <= MaxBrightness) {
                if(SetMonitorBrightness(phm[0].hPhysicalMonitor, bright_level)) {
                    return 0;
                }
            }
            return 20; // SetBrightness error
        }

        // ~MonOptions() {
        //     delete[] hMonitor;
        //     std::cout << "\nОбъект уничтожен" << std::endl;
        // }
};


int main (int argc, char* argv[]) {
    int argCount;
    LPWSTR* argvArray;
    argvArray = CommandLineToArgvW(GetCommandLineW(), &argCount);

    // for (int i = 1; i < argCount; i++) {
    //     std::wcout << "\n" << argvArray[i];
    // }

    HWND hWnd = GetConsoleWindow(); //winuser.h
    MonOptions MonOptions_1(hWnd);
    if (MonOptions_1.hMonitor)
    {
        for (int i = 1; i < argCount; i++) {
            if (wcscmp(argvArray[i], L"--info") == 0) {
                MonOptions_1.GetBrightness();
                std::cout << "\nBrightness: " 
                    << MonOptions_1.CurrentBrightness 
                    << " (" << MonOptions_1.MinBrightness 
                    << "-" << MonOptions_1.MaxBrightness << ")";
            }
            if (wcscmp(argvArray[i], L"--set-bright") == 0) {
                //LPWSTR value = argvArray[i + 1];
                DWORD znach = _wtoi(argvArray[i + 1]);
                if(MonOptions_1.SetBrightness(znach) != 0)
                {
                    std::cout << "error 20" << std ::endl;
                    return 20;
                }
                //std::cout << "\n\n" << typeid(znach).name() << "  " << znach << std::endl;
            }
        }
        //}
    } else {
        std::cout << "monitor not found";
    }
    LocalFree(argvArray);
    //system("pause");
    return 0;
}