//查找
//查找是指根据给定的某个值，在查找表中确定一个其关键字等千给定值的记录或数据元素。
//其中某个值为关键字，即数据元素（或记录） 中某个数据项的值，用它可以标识一个数据元素（或记录）。


#include "random_array.h"  
#include "Sequential_List.h"

void Test_SeqList()
{
    random_array generator;

    // 生成随机无序数组
    std::vector<int> randomVector = generator.generateRandomVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    // 随机生成查找值
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size()+5);
    int randomIndex = dis(gen);
    int searchKey = randomIndex < randomVector.size() ? randomVector[randomIndex] : randomIndex;  // 随机选择数组中的某个值作为查找目标

    // 测试顺序查找
    int indexSeq = Search_Seq(randomVector, searchKey);
    std::cout << "Sequential Search: Key " << searchKey
        << " found at index " << indexSeq << std::endl;

    // 测试顺序查找
    int indexSeq1 = Search_Seq_modify(randomVector, searchKey);
    std::cout << "Sequential Search: Key " << searchKey
        << " found at index " << indexSeq1 << std::endl;

    // 生成随机有序数组
    std::vector<int> orderedVector = generator.generateRandomOrderedVector();
    std::cout << "\nOrdered Vector:" << std::endl;
    printArray(orderedVector);

    // 随机生成查找值
    std::uniform_int_distribution<> disOrdered(0, orderedVector.size() + 5);
    int randomOrderedIndex = disOrdered(gen);
    int searchKeyOrdered = randomOrderedIndex< orderedVector.size()?orderedVector[randomOrderedIndex]: randomOrderedIndex;  // 随机选择数组中的某个值作为查找目标

    // 测试二分查找（闭区间实现）
    int indexBin = Binary_Search(orderedVector.data(), 0, orderedVector.size() - 1, searchKeyOrdered);
    std::cout << "Binary Search (closed interval): Key " << searchKeyOrdered
        << " found at index " << indexBin << std::endl;

    // 测试二分查找（左闭右开实现）
    int indexBinOpen = Binary_Search(orderedVector.data(), orderedVector.size(), searchKeyOrdered);
    std::cout << "Binary Search (left-closed right-open): Key " << searchKeyOrdered
        << " found at index " << indexBinOpen << std::endl;

    // 测试左闭右开递归实现
    int indexOpen1 = Binary_Search_Recursive(orderedVector.data(), 0, orderedVector.size() - 1, searchKeyOrdered);
    std::cout << "Binary_Search_Recursive:"<<"Key " << searchKeyOrdered << " found at index " << indexOpen1 << std::endl;

    int indexOpen2 = Binary_Search_Recursive_Open(orderedVector.data(), 0, orderedVector.size() - 1, searchKeyOrdered);
    std::cout << "Binary_Search_Recursive_Open:"<< "Key " << searchKeyOrdered << " found at index "  << indexOpen2 <<  std::endl;

    return;
}

//测试一致对半查找
void Test_cbiSearch()
{
    random_array generator;

    // 生成随机数组
    std::vector<int> randomVector = generator.generateRandomOrderedVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    int* arr1 = randomVector.data();
    int n1 = randomVector.size();

    // 随机生成查找值
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size());
    int randomIndex = dis(gen);
    int searchKey1 = randomVector[randomIndex]; // 随机选择数组中的某个值作为查找目标

    // 测试用例 1：正常查找，目标值存在
    std::cout << "Test 1: key:" << searchKey1 << std::endl;
    std::cout << cbiSearch(arr1, n1, searchKey1) << std::endl;

    // 测试用例 2：查找失败，目标值不存在
    std::cout << "Test 2: ";
    std::cout << cbiSearch(arr1, n1, 1001)<< std::endl;

    // 测试用例 3：边界值（第一个和最后一个元素）
    std::cout << "Test 3a: key:" << randomVector[0] << std::endl;
    std::cout << cbiSearch(arr1, n1, randomVector[0]) << std::endl;
    std::cout << "Test 3b: key:" << randomVector[n1-1] << std::endl;
    std::cout << cbiSearch(arr1, n1, randomVector[n1-1])  << std::endl;   
}

void Test_Fibonacci_Search()
{
    random_array generator;

    // 生成随机数组
    std::vector<int> randomVector = generator.generateRandomOrderedVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    // 随机生成查找值
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size() + 5);
    int randomIndex = dis(gen);
    int searchKey = randomIndex < randomVector.size() ? randomVector[randomIndex] : randomIndex;  // 随机选择数组中的某个值作为查找目标

    int indexOpen1 =Fibonacci_Search(randomVector.data(), randomVector.size() , searchKey);
    std::cout << "Fibonacci_Search:" << "Key " << searchKey << " found at index " << indexOpen1 << std::endl;
}

void Test_InterPolationSearch()
{
    random_array generator;

    // 生成随机数组
    std::vector<int> randomVector = generator.generateRandomOrderedVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    // 随机生成查找值
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size() + 5);
    int randomIndex = dis(gen);
    int searchKey = randomIndex < randomVector.size() ? randomVector[randomIndex] : randomIndex;  // 随机选择数组中的某个值作为查找目标

    int indexOpen1 = InterPolation_Search(randomVector.data(), randomVector.size(), searchKey);
    std::cout << "InterPolation_Search:" << "Key " << searchKey << " found at index " << indexOpen1 << std::endl;
}
int main()
{
    Test_SeqList();
    system("Pause");

    Test_cbiSearch();
    system("Pause");

    Test_Fibonacci_Search();
    system("Pause");

    Test_InterPolationSearch();
    system("Pause");
}