// Events.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	setlocale(0, "rus");
	HANDLE event1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"ev1");
	HANDLE event2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"ev2");

	if (event1 == NULL && event2 ==NULL)
	{
		std::cout << "events not optntd";
		return 0;
	}


	while (true)
	{
		cout << "event 1 or 2" << endl;
		int answ;
		cin >> answ;


		switch (answ)
		{
		case 1:
			{
			SetEvent(event1);
				break;
			}
		default:
		{
			SetEvent(event2);
			break;
		}
		}
	}

}
