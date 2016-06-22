#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

namespace qh
{
    template<class T>
    class vector {
    public:
		typedef T* iterator;

        //ctor
        vector()
            : alloc_(std::allocator<T>()), _data(NULL), size_(0)
        {
        }

        explicit vector( size_t n, const T& value = T())
			: alloc_(std::allocator<T>())
        {
            _data = new T[n];
            for (size_t i = 0; i < n; i++)
            {
                _data[0] = value;
            }
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
            _data = rhs._data;
            size_ = rhs.size_;
        }

        //dtor
        ~vector()
        {
            if (_data)
            {
                delete _data;
            }
        }

        //get
        size_t size() const {
            return size_;
        }
		
		iterator begin() const {
			return _data;
		}

		iteratro end() const {
			return (_data + _size);
		}
	
        // set & get
        T& operator[](size_t index);

        // set
        void push_back(const T& element);
        void pop_back();
        void resize();
        void reserve();
        void clear();
        void empty();
		void 
    private:
		int reallocation();

		std::allocator alloc_;
        T*      _data;
		size_t cap_;
		size_t size_;
    };
}

#endif


