// CSGO_Internals.cpp : Defines the exported functions for the DLL application.
//
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

#include <string>
#include <iostream>
#include "stdafx.h"
#include "SolaireHub2.h"

#include "Localplayer.h"

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include "Player.h"
#include <sstream>
Trigger trigger;
CommonMethods commonMethods;
Bhop bunnyHop;
GlowEsp glowEsp;
AntiFlash antiFlash;
Radar radar;

namespace cheats
{
	void PlayerInfo()
	{
		//retreive player base pointer
		Player.CBase = *(DWORD*)(dwClient + m_dwLocalPlayer);
		//if ingame?
		if (Player.CBase > 0)
		{
			//on air pointer
			Player.onAir = *(int*)(Player.CBase + m_onAir);
			Player.crossHair = *(int*)(Player.CBase + m_iCrosshairId);
		}
	}

	void CheckInput()
	{
		//check if space is pressed
		//and react accordingly turning
		//the bunny hop on or off
		if (GetAsyncKeyState(VK_SPACE))
		{
			Active.Bhop = true;
		}
		else
		{
			Active.Bhop = false;
		}
	}

	//check which cheats are active
	//and run their respective methods
	//note some of thesew are in the CommonMethods x64 loop
	void runCheats()
	{
		if (Active.Bhop && Active.togBhop)
		{
			bunnyHop.BunnyHops();
		}
		if (Active.Trigger)
		{
			trigger.triggerBot();
		}
		if (Active.antiFlash)
		{
			antiFlash.antiFlash();
		}
	}

	void MainLoop()
	{
		//set active cheats//
		Active.Trigger = false;
		Active.radar = false;
		Active.antiFlash = false;
		Active.chams = false;
		Active.glowEsp = false;
		Active.aimBot = false;
		Active.togBhop = false;

		bool togGUI = true;
		//trigger aimbot glow antiflash radar
		while (1)
		{
			if (Active.aimBot)
			{
				Run();
			}

			//retreive basic player info
			PlayerInfo();
			
			//checking for keypress
			CheckInput();

			//for loop stuff goes in here
			commonMethods.entityListLoop();

			runCheats();

			LPCSTR wndName = "csgo";

			HWND hwnd = FindWindow(NULL, wndName);

			HDC hdc = GetDC(hwnd);

			if (GetKeyState(VK_F1) & 0x8000)
			{
				Active.Trigger = !Active.Trigger;
				Sleep(150);
			}
			if (GetKeyState(VK_F2) & 0x8000)
			{
				Active.aimBot = !Active.aimBot;
				Sleep(150);
			}
			if (GetKeyState(VK_F3) & 0x8000)
			{
				Active.glowEsp = !Active.glowEsp;
				Sleep(150);
			}
			if (GetKeyState(VK_F4) & 0x8000)
			{
				Active.antiFlash = !Active.antiFlash;
				Sleep(150);
			}

			if (GetKeyState(VK_F5) & 0x8000)
			{
				Active.radar = !Active.radar;
				Sleep(150);
			}
			if (GetKeyState(VK_F6) & 0x8000)
			{
				Active.togBhop = !Active.togBhop;
				Sleep(150);
			}

			if (GetKeyState(VK_F7) & 0x8000)
			{
				togGUI = !togGUI;
				Sleep(150);
			}

			if (GetKeyState(VK_OEM_PLUS) & 0x8000)
			{
				Sleep(150);
				aimbotSnap+=0.1f;
			}
			if (GetKeyState(VK_OEM_MINUS) & 0x8000)
			{
				Sleep(150);
				aimbotSnap -= 0.1f;
			}

			if (hdc && togGUI) {

				
				if (Active.Trigger)
				{
					TextOut(hdc, 0, 0, "Trigger - ON [F1] ", 18);
				}
				else
				{
					TextOut(hdc, 0, 0, "Trigger - OFF [F1] ", 18);
				}
				

				if (Active.aimBot)
				{
					TextOut(hdc, 0, 30, "AimBot - ON [F2] ", 18);
				}
				else
				{
					TextOut(hdc, 0, 30, "AimBot - OFF [F2] ", 18);
				}

				if (Active.glowEsp)
				{
					TextOut(hdc, 0, 60, "Walls - ON [F3] ", 18);
				}
				else
				{
					TextOut(hdc, 0, 60, "Walls - OFF [F3] ", 18);
				}

				if (Active.antiFlash)
				{
					TextOut(hdc, 0, 90, "antiFlash - ON [F4] ", 18);
				}
				else
				{
					TextOut(hdc, 0, 90, "AFlash - OFF [F4] ", 18);
				}

				if (Active.radar)
				{
					TextOut(hdc, 0, 120, "radar - ON [F5] ", 18);
				}
				else
				{
					TextOut(hdc, 0, 120, "radar - OFF [F5] ", 18);
				}

				if (Active.togBhop)
				{
					TextOut(hdc, 0, 150, "bhop - ON [F6] ", 18);
				}
				else
				{
					TextOut(hdc, 0, 150, "bhop - OFF [F6] ", 18);
				}


				std::string snap = std::to_string(aimbotSnap);


				TextOut(hdc, 0, 180, snap.c_str(), 20);

				TextOut(hdc, 0, 210, "Togg menu [F7]", 18);				
			}
			DeleteDC(hdc);
		}
	}

}



//entry point
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cheats::MainLoop, 0, 0, 0);


	return 1;
}