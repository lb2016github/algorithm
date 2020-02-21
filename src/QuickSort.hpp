#pragma once
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


void testSortFunc(SortFunc func)
{
	const int length = 10000;
	int data[length];
	for (int i = 0; i < 100; ++i)
	{
		gen_data(data, length);
		func(data, length);
		if (!check_data(data, length))
		{
			cout << "failed" << endl;
			print_data(data, length);
		}
	}
	cout << "success" << endl;
}


///////////////////////// functions for test /////////////////

void quickSort(int* data, int length)
{
	if (length <= 1) return;
	int left = 0, right = length;
	auto swap = [data](int t_left, int t_right)
	{
		auto tmp = data[t_left];
		data[t_left] = data[t_right];
		data[t_right] = tmp;
	};
	do
	{
		do { ++left; } while (data[left] < data[0]);
		do { --right; } while (data[right] > data[0]);
		if (left < right)
		{
			swap(left, right);
		}
	} while (left < right);
	swap(0, right);

	quickSort(data, right);
	quickSort(data + right + 1, length - right - 1);
}

void bubbleSort(int* data, int length)
{

}
