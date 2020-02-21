#pragma once
template<class T>
void swap(T* data, T left, T right)
{
	T tmp = data[left];
	data[left] = data[right];
	data[right] = tmp;
};

template<class T>
void quickSort(T* data, int length)
{
	if (length <= 1) return;
	int left = 0, right = length;
	do
	{
		do { ++left; } while (left < length && data[left] < data[0]);	// ·ÀÖ¹rightÔ½½ç
		do { --right; } while (data[right] > data[0]);
		if (left < right)
		{
			swap(data, left, right);
		}
	} while (left < right);
	swap(data, 0, right);

	quickSort(data, right);
	quickSort(data + right + 1, length - right - 1);
}

template<class T>
void bubbleSort(T* data, int length)
{
	int maxIdx = length - 1;
	do
	{
		int tmp = 0;
		for (int i = 0; i < maxIdx; ++i)
		{
			if (data[i] > data[i + 1])
			{
				swap(data, i, i + 1);
				tmp = i;
			}
		}
		maxIdx = tmp;
	} while (maxIdx > 0);
}

template<class T>
void mergeSort(T* data, int length)
{
	T* tmp_data = new T[length];
	auto mergeData = [data, tmp_data](int i1, int j1, int i2, int j2)
	{
		int i = i1, j = i2, k = 0;
		while (i <= j1 && j <= j2)
		{
			tmp_data[k++] = data[i] <= data[j] ? data[i++] : data[j++];
		}
		while(i <= j1) tmp_data[k++] = data[i++];
		while(j <= j2) tmp_data[k++] = data[j++];
		i = 0;
		while (i < j2 - i1 + 1) data[i1 + i] = tmp_data[i++];
	};
	int size = 1;
	do
	{
		int i1 = 0;
		int j1, i2, j2;
		while (i1 + size < length)
		{
			j1 = i1 + size - 1;
			i2 = i1 + size;
			j2 = i2 + size - 1;
			if (j2 >= length)
			{
				j2 = length - 1;
			}
			mergeData(i1, j1, i2, j2);
			i1 = j2 + 1;
		}
		size *= 2;
	} while (size < length);
	delete[] tmp_data;
}

template<class T>
void heapSort(T* data, int length)
{
	auto adjustDown = [data](int r, int length)
	{
		int child = 2 * r + 1;
		while (child < length)
		{
			if (child + 1 < length && data[child + 1] > data[child]) ++child;	// get the max child
			if (data[child] > data[r]) swap(data, child, r);
			else break;
			r = child;
			child = 2 * r + 1;
		}
	};
	// make max heap
	int r = (length - 2) / 2;
	for (int i = r; i >= 0; --i) adjustDown(i, length);
	// swap head of heap and then adjust down
	for (int i = length; i > 1; --i)
	{
		swap(data, 0, i - 1);
		adjustDown(0, i - 1);
	}
}

template<class T>
void insertSort(T* data, int length)
{
	for (int i = 0; i < length; ++i)
	{
		int j = i;
		int tmp = data[i];
		while (j > 0 && tmp < data[j - 1])
		{
			data[j] = data[j - 1];
			--j;
		}
		data[j] = tmp;
	}
}
