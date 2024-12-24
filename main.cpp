#include <iostream> 
#include <iomanip>
#include <typeinfo>
#include <Windows.h>
#include <winuser.h>
#include <highlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>
#include <dxva2api.h>
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
            std::cout << "\nUse monitor";
        }

        int GetBrightness() {
            if(GetMonitorBrightness(phm[0].hPhysicalMonitor, &MinBrightness, &CurrentBrightness, &MaxBrightness)) {
                return 0;
            }
            return 10; // GetBrightness error
        }

        ~MonOptions() {
            delete[] hMonitor;
            std::cout << "\nОбъект уничтожен" << std::endl;
        }
};


int main () {
    HWND hWnd = GetConsoleWindow(); //winuser.h
    MonOptions MonOptinons_1(hWnd);
    if (MonOptinons_1.hMonitor)
    {
        if (MonOptinons_1.phm)
        {
            if (MonOptinons_1.GetBrightness())
            {
                std::cout << "test_2" << " min:" << MonOptinons_1.MinBrightness << " cur:" << MonOptinons_1.CurrentBrightness << " max:" << MonOptinons_1.MaxBrightness;
                //SetMonitorBrightness(phm[0].hPhysicalMonitor, 30);
                //GetMonitorBrightness(phm[0].hPhysicalMonitor, &MinBrightness, &CurrentBrightness, &MaxBrightness);
                //std::cout << "test_2" << " min:" << MinBrightness << " cur:" << CurrentBrightness << " max:" << MaxBrightness;
            }
        }
    } else {
        std::cout << "monitor not found";
    }
    system("pause");
    return 0;
}