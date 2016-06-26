#include <stdlib.h>
#include <vector>
#include "qh_vector.h"

template <class T>
bool compare(std::vector<T>& v1, qh::vector<T>& v2) {
	if (v1.size() != v2.size())
		return false;
	for (size_t i = 0; i < v1.size(); i++) {
		if(v1[i] != v2[i])
			return false;
	}
	
	return true;
}

void test1() {
	std::vector<int> b(5);
	qh::vector<int> c(5);
	assert(compare(b, c));
}

void test2() {
	std::vector<int> a;
	qh::vector<int> b;
	
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);

	b.push_back(1);
	b.push_back(2);
	b.push_back(3);

	assert(compare(a, b));
}

void test3() {
	std::vector<int> b(5, 3);
	qh::vector<int> c(5, 3);

	b.pop_back();
	b.pop_back();
	
	c.pop_back();
	c.pop_back();
	
	assert(compare(b, c));

	b.pop_back();
	b.pop_back();
	
	c.pop_back();
	c.pop_back();
	
	assert(compare(b, c));
}

void test4() {
	std::vector<int> b(5, 1);
	qh::vector<int> c(5, 1);

	b.resize(3);
	c.resize(3);
	
	assert(compare(b, c));

	b.resize(8);
	c.resize(8);
	
	assert(compare(b, c));

	b.resize(30);
	c.resize(30);
	
	assert(compare(b, c));

	b.clear();
	c.clear();
	assert(compare(b, c));

	assert(c.empty());
}

void test5() {
	std::vector<int> b;
	qh::vector<int> c;
	
	for (int i = 0; i < 100; i++) {
		b.push_back(i);
		c.push_back(i);
	}

	b.erase(b.begin(), b.begin() + 5);
	c.erase(c.begin(), c.begin() + 5);	
	assert(compare(b, c));

	b.erase(b.end() - 10, b.end());
	c.erase(c.end() - 10, c.end());
	assert(compare(b, c));	

	b.erase(b.begin() + 5, b.end() - 10);
	c.erase(c.begin() + 5, c.end() - 10);
	assert(compare(b, c));
}

void test6() {
	std::vector<int> b(10, 1);
	qh::vector<int> c(10, 1);
	
	b.insert(b.begin(), 5, 1);
	c.insert(c.begin(), 5, 1);
	assert(compare(b, c));

	b.insert(b.end(), 5, 2);
	c.insert(c.end(), 5, 2);
	assert(compare(b, c));	
	
	b.insert(b.end() - 2, 5, 3);
	c.insert(c.end() - 2, 5, 3);
	assert(compare(b, c));	


	b.insert(b.end() - 3, 2, 4);
	c.insert(c.end() - 3, 2, 4);
	assert(compare(b, c));	
}

void test7() {
	std::vector<int> t(5, 1);
	std::vector<int> tt(3);

	std::vector<std::vector<int> > b(3, t);
	qh::vector<std::vector<int> > c(3, t);
	assert(compare(b, c));

	b.push_back(tt);
	b.push_back(tt);
	c.push_back(tt);
	c.push_back(tt);
	assert(compare(b, c));

	b.pop_back();
	c.pop_back();
	assert(compare(b, c));

	b.resize(10);
	c.resize(10);	
	assert(compare(b, c));

	b.insert(b.begin() + 1, t);
	c.insert(c.begin() + 1, t);
	assert(compare(b, c));
	
	b.erase(b.begin() + 1, b.begin() + 3);
	c.erase(c.begin() + 1, c.begin() + 3);
	assert(compare(b, c));
}


int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
	//test push_back pop_back resize erase insert 
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	//test other object ,i.e, vector<vector>
	test7();
#ifdef WIN32
    system("pause");
#endif

	return 0;
}

