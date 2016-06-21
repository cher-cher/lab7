// FindMax.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "FindMax.h"

int main(int argc, char * argv[])
{
	std::string s1, s2;
	const char * maxValue;
	// Считываем строки в переменные s1 и s2
	std::getline(std::cin, s1);
	std::getline(std::cin, s2);

	// Получаем указатели на хранящиеся в строках массивы символов
	std::vector<const char*> p1;
	p1.push_back(s1.c_str());
	p1.push_back(s2.c_str());

	FindMax(p1, maxValue);
	return 0;
}

