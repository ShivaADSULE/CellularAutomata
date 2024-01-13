// CellularAutomata.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <windows.h>
#include <vector>


int main(int argc,char* argv[])
{
	int rule;
	int totalSize = 100;
	bool isSizeChanged = true;

	bool ruletable[8];
	memset(ruletable, false, sizeof(bool) * 8);

	if (argc == 2) 
	{
		rule = std::stoi(argv[1]);
	}
	else 
	{
		std::cout << "RULE : ";
	}
	std::cin >> rule;

	for (int i = 0; rule != 0; rule/=2, i++) 
	{
		ruletable[i] = rule % 2;
	}
	std::cout << std::endl;
	for (int i = 0; i < 8; i++)std::cout << ruletable[i];
	std::cout <<std::endl;

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	std::vector<bool> data;
	std::vector<bool> temp_data;

	int actualSize;


	while(true)
	{
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
			
			if (totalSize != (csbi.srWindow.Right - csbi.srWindow.Left)) 
			{
				totalSize = csbi.srWindow.Right - csbi.srWindow.Left;
				isSizeChanged = true;
			}
		}

		if(isSizeChanged)
		{
			actualSize = totalSize;
			if (actualSize % 2 == 0 ) actualSize -= 1;

			data.assign(actualSize,false);
			temp_data.assign(actualSize, false);
			system("cls");
			data[(data.size() / 2 + 1)] = 1;
			isSizeChanged = false;
		}

		for(int i = 0; i < actualSize; i++)
		{
			std::cout<<(data[i] ? "O" : " ");
		}
		std::cout << std::endl;

		temp_data.assign(actualSize,false);
		temp_data.begin() = data.begin();		
		temp_data.end() = data.end();

		for(int i=1;i< actualSize -1;i++)
		{
			int index = data[i - 1] * 4 + data[i] * 2 + data[i + 1];
			temp_data[i] = ruletable[index];
		}
		data.assign(temp_data.begin(), temp_data.end());
	
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
