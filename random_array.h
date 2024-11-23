#pragma once
#include <iostream>
#include <random>
#include <vector>

// ����ָ����Χ�ڵ������������
class random_array
{
public:
    std::vector<int> generateRandomVector()
    {
        std::random_device rd;   // ��ȡ����豸
        std::mt19937 gen(rd());  // ʹ�� Mersenne Twister �����������

        // �����������Ĵ�С
        std::uniform_int_distribution<> size_dis(10, 30);
        int size = size_dis(gen);


        // ����������½�
        std::uniform_int_distribution<> lower_dis(-100, 0);
        std::uniform_int_distribution<> upper_dis(0, 1000);
        int lower = lower_dis(gen);
        int upper = upper_dis(gen);

        // �����������
        std::uniform_int_distribution<> value_dis(lower, upper);
        std::vector<int> arr(size); // ����һ��ָ����С����������
        for (int i = 0; i < size; i++)
        {
            arr[i] = value_dis(gen); // �������
        }

        return arr; // �������ɵ�����
    }

     //������������
    std::vector<int> generateRandomOrderedVector()
    {
        std::vector<int> v = generateRandomVector();
        std::sort(v.begin(), v.end());
        return v;
    }
};


// ��ӡ std::vector<int> ����
void printArray(const std::vector<int>& arr)
{
    int count = 0; // Ԫ�ؼ�����
    for (const int& num : arr) {
        std::cout << num << " ";
        count++;
        if (count % 5 == 0) { // ÿ���Ԫ�ػ���
            std::cout << std::endl;
        }
    }
    if (count % 5 != 0) { // ������һ�в������������
        std::cout << std::endl;
    }
}

// ��ӡ����
void printArray(const std::vector<uint32_t>& arr)
{
    for (const int& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// ��ӡ����
void printArray(const int* arr, int n)
{
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
