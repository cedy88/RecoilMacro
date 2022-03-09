#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#define WIN32_LEAN_AND_MEAN //to exclude some of the less frequently used APIs 

struct vec2{ float x, y; };//https://docs.microsoft.com/en-ca/cpp/cpp/struct-cpp?view=msvc-170
bool recoil_enable = false;//https://docs.microsoft.com/en-ca/cpp/cpp/bool-cpp?view=msvc-170
vec2 recoil;
void console_menu() {//you could add a framework as example ImGui.
	while (true) {
		if (recoil_enable) 
			std::cout << "Recoil [ON]" << std::endl;
		else
			std::cout << "Recoil [OFF]" << std::endl;
		std::cout << "Recoil X: [" << recoil.x << "]" << std::endl;
		std::cout << "Recoil Y: [" << recoil.y << "]" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));//a cooler way to sleep.
		//https://docs.microsoft.com/en-ca/cpp/standard-library/thread-functions?view=msvc-170
		//https://docs.microsoft.com/en-ca/cpp/standard-library/chrono?view=msvc-170
		system("cls");//https://docs.microsoft.com/en-ca/cpp/c-runtime-library/reference/system-wsystem?view=msvc-170
	}
}

void main() {
	std::thread(console_menu).detach();
    while(true) {
        while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && recoil_enable) {//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
            mouse_event(MOUSEEVENTF_MOVE, recoil.x, recoil.y, 0, 0);//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-mouse_event
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

		if (GetAsyncKeyState(VK_F1) & 1)
			recoil_enable = !recoil_enable;
		if (GetAsyncKeyState(VK_F2) & 1) 
			recoil.x += 1;
		if (GetAsyncKeyState(VK_F3) & 1) 
			recoil.x -= 1;
		if (GetAsyncKeyState(VK_F4) & 1) 
			recoil.y += 1;
		if (GetAsyncKeyState(VK_F5) & 1)
			recoil.y -= 1;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
//Enjoy.