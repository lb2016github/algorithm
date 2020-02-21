#pragma once
#include <iostream>
#include <random>
#include <string>
#include <time.h>
using namespace std;

typedef void (*SortFunc)(int* data, int length);
///////////////////////// functions for test /////////////////
void gen_data(int* data, int length)
{
	for (int i = 0; i < length; ++i)
	{
		data[i] = rand();
	}
}

void print_data(int* data, int length)
{
	for (int i = 0; i < length; ++i)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

bool check_data(int* data, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		if (data[i] > data[i + 1])
			return false;
	}
	return true;
}


void testSortFunc(SortFunc func, const std::string& name)
{
	auto start = clock();
	cout << "Start test " << name << endl;
	const int length = 10000;
	int data[length];
	for (int i = 0; i < 2; ++i)
	{
		gen_data(data, length);
		func(data, length);
		if (!check_data(data, length))
		{
			cout << "failed" << endl;
			//print_data(data, length);
		}
	}
	cout << "success" << endl;
	cout << "duration: " << clock() - start << endl;
}


///////////////////////// functions for test /////////////////
