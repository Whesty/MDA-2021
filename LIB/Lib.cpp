#include <iostream>
//���������� ��� ��� ����� ������� ��� �� ����� C

extern "C"
{
	int __stdcall len(char* source)
	{
		int result = 0;
		while (source[result] != '\0')
		{
			result++;
		}
		return result;
	}

	int __stdcall stcmp(char* source1, char* source2)
	{
		return -strcmp(source1, source2);
	}

	int __stdcall outw(char* value)
	{
		setlocale(0, "");
		std::cout << value << std::endl;
		return 0;
	}

	int __stdcall outn(int value)
	{
		std::cout << value << std::endl;
		return 0;
	}
}