#pragma warning(disable:4996)
#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>

using namespace std;

#define SIZE_OF_ARRAY(ary)  (sizeof(ary)/sizeof((ary)[0]))

class Memory
{
public:

	Memory(char * pname)
	{
		hProcess = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcessByName(pname));
		Result32 = 0;
		Result64 = 0;
		v_size = 0;
	}
	Memory()
	{
		hProcess = 0;
		Result32 = 0;
		Result64 = 0;
		v_size = 0;
	}
	~Memory()
	{
		hProcess = 0;
		Result32 = 0;
		Result64 = 0;
		v_size = 0;
	}
	DWORD GetProcessByName(char* name)
	{
		DWORD pid = 0;

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 process;
		ZeroMemory(&process, sizeof(process));
		process.dwSize = sizeof(process);

		if (Process32First(snapshot, &process))
		{
			do
			{
				if (strstr(process.szExeFile, name) != NULL)
				{
					pid = process.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &process));
		}

		CloseHandle(snapshot);

		if (pid != 0)
		{
			return pid;
		}

		return NULL;

	}

	bool FindPatten32(char * PNAME, DWORD START_ADDR, DWORD END_ADDR, void* patten, DWORD Len)
	{
		CHAR *MemoryBuffer = new CHAR[4096];
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcessByName(PNAME));
		DWORD ADDR = START_ADDR;
		DWORD ADDR_E = END_ADDR;

		vector<DWORD> Store_Buffer;

		if (hProcess == 0)
			return false;

		for (;;)
		{
			ReadProcessMemory(hProcess, (LPVOID)ADDR, (LPVOID)MemoryBuffer, 4096, NULL);

			for (int s = 0; s < 4096; s++)
			{
				ADDR++;
				MemoryBuffer++;
				if (memcmp(MemoryBuffer, patten, Len) == 0)
				{
					Store_Buffer.push_back(ADDR);
				}
			}
			MemoryBuffer -= 4096;

			if (ADDR > ADDR_E)
			{
				v_size = Store_Buffer.size();
				Result32 = (DWORD*)malloc(v_size * sizeof(DWORD));

				for (DWORD i = 0; i < v_size; i++)
				{
					Result32[i] = Store_Buffer[i];
				}
				return true;
			}
		}
		return false;
	}

	bool FindPatten64(char * PNAME, DWORD64 START_ADDR, DWORD64 END_ADDR, void* patten, DWORD Len)
	{
		CHAR *MemoryBuffer = new CHAR[4096];
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcessByName(PNAME));
		DWORD64 ADDR = START_ADDR;
		DWORD64 ADDR_E = END_ADDR;

		vector<DWORD64> Store_Buffer;

		if (hProcess == 0)
			return false;

		for (;;)
		{
			ReadProcessMemory(hProcess, (LPVOID)ADDR, (LPVOID)MemoryBuffer, 4096, NULL);

			for (int s = 0; s < 4096; s++)
			{
				ADDR++;
				MemoryBuffer++;
				if (memcmp(MemoryBuffer, patten, Len) == 0)
				{
					Store_Buffer.push_back(ADDR);
				}
			}
			MemoryBuffer -= 4096;

			if (ADDR > ADDR_E)
			{
				v_size = Store_Buffer.size();
				Result64 = (DWORD64*)malloc(v_size * sizeof(DWORD64));

				for (DWORD i = 0; i < v_size; i++)
				{
					Result64[i] = Store_Buffer[i];
				}
				return true;
			}
		}
		return false;
	}

	DWORD GetModuleBase32(LPSTR lpModuleName, DWORD dwProcessId)
	{
		MODULEENTRY32 lpModuleEntry = { 0 };
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
		if (!hSnapShot)
			return NULL;
		lpModuleEntry.dwSize = sizeof(lpModuleEntry);
		BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);
		while (bModule)
		{
			if (!strcmp(lpModuleEntry.szModule, lpModuleName))
			{
				CloseHandle(hSnapShot);
				return (DWORD)lpModuleEntry.modBaseAddr;
			}
			bModule = Module32Next(hSnapShot, &lpModuleEntry);
		}
		CloseHandle(hSnapShot);
		return NULL;
	}

	DWORD64 GetModuleBase64(LPSTR lpModuleName, DWORD dwProcessId)
	{
		MODULEENTRY32 lpModuleEntry = { 0 };
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
		if (!hSnapShot)
			return NULL;
		lpModuleEntry.dwSize = sizeof(lpModuleEntry);
		BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);
		while (bModule)
		{
			if (!strcmp(lpModuleEntry.szModule, lpModuleName))
			{
				CloseHandle(hSnapShot);
				return (DWORD64)lpModuleEntry.modBaseAddr;
			}
			bModule = Module32Next(hSnapShot, &lpModuleEntry);
		}
		CloseHandle(hSnapShot);
		return NULL;
	}

	DWORD GetCall(DWORD CallingAddr)
	{
		BYTE * buffer = new BYTE[4];
		DWORD N = 0;
		if (!ReadProcessMemory(hProcess, (LPVOID)(CallingAddr + 1), (LPVOID)buffer, 4, NULL))
			return 0;

		memcpy(&N, buffer, 4);
		return N + CallingAddr + 5;
	}
	void Free()
	{
		free(Result32);
		free(Result64);
	}


	void Suspend(bool isEnable)
	{
		_NtSuspendProcess NtSuspendProcess = 0;
		_NtResumeProcess NtResumeProcess = 0;

		NtSuspendProcess = (_NtSuspendProcess)GetProcAddress(GetModuleHandle("ntdll"), "NtSuspendProcess");

		NtResumeProcess = (_NtResumeProcess)GetProcAddress(GetModuleHandle("ntdll"), "NtResumeProcess");

		if (isEnable)
			NtSuspendProcess(hProcess);
		else
			NtResumeProcess(hProcess);
	}
	DWORD *Result32;
	DWORD64 *Result64;
	DWORD v_size;
private:
	HANDLE hProcess;

	typedef LONG(NTAPI *_NtSuspendProcess)(IN HANDLE ProcessHandle);
	typedef LONG(NTAPI *_NtResumeProcess)(IN HANDLE ProcessHandle);
};
