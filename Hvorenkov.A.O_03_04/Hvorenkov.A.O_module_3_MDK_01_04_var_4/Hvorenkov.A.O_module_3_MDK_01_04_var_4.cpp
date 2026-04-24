
#include <iostream>
#include <Windows.h>

using namespace std;
const wchar_t name[] = L"C:\\Users\\st310-09\\Desktop\\Hvorenkov.A.O_module_3_MDK_01_04_var_4\\x64\\Debug\\Events.exe";


int counter = 0;

HANDLE Event;
HANDLE Event1;
bool stop = false;



DWORD WINAPI EV1(LPVOID)
{
	while (counter<1000)
	{
		DWORD rez = WaitForSingleObject(Event, 1000);
		if (rez == WAIT_OBJECT_0)
		{
			cout << "вы вызвали первое событие ";
			cout << counter << endl;

		}
	}
	return 0;

}
DWORD WINAPI EV2(LPVOID)
{
	while (counter < 1000)
	{

		DWORD rez1 = WaitForSingleObject(Event1, 1000);
		if (rez1 == WAIT_OBJECT_0)
		{
			cout << "вы вызвали второе событие " << endl;
			if (stop)
			{
				stop = false;
			}
			else
			{
				stop = true;
			}

		}
	}
	
	return 0;
}

int main()
{
	setlocale(0, "rus");


	Event = CreateEvent(NULL, FALSE, FALSE, L"ev1");
	Event1 = CreateEvent(NULL, FALSE, FALSE, L"ev2");

	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };

	if (!CreateProcess(name,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi))
	{
		cout<<"process not created";
	}


	HANDLE pot1 = CreateThread(NULL, 0, EV1, NULL, NULL, NULL);
	HANDLE pot2 = CreateThread(NULL, 0, EV2, NULL, NULL, NULL);


	for (int i = 0; i < 1000; i++)
	{


		if (!stop)
		{
			counter++;
			Sleep(1000);
		}
		else
		{
			i--;
			Sleep(1000);
		}
		
	}

	WaitForSingleObject(pot1, INFINITE);

	CloseHandle(pot1);
	CloseHandle(pot2);

	TerminateProcess(pi.hProcess, 0);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);



	return 0;

}
