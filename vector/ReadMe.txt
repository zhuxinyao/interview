vector 工程

请实现std::vector类的主要功能。函数声明以及写作头文件中。部分实现也做了，但可能不完全正确。

请面试者实现这个类，并补充尽可能详尽的单元测试用例，越多越好，代码逻辑路径覆盖越全越好。

请认真对待，仔细考虑每一个细节问题。

实现vector功能如下
vector()
vector(size_t n, const T& value = T())

vector<T>& operator=(const vector<T>& rhs)
T& operator[](size_t index);

//get
size_t size() const
size_t capacity() const 
iterator begin() const 
iterator end() const 

// set & get
T& at(size_t index);
const T& front();
const T& back();		

// set
void push_back(const T& element);
void pop_back();
void resize();
void reserve(size_t new_cap);
void clear();
bool empty();
void resize(size_t new_size, const T& element = T());
void erase(iterator start, iterator stop);
void insert(const iterator start, size_t n, const T& element);
void insert(const iterator start, const T& element);
void insert(const iterator start, iterator first, iterator last);
