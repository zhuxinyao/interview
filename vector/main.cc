#include <stdlib.h>
#include "qh_vector.h"


int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�
    qh::vector<int> num_vect(3, 0);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
    num_vect.push_back(1);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.insert(num_vect.begin(), 2, 1);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.pop_back();
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.insert(num_vect.begin(), 4, 2);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.insert(num_vect.end(), 3, 3);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.insert(num_vect.end() - 1, 2, 9);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.resize(5);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.resize(10);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	num_vect.reserve(20);
	printf("%d %d\n", num_vect.size(), num_vect.capacity());
	for (int i = 0; i < num_vect.size(); i++)
		printf("%d\n", num_vect[i]);

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

