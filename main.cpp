#include <windows.h>
#include <iostream>
#include <xstring>
#include <winnt.h>
#include <random>
#include <WinUser.h>
#include <string>
#include <tlhelp32.h>
#include <sstream>
#include <wingdi.h>
#include <windef.h>
#include <iosfwd>
#include "Memory.h"

vector<DWORD*> Results;

Memory *mem;
DWORD PID;
HANDLE hProcess;

DWORD xem_base = 0;
int count2 = 0;
int ft = 0;
int v_size_s[13];


void After()
{
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	WriteProcessMemory(hProcess, (LPVOID)(xem_base + 0x6E418), "\xE9\x0D\x01\x00\x00\x90", 6, NULL);
	WriteProcessMemory(hProcess, (LPVOID)(xem_base + 0x101682), "\x90\x90\x90", 3, NULL);

	int v_size = (int)Results.size();

	for (int i = 0; i < v_size; i++)
	{
		DWORD *Result32 = Results[i];
		if (i == 0)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0x5CC)
				{


					printf("check 3\n");
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

					WriteProcessMemory(hProcess, (LPVOID)(Result32[j] + 0x12), "\xE9\x09\x01\x00\x00\x90", 6, NULL);
					DWORD calling_addr = mem->GetCall(Result32[j] + 0x129);
					calling_addr = mem->GetCall(calling_addr + 6);

					WriteProcessMemory(hProcess, (LPVOID)(calling_addr + 6), "\x90\x90\x90", 3, NULL);
					count2++;
					printf("writing_1...\n");
				}
			}
			printf("\n");
		}

		if (i == 1)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0xAC5)
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

					WriteProcessMemory(hProcess, (LPVOID)(Result32[j] + 0xF), "\xE9\x0D\x01\x00\x00\x90", 6, NULL);
					DWORD calling_addr = mem->GetCall(Result32[j] + 0x126);
					calling_addr = mem->GetCall(calling_addr + 6);

					WriteProcessMemory(hProcess, (LPVOID)(calling_addr + 6), "\x90\x90\x90", 3, NULL);
					count2++;

					printf("writing_2...\n");
				}
			}

			printf("\n");
		}

		if (i == 2)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0x255)
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
					//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] - 7), "\xB8\x01\x00\x00\x00\x90\x90\x90\x90\x90\x90\x90", 12, NULL);
					printf("writing_4...\n");
					count2++;
				}
			}
			printf("\n");
		}

		if (i == 3)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0xDC5)
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
					//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] - 0xC), "\x31\xC0\x90\x90\x90\x90\x90\x90", 8, NULL);
					printf("writing_5...\n");
					count2++;
				}
			}
			printf("\n");
		}

		if (i == 4)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0x537)
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
					//WriteProcessMemory(hProcess, (LPVOID)Result32[j], "\x90\x90", 2, NULL);
					//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] + 8), "\x90\x90", 2, NULL);
					printf("writing_6...\n");
					count2++;
				}
			}
		}

		if (i == 5)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0x462)
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

					WriteProcessMemory(hProcess, (LPVOID)Result32[j], "\x90\x90\x90\x90\x90\x90\x90\x90", 8, NULL);
					WriteProcessMemory(hProcess, (LPVOID)(Result32[j] - 9), "\x90\x90\x90\x90\x90", 5, NULL);
					printf("detect_1...\n");
					count2++;
				}
			}
		}

		if (i == 6)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0x92)
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
					//main detect
					//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] - 0xC), "\xC3\x90", 2, NULL);
					printf("%X\n", (Result32[j] - 0xC));
					printf("detect_2...\n");
					count2++;
				}

			}
		}

		if (i == 8)
		{
			for (int j = 0; j < v_size_s[i]; j++)
			{
				if (Result32[j] << 20 >> 20 == 0x471)
				{
					hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
					//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] - 6), "\x90", 1, NULL);
					//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] - 5), "\x90\x90\x90\x90\x90", 5, NULL);
					printf("I'm hereeeeeeeeeeeeee detect_3 %X...\n", Result32[j]);
					count2++;
				}

			}
		}

		/*
		if (i == 7)
		{
		for (int j = 0; j < v_size_s[i]; j++)
		{

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] + 0xA), "\x90", 1, NULL);
		//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] + 0x11), "\x90", 1, NULL);
		//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] + 0x14), "\x90\x90\x90\x90\x90", 5, NULL);
		//WriteProcessMemory(hProcess, (LPVOID)(Result32[j] + 0x54), "\x31\xC0\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 14, NULL);
		printf("detect_3...\n");
		count2++;

		}
		}

		if (i == 8)
		{
		for (int j = 0; j < v_size_s[i]; j++)
		{
		if (Result32[j] << 20 >> 20 == 0x8D9)
		{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		//WriteProcessMemory(hProcess, (LPVOID)(Result32[j]), "\xC2\x08\x00", 3, NULL);
		printf("detect_3...\n");
		count2++;
		}

		}
		}*/


	}
}

void Bypass()
{
	mem = new Memory();

	for (;;)
	{
		if (mem->GetProcessByName("crossfire") > 0)
			break;

		Sleep(290);
	}

	PID = mem->GetProcessByName("crossfire");
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

	for (;;)
	{
		if (mem->GetModuleBase32("x3.xem", PID) > 0)
			break;
	}
	printf("check 1\n");
	xem_base = mem->GetModuleBase32("x3.xem", PID);
	Sleep(1090);
	//exit(0);
	printf("check 2\n");
	count2 = 0;
	int bRand = 0;
	ft = 0;
	//lol
	mem->FindPatten32("crossfire", 0x0, 100, "\x19\x19\x14", 3);
	for (;;)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

		mem->Suspend(true);

		//crc_1
		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x89\x85\xE4\xFC\xFF\xFF\xFF\x77\x18", 9);
		for (int i = 0; i < mem->v_size; i++)
		{
			if (mem->Result32[i] << 20 >> 20 == 0x5CC)
			{
				if (ft == 0)
				{
					ft = 1;
					mem->Suspend(false);
					Sleep(6550);
					mem->Suspend(true);
					printf("start to find patterns\n");
				}
				i = 0;
				mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x89\x85\xE4\xFC\xFF\xFF\xFF\x77\x18", 9);
				Results.push_back(mem->Result32);
				v_size_s[0] = mem->v_size;
				bRand = 1;
				break;
				/*for (int i = 0; i < mem->v_size; i++)
				{
				if (mem->Result32[i] << 20 >> 20 == 0x5CC)
				{
				if (ft == 0)
				{
				ft = 1;
				mem->Suspend(false);
				Sleep(2453);
				mem->Suspend(true);
				}

				printf("check 3\n");
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

				WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 0x12), "\xE9\x09\x01\x00\x00\x90", 6, NULL);
				DWORD calling_addr = mem->GetCall(mem->Result32[i] + 0x129);
				calling_addr = mem->GetCall(calling_addr + 6);

				WriteProcessMemory(hProcess, (LPVOID)(calling_addr + 6), "\x90\x90\x90", 3, NULL);
				count2++;
				printf("writing_1...\n");
				}
				}
				break;
				*/
			}
		}

		//printf("\n");

		//crc_2
		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x89\x9D\xE0\xFC\xFF\xFF\x8B\x8D\xEC\xFC\xFF\xFF\x3B\x59\x10", 15);
		Results.push_back(mem->Result32);
		v_size_s[1] = mem->v_size;

		/*for (int i = 0; i < mem->v_size; i++)
		{
		if (mem->Result32[i] << 20 >> 20 == 0xAC5)
		{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 0xF), "\xE9\x0D\x01\x00\x00\x90", 6, NULL);
		DWORD calling_addr = mem->GetCall(mem->Result32[i] + 0x126);
		calling_addr = mem->GetCall(calling_addr + 6);

		WriteProcessMemory(hProcess, (LPVOID)(calling_addr + 6), "\x90\x90\x90", 3, NULL);
		count2++;

		printf("writing_2...\n");
		}
		}

		printf("\n");
		*/

		//crc_3(x3.xem)
		//WriteProcessMemory(hProcess, (LPVOID)(xem_base + 0x6E418), "\xE9\x0D\x01\x00\x00\x90", 6, NULL);
		//WriteProcessMemory(hProcess, (LPVOID)(xem_base + 0x101682), "\x90\x90\x90", 3, NULL);

		//printf("writing_3...\n");
		//printf("\n");

		//crc_4
		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x8B\x08\xFF\x51\x28\x85\xC0\x75\x40", 9);
		Results.push_back(mem->Result32);
		v_size_s[2] = mem->v_size;
		/*
		for (int i = 0; i < mem->v_size; i++)
		{
		if (mem->Result32[i] << 20 >> 20 == 0x255)
		{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] - 7), "\xB8\x01\x00\x00\x00\x90\x90\x90\x90\x90\x90\x90", 12, NULL);
		printf("writing_4...\n");
		count2++;
		}
		}
		*/

		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x89\x85\xF0\xFD\xFF\xFF\x8D\x85\xF0\xFD\xFF\xFF\x89\x9D\xF4\xFD\xFF\xFF", 18);
		Results.push_back(mem->Result32);
		v_size_s[3] = mem->v_size;
		/*
		for (int i = 0; i < mem->v_size; i++)
		{
		if (mem->Result32[i] << 20 >> 20 == 0xDC5)
		{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] - 0xC), "\x31\xC0\x90\x90\x90\x90\x90\x90", 8, NULL);
		printf("writing_5...\n");
		count2++;
		}
		}
		printf("\n");
		*/

		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x75\x0F\x46\x83\xC0\x14\x3B\xF3\x7C\xD3", 10);
		Results.push_back(mem->Result32);
		v_size_s[4] = mem->v_size;
		/*
		for (int i = 0; i < mem->v_size; i++)
		{
		if (mem->Result32[i] << 20 >> 20 == 0x537)
		{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		WriteProcessMemory(hProcess, (LPVOID)mem->Result32[i], "\x90\x90", 2, NULL);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 8), "\x90\x90", 2, NULL);
		printf("writing_6...\n");
		count2++;
		}
		}
		printf("\n");
		*/

		//detect_1
		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\xFF\x75\x14\xFF\x36\xFF\x55\x10\x89\x45\xFC", 11);
		Results.push_back(mem->Result32);
		v_size_s[5] = mem->v_size;
		/*
		for (int i = 0; i < mem->v_size; i++)
		{
		if (mem->Result32[i] << 20 >> 20 == 0x462)
		{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

		WriteProcessMemory(hProcess, (LPVOID)mem->Result32[i], "\x90\x90\x90\x90\x90\x90\x90\x90", 8, NULL);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] - 9), "\x90\x90\x90\x90\x90", 5, NULL);
		printf("detect_1...\n");
		count2++;
		}
		}
		printf("\n");
		*/

		//detect_2
		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x89\x4D\xE0\x83\x65\xFC\x00", 7);
		Results.push_back(mem->Result32);
		v_size_s[6] = mem->v_size;
		/*
		for (int i = 0; i < mem->v_size; i++)
		{

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 7), "\x90\x90\x90\x90\x90", 5, NULL);
		printf("detect_2...\n");
		count2++;

		}
		printf("\n");
		*/
		//detect_3
		mem->FindPatten32("crossfire", 0x0A000000, 0x10000000, "\xC6\x45\xFC\x02\x8D\x85\x58\xFF\xFF\xFF", 10);
		Results.push_back(mem->Result32);
		v_size_s[7] = mem->v_size;


		//ŒÂ•ÊŒŸ’m‰ñ”ð


		/*mem->FindPatten32("crossfire", 0x0A000000, 0x10000000, "\x89\x45\xFC\x81\x7D\xFC\x32\x6B\x7F\xA3\x0F\x87\x61\x02\x00\x00", 16);
		WriteProcessMemory(hProcess, (LPVOID)0x015387A0, &mem->Result32[0], 4, NULL);

		Results.push_back(mem->Result32);
		v_size_s[8] = mem->v_size;

		*/

		/*
		for (int i = 0; i < mem->v_size; i++)
		{

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 0xA), "\x90", 1, NULL);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 0x11), "\x90", 1, NULL);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 0x14), "\x90\x90\x90\x90\x90", 5, NULL);
		printf("detect_3...\n");
		count2++;

		}
		printf("\n");
		*/
		/*
		//find detect_1
		mem->FindPatten32("crossfire", 0x04000000, 0x10000000, "\x76\x08\x03\x16\x83\xC6\x04\x48\x75\xF8", 10);
		for (int i = 0; i < mem->v_size; i++)
		{
		if (mem->Result32[i] << 20 >> 20 == 0x99A)
		{
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 0xE), "\x90\x90", 2, NULL);
		WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] + 0x19), "\x90\x90", 2, NULL);
		count++;
		printf("detect_1\n");

		}
		}
		*/

		if (bRand == 1)
		{
			mem->Suspend(false);
			Sleep(2320);
			mem->Suspend(true);
			printf("start...\n");
			After();
			printf("done\n");

			mem->FindPatten32("crossfire", 0x0A000000, 0x10000000, "\x8B\x7D\x08\x8B\x4D\x0C\x89\x4D\xF0\x57\x8B\x0F\xFF\x51\x0C", 15);

			for (int i = 0; i < mem->v_size; i++)
			{
				if (mem->Result32[i] << 20 >> 20 == 0xD8A)
				{
					//WriteProcessMemory(hProcess, (LPVOID)(mem->Result32[i] - 6), "\xC7\x45\x10\xFF\xFF\xFF\xFF\xEB\x40", 9, NULL);
				}
			}



			mem->Suspend(false);
			Sleep(-1);
			exit(0);
			break;
		}
		mem->Suspend(false);
		Sleep(100);
	}
}
int main()
{
	Bypass();
}
