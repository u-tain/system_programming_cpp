#include <thread>
#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

// функция слияния двух отсортированных массивов в один отсортированный
void merge_arrays(std::vector<int>& arr, std::vector<int>& buffer, size_t length_left, size_t length_right, int start_left, int start_right)
{
	int idx_left, idx_right, idx_buffer;
	idx_left = idx_right = idx_buffer = 0;

	// слияние массивов, пока не дойдем до конца одного из них
	while ((idx_left < length_left) && (idx_right < length_right))
	{
		if (arr[start_left + idx_left] < arr[start_right + idx_right])
		{
			do {
				buffer[start_left + idx_buffer] = arr[start_left + idx_left];
				++idx_buffer;
				++idx_left;
			} while ((idx_left < length_left) && (arr[start_left + idx_left] < arr[start_right + idx_right]));
		}
		else
		{
			do {
				buffer[start_left + idx_buffer] = arr[start_right + idx_right];
				++idx_buffer;
				++idx_right;
			} while ((idx_right < length_right) && (arr[start_right + idx_right] < arr[start_left + idx_left]));
		}
	}

	// слияние остатка не законченного массива с итоговым
	if (idx_left == length_left)
	{
		for (; idx_right < length_right; ++idx_right)
		{
			buffer[start_left + idx_buffer] = arr[start_right + idx_right];
			++idx_buffer;
		}
	}
	else
	{
		for (; idx_left < length_left; ++idx_left)
		{
			buffer[start_left + idx_buffer] = arr[start_left + idx_left];
			++idx_buffer;
		}
	}

	// копирование итогового упорядоченного массива в исходный
	for (int i = 0; i < idx_buffer; ++i)
	{
		arr[start_left + i] = buffer[start_left + i];
	}
}

// функция сортировки, рекурсивно сортирующая свои половины слиянием
void merge_sort(std::vector<int>& arr, std::vector<int>& buffer, size_t length, int from)
{
	// массив длины 1 упорядочен
	if (length == 1)
	{
		return;
	}
	// делим массив пополам
	int length_left = length / 2;
	int length_right = length - length_left;

	// вызываем рекурсию для левой и правой части
	merge_sort(arr, buffer, length_left, from);
	merge_sort(arr, buffer, length_right, from + length_left);

	// слияние упорядоченных частей
	merge_arrays(arr, buffer, length_left, length - length_left, from, from + length_left);
}

// финальное рекурсивное слияние кусочков, отсортированных потоками
int merge_sorted_after_multithreading(std::vector<int>& arr, std::vector<int>& buffer,
	std::vector<int>& thread_from, std::vector<int>& thread_length,
	unsigned int threads_count, int i_thread)
{
	if (threads_count == 1)
		return thread_length[i_thread];

	int count_left = threads_count / 2;
	int i_thread_left = i_thread;
	int count_right = threads_count - count_left;
	int i_thread_right = i_thread + count_left;

	// вызываем рекурсию для левой и правой части
	int length_left_merged = merge_sorted_after_multithreading(arr, buffer, thread_from, thread_length, count_left, i_thread_left);
	int length_rigth_merged = merge_sorted_after_multithreading(arr, buffer, thread_from, thread_length, count_right, i_thread_right);

	// слияние упорядоченных частей
	merge_arrays(arr, buffer, length_left_merged, length_rigth_merged, thread_from[i_thread_left], thread_from[i_thread_right]);
	return length_left_merged + length_rigth_merged;
}
// функция делит массив на примерно равные части и записывает их длины и индексы начала в массиве
void make_parts(std::vector<int>& thread_from, std::vector<int>& thread_length, unsigned int threads_count, size_t length)
{
	int dlength = (length / threads_count);
	int odd_length = length % threads_count;
	int offset = 0;
	for (int i = 0; i < threads_count; ++i)
	{
		if (odd_length > 0)
		{
			thread_length.push_back(dlength + 1);
			--odd_length;
		}
		else
			thread_length.push_back(dlength);

		thread_from.push_back(offset);
		offset += thread_length[i];
	}
}

// функция многопоточной сортировки слиянием
void merge_sort_multithread(std::vector<int>& arr, std::vector<int>& buffer, unsigned int threads_count)
{
	int length = arr.size();
	std::vector<std::thread> threads;

	// делим массив на примерно равные части, вычисляем указатели на начала частей и их длины
	std::vector<int> thread_from;
	std::vector<int> thread_length;
	make_parts(thread_from, thread_length, threads_count, length);

	// запускаем все потоки
	for (int i = 0; i < threads_count; ++i)
	{
		threads.push_back(std::thread(merge_sort, std::ref(arr), std::ref(buffer), thread_length[i], thread_from[i]));
	}
	
	// ожидаем пока все выполнятся
	for (int i = 0; i < threads_count; ++i)
		threads[i].join();

	merge_sorted_after_multithreading(arr, buffer, thread_from, thread_length, threads_count, 0);
}
//-------------------------------------------------------------

// проверка того, что массив является возрастающим
bool is_increasing_array(std::vector<int>& arr)
{
	for (int j = 0; j < arr.size() - 1; ++j)
	{
		if (arr[j] > arr[j + 1])
			return false;
	}
	return true;
}

// внутри многопоточной сортировки: после выполнения потоков но до слияние сортированный частей
// можно проверить что они отсортированы по возрастанию
void is_increasing_for_sorted_parts(std::vector<int>& arr, std::vector<int>& thread_from, std::vector<int>& thread_length)
{
	for (int i = 0; i < thread_from.size(); ++i)
	{
		for (int j = thread_from[i]; j < thread_length[i] - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
				return;
		}
	}
}

// генерация массива заданной длины
void generate_int_array(std::vector<int>& arr, int length)
{
	for (int i = 0; i < length; ++i)
		arr.push_back(rand() % 15);
}

// проверка равенства двух массивов одинаковой длины
int compare_arrays(std::vector<int>& arr1, std::vector<int>& arr2)
{
	for (int k = 0; k < arr1.size(); ++k)
	{
		if (arr1[k] != arr2[k])
			return k;
	}
	return -1;
}


void get_time()
{
	std::vector<int> array_lengths = { 100, 1000, 10000 , 100000 , 1000000 }; //1000000000 };
	std::vector<long long int> time_usual;
	std::vector<long long int> time_threading;
	auto begin = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();

	unsigned int threads_count = std::thread::hardware_concurrency();
	int test_count = 3;
	std::cout << "Counting time of sorting arrays. Please, wait.\n";
	for (int i_size = 0; i_size < array_lengths.size(); ++i_size)
	{
		for (int i_test = 0; i_test < test_count; ++i_test)
		{
			std::vector<int> arr1;
			generate_int_array(arr1, array_lengths[i_size]);
			std::vector<int> arr2;
			for (int i = 0; i < arr1.size(); ++i)
				arr2.push_back(arr1[i]);
			std::vector<int> buffer;
			for (int i = 0; i < array_lengths[i_size]; ++i)
				buffer.push_back(0);

			begin = std::chrono::steady_clock::now();
			merge_sort(arr1, buffer, array_lengths[i_size], 0);
			end = std::chrono::steady_clock::now();
			time_usual.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

			begin = std::chrono::steady_clock::now();
			merge_sort_multithread(arr2, buffer, threads_count);
			end = std::chrono::steady_clock::now();
			time_threading.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

			assert(compare_arrays(arr1, arr2) == -1);
		}
	}

	std::cout << "Timing in MILLISECONDS for " << threads_count << " threads.\n";

	for (int i_size = 0; i_size < array_lengths.size(); ++i_size)
	{
		std::cout << "Array length = " << array_lengths[i_size] << std::endl;
		std::cout << "Usual merge sort:" << std::endl;
		for (int i_test = 0; i_test < test_count; ++i_test)
		{
			std::cout << i_test + 1 << ". " << time_usual[i_size * 3 + i_test] << " ms" << std::endl;
		}
		std::cout << "Multithread merge sort:" << std::endl;
		for (int i_test = 0; i_test < test_count; ++i_test)
		{
			std::cout << i_test + 1 << ". " << time_threading[i_size * 3 + i_test] << " ms" << std::endl;
		}
		std::cout << "----------------" << std::endl;
	}
}
