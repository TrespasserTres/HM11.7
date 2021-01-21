#include<iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void mergefile(int* arr1, int* arr2, int* fin, int l1, int l2)
{
    int i = 0, j = 0;
    int k = 0;

    while (i < l1 && j < l2)
    {
        // записываем минимальные элементы обратно во входной массив
        if (arr1[i] <= arr2[j]) {
            fin[k] = arr1[i];
            i++;
        }
        else {
            fin[k] = arr2[j];
            j++;
        }
        k++;
    }
    // записываем оставшиеся элементы левой части
    while (i < l1)
    {
        fin[k] = arr1[i];
        i++;
        k++;
    }
    // записываем оставшиеся элементы правой части
    while (j < l2)
    {
        fin[k] = arr2[j];
        j++;
        k++;
    }
}

void quickSort(int* numbers, int left, int right)
{
    int pivot; // разрешающий элемент
    int l_hold = left; //левая граница
    int r_hold = right; // правая граница
    pivot = numbers[left];
    while (left < right) // пока границы не сомкнутся
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
            left++; // сдвигаем левую границу вправо
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
            right--; // сдвигаем правую границу вправо
        }
    }
    numbers[left] = pivot; // ставим разрешающий элемент на место
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSort(numbers, left, pivot - 1);
    if (right > pivot)
        quickSort(numbers, pivot + 1, right);
}

void write_arr(const string& filename, const int* arr, const int n)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if (fs.is_open()) // проверяем, что файл успешно открыт
    {
        fs << n << '\n';  // записываем размер массива
        for (int i = 0; i < n; i++)
            fs << arr[i] << ' '; // записываем значения через пробел
        fs << '\n';

        fs.close(); // закрываем файл
    }
}

void read_arr(const string& filename, int*& arr, int& n)
{
    fstream fs;

    fs.open(filename, fstream::in);
    if (fs.is_open()) // проверяем, что файл успешно открыт
    {
        fs >> n;  // читаем размер массива
        arr = new int[n];
        for (int i = 0; i < n; i++)
            fs >> arr[i]; // читаем из файла разделительные символы - пробел и перенос строки

        fs.close(); // закрываем файл
    }
}

int main()
{
    // Подготовка файлов

    string filename = "array_1.txt";     // Подготовка 1го файла
    const int size = 1000000;
    int* rand_arr = new int[size];

    srand(time(nullptr));                                // используем текущее время, чтобы сгенерировать рандомные значения
    int lef_border = 100;
    int range_len = 100000;                               // правая граница
    for (int i = 0; i < size; i++)
        rand_arr[i] = lef_border + rand() % range_len;   // генерируем число в указанном диапазоне и записываем в массив

    write_arr(filename, rand_arr, size); // записываем массив в файл


    string filename2 = "array_2.txt";   // Подготовка 2го файла
    const int size2 = 1000000;
    int* rand_arr2 = new int[size2];

    lef_border = 1;
    range_len = 20000;                                     // правая граница 
    for (int i = 0; i < size2; i++)
        rand_arr2[i] = lef_border + rand() % range_len; // генерируем число в указанном диапазоне и записываем в массив

    write_arr(filename2, rand_arr2, size2);             // записываем массив в файл

    string filename3 = "array_3.txt";   // Подготовка 3го файла
    const int size3 = 1000000;
    int* rand_arr3 = new int[size3];

    lef_border = 100;
    range_len = 20000;                                     // правая граница 
    for (int i = 0; i < size3; i++)
        rand_arr3[i] = lef_border + rand() % range_len; // генерируем число в указанном диапазоне и записываем в массив

    write_arr(filename3, rand_arr3, size3);             // записываем массив в файл

    string filename4 = "array_4.txt";   // Подготовка 4го файла
    const int size4 = 1000000;
    int* rand_arr4 = new int[size4];

    lef_border = 1000;
    range_len = 20000;                                     // правая граница 
    for (int i = 0; i < size4; i++)
        rand_arr4[i] = lef_border + rand() % range_len; // генерируем число в указанном диапазоне и записываем в массив

    write_arr(filename4, rand_arr4, size4);             // записываем массив в файл

    // Сортируем файлы

    int* array_from_file = nullptr;
    int n = 0;
    read_arr(filename, array_from_file, n);             // читаем массив из файла

    quickSort(array_from_file, 0, n - 1);               // запускаем сортировку
    string filenametemp1 = "array_temp1.txt";
    write_arr(filenametemp1, array_from_file, size);    // записываем отсортировнный массив во временный файл

    int* array_from_file2 = nullptr;
    int m = 0;
    read_arr(filename2, array_from_file2, m);          // читаем массив из файла

    quickSort(array_from_file2, 0, m - 1);             // запускаем сортировку
    string filenametemp2 = "array_temp2.txt";
    write_arr(filenametemp2, array_from_file2, size2); // записываем отсортировнный массив во временный файл

    int* array_from_file3 = nullptr;
    int q = 0;
    read_arr(filename3, array_from_file3, q);          // читаем массив из файла

    quickSort(array_from_file3, 0, q - 1);             // запускаем сортировку
    string filenametemp3 = "array_temp3.txt";
    write_arr(filenametemp3, array_from_file3, size3); // записываем отсортировнный массив во временный файл

    int* array_from_file4 = nullptr;
    int w = 0;
    read_arr(filename4, array_from_file4, w);          // читаем массив из файла

    quickSort(array_from_file4, 0, w - 1);             // запускаем сортировку
    string filenametemp4 = "array_temp4.txt";
    write_arr(filenametemp4, array_from_file4, size4); // записываем отсортировнный массив во временный файл

    // Объединяем файлы

    int* prefin1 = new int[size + size2];
    array_from_file = nullptr;
    array_from_file2 = nullptr;
    n = 0;

    read_arr(filenametemp1, array_from_file, n);                    // читаем массив из файла
    read_arr(filenametemp2, array_from_file2, n);                   // читаем массив из файла
    mergefile(array_from_file, array_from_file2, prefin1, size, size2); // Объединяем файлы

    string filenameprefin1 = "array_1+2.txt";                   // Создаём общий файл
    write_arr(filenameprefin1, prefin1, size + size2);          // записываем массив в файл

    int* prefin2 = new int[size3 + size4];
    array_from_file3 = nullptr;
    array_from_file4 = nullptr;

    read_arr(filenametemp3, array_from_file3, n);                          // читаем массив из файла
    read_arr(filenametemp4, array_from_file4, n);                          // читаем массив из файла
    mergefile(array_from_file3, array_from_file4, prefin2, size3, size4);  // Объединяем файлы

    string filenameprefin2 = "array_3+4.txt";                              // Создаём общий файл
    write_arr(filenameprefin2, prefin2, size3 + size4);                    // записываем массив в файл

    int* fin = new int[size + size2 + size3 + size4];
    array_from_file = nullptr;
    array_from_file2 = nullptr;

    read_arr(filenameprefin1, array_from_file, n);                        // читаем массив из файла
    read_arr(filenameprefin2, array_from_file2, n);                        // читаем массив из файла
    mergefile(prefin1, prefin2, fin, size + size2, size3 + size4);                        // Объединяем файлы

    string filenamefin = "array1-4.txt";                                   // Создаём общий файл
    write_arr(filenamefin, fin, size + size2 + size3 + size4);             // записываем массив в файл

    remove("array_temp1.txt");              // удаление временных файлов
    remove("array_temp2.txt");              // удаление временных файлов
    remove("array_temp3.txt");              // удаление временных файлов
    remove("array_temp4.txt");              // удаление временных файлов

    delete[] rand_arr;
    delete[] rand_arr2;
    delete[] rand_arr3;
    delete[] rand_arr4;
    delete[] prefin1;
    delete[] prefin2;
    delete[] array_from_file;
    delete[] array_from_file2;
    delete[] array_from_file3;
    delete[] array_from_file4;
    return 0;
}