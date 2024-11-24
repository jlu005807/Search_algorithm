//����
//������ָ���ݸ�����ĳ��ֵ���ڲ��ұ���ȷ��һ����ؼ��ֵ�ǧ����ֵ�ļ�¼������Ԫ�ء�
//����ĳ��ֵΪ�ؼ��֣�������Ԫ�أ����¼�� ��ĳ���������ֵ���������Ա�ʶһ������Ԫ�أ����¼����


#include "random_array.h"  
#include "Sequential_List.h"

void Test_SeqList()
{
    random_array generator;

    // ���������������
    std::vector<int> randomVector = generator.generateRandomVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    // ������ɲ���ֵ
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size()+5);
    int randomIndex = dis(gen);
    int searchKey = randomIndex < randomVector.size() ? randomVector[randomIndex] : randomIndex;  // ���ѡ�������е�ĳ��ֵ��Ϊ����Ŀ��

    // ����˳�����
    int indexSeq = Search_Seq(randomVector, searchKey);
    std::cout << "Sequential Search: Key " << searchKey
        << " found at index " << indexSeq << std::endl;

    // ����˳�����
    int indexSeq1 = Search_Seq_modify(randomVector, searchKey);
    std::cout << "Sequential Search: Key " << searchKey
        << " found at index " << indexSeq1 << std::endl;

    // ���������������
    std::vector<int> orderedVector = generator.generateRandomOrderedVector();
    std::cout << "\nOrdered Vector:" << std::endl;
    printArray(orderedVector);

    // ������ɲ���ֵ
    std::uniform_int_distribution<> disOrdered(0, orderedVector.size() + 5);
    int randomOrderedIndex = disOrdered(gen);
    int searchKeyOrdered = randomOrderedIndex< orderedVector.size()?orderedVector[randomOrderedIndex]: randomOrderedIndex;  // ���ѡ�������е�ĳ��ֵ��Ϊ����Ŀ��

    // ���Զ��ֲ��ң�������ʵ�֣�
    int indexBin = Binary_Search(orderedVector.data(), 0, orderedVector.size() - 1, searchKeyOrdered);
    std::cout << "Binary Search (closed interval): Key " << searchKeyOrdered
        << " found at index " << indexBin << std::endl;

    // ���Զ��ֲ��ң�����ҿ�ʵ�֣�
    int indexBinOpen = Binary_Search(orderedVector.data(), orderedVector.size(), searchKeyOrdered);
    std::cout << "Binary Search (left-closed right-open): Key " << searchKeyOrdered
        << " found at index " << indexBinOpen << std::endl;

    // ��������ҿ��ݹ�ʵ��
    int indexOpen1 = Binary_Search_Recursive(orderedVector.data(), 0, orderedVector.size() - 1, searchKeyOrdered);
    std::cout << "Binary_Search_Recursive:"<<"Key " << searchKeyOrdered << " found at index " << indexOpen1 << std::endl;

    int indexOpen2 = Binary_Search_Recursive_Open(orderedVector.data(), 0, orderedVector.size() - 1, searchKeyOrdered);
    std::cout << "Binary_Search_Recursive_Open:"<< "Key " << searchKeyOrdered << " found at index "  << indexOpen2 <<  std::endl;

    return;
}

//����һ�¶԰����
void Test_cbiSearch()
{
    random_array generator;

    // �����������
    std::vector<int> randomVector = generator.generateRandomOrderedVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    int* arr1 = randomVector.data();
    int n1 = randomVector.size();

    // ������ɲ���ֵ
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size());
    int randomIndex = dis(gen);
    int searchKey1 = randomVector[randomIndex]; // ���ѡ�������е�ĳ��ֵ��Ϊ����Ŀ��

    // �������� 1���������ң�Ŀ��ֵ����
    std::cout << "Test 1: key:" << searchKey1 << std::endl;
    std::cout << cbiSearch(arr1, n1, searchKey1) << std::endl;

    // �������� 2������ʧ�ܣ�Ŀ��ֵ������
    std::cout << "Test 2: ";
    std::cout << cbiSearch(arr1, n1, 1001)<< std::endl;

    // �������� 3���߽�ֵ����һ�������һ��Ԫ�أ�
    std::cout << "Test 3a: key:" << randomVector[0] << std::endl;
    std::cout << cbiSearch(arr1, n1, randomVector[0]) << std::endl;
    std::cout << "Test 3b: key:" << randomVector[n1-1] << std::endl;
    std::cout << cbiSearch(arr1, n1, randomVector[n1-1])  << std::endl;   
}

void Test_Fibonacci_Search()
{
    random_array generator;

    // �����������
    std::vector<int> randomVector = generator.generateRandomOrderedVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    // ������ɲ���ֵ
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size() + 5);
    int randomIndex = dis(gen);
    int searchKey = randomIndex < randomVector.size() ? randomVector[randomIndex] : randomIndex;  // ���ѡ�������е�ĳ��ֵ��Ϊ����Ŀ��

    int indexOpen1 =Fibonacci_Search(randomVector.data(), randomVector.size() , searchKey);
    std::cout << "Fibonacci_Search:" << "Key " << searchKey << " found at index " << indexOpen1 << std::endl;
}

void Test_InterPolationSearch()
{
    random_array generator;

    // �����������
    std::vector<int> randomVector = generator.generateRandomOrderedVector();
    std::cout << "Random Vector:" << std::endl;
    printArray(randomVector);

    // ������ɲ���ֵ
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, randomVector.size() + 5);
    int randomIndex = dis(gen);
    int searchKey = randomIndex < randomVector.size() ? randomVector[randomIndex] : randomIndex;  // ���ѡ�������е�ĳ��ֵ��Ϊ����Ŀ��

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