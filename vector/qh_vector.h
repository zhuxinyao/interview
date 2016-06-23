#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <assert.h>
#include <algorithm>

namespace qh
{
    template <class T>
    class vector {
    public:
		typedef T* iterator;

        //ctor
        vector()
            : _alloc(std::allocator<T>()), _data(NULL), _cap(0), _size(0) {}

        explicit vector( size_t n, const T& value = T())
			: _alloc(std::allocator<T>()) {
			_data = _alloc.allocate(n);
			_cap = n;
			_size = n;	
            for (size_t i = 0; i < n; i++) {
				_alloc.construct(_data + i, value);
            }
        }

        vector<T>& operator=(const vector<T>& rhs) {
			if (_size != 0)
				erase(begin(), end());
			if (rhs.size > _cap)
				reserve(rhs.capacity());

			for (iterator i = rhs.begin(), j = begin(); \
					i < rhs.end(); i++, j++) {
				_alloc.construct(j, *i);
			}
			_size = rhs.size();
			return *this;
        }

        //dtor
        ~vector() {
            if (_data) {
                _alloc.deallocate(_data, _cap);
            }
        }

        //get
        size_t size() const {
            return _size;
        }
		
		size_t capacity() const {
			return _cap;
		}
	
		iterator begin() const {
			return _data;
		}

		iterator end() const {
			return (_data + _size);
		}
	
        // set & get
        T& operator[](size_t index);
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

    private:
		void reallocate(size_t new_cap);
		size_t cal_cap(size_t new_cap);
		
		std::allocator<T> _alloc;
        T*      _data;
		size_t _cap;
		size_t _size;
    };
	
	//
	//implement vector
	//

	template <class T>
	T& vector<T>::operator[](size_t index) {
		return *(_data + index);
	}
	
	template <class T>
	T& vector<T>::at(size_t index) {
		assert(index < _size && index >= 0);
		return *(_data + index);
	}

	template <class T>
	const T& vector<T>::front() {
		if (_data == NULL) 
			return NULL;
		return _data[0];
	}	
	
	template <class T>
	const T& vector<T>::back() {
		if (_data == NULL)
			return NULL;
		return _data[_size - 1];
	}	
	
	template <class T> 
	void vector<T>::push_back(const T& element) {
		if (_size >= _cap) {
			size_t new_cap = cal_cap(_size + 1);
			reserve(new_cap);
		}
		_alloc.construct(end(), element);
		_size++;
		return;
	}
	
	template <class T>
	void vector<T>::pop_back() {
		if (_size == 0)
			return;
		--_size;
		_alloc.destroy(end());		
		return;	
	}
	
	template <class T>
	void vector<T>::resize(size_t new_size, const T& element) {
		if (new_size < _size) {
			erase(begin() + new_size, end());
		} else if (new_size > _size) {
			insert(end(), new_size - _size, element);
		}
		
		_size = new_size;
		return;
	}
	
	template <class T>
	void vector<T>::erase(iterator start, iterator stop) {
		size_t n = (size_t)(stop - start);
		assert(start >= _data && start <= stop && stop <= end());		
		for (iterator i = start; i < stop; i++) {
			_alloc.destroy(i);
		}
		
		for (iterator i = start, j = stop; j < end(); i++, j++) {
			_alloc.construct(i, *j);
		}	

		for (iterator i = end() - n; i < end(); i++) {
			_alloc.destroy(i);
		}

		_size -= n;
		return;
	}

	template <class T>
	void vector<T>::insert(const iterator start, size_t n, const T& element) {
		size_t pos = start - _data;
		if (n == 0) return;
		if (_size + n > _cap) {
			size_t new_cap = cal_cap(_size + n);			
			reserve(new_cap);
		}
		size_t new_size = _size + n;
		T copy = element;
		assert(new_size <= _cap);
		if (end() > _data + pos + n) {
			for (iterator i = end(), j = end() - n; \
					j < end(); i++, j++) {
				_alloc.construct(i, *j);
			}
			
			std::copy_backward(_data + pos, end() - n, end());
	
			for (iterator i = _data + pos; i < (_data + pos + n); i++) {
				_alloc.construct(i, copy);
			}
		} else {
			for (iterator i = _data + pos + n, j = _data + pos; j < end(); i++, j++) {
				_alloc.construct(i, *j);
			} 
			
			for (iterator i = _data + pos; i < (_data + pos + n); i++) {
				_alloc.construct(i, copy);
			}
		}
		_size = new_size;	
		return ;
	}
	
	template <class T>
	void vector<T>::insert(const iterator start, const T& element) {
		insert(start, 1, element);
	}
	
	template <class T>
	void vector<T>::insert(const iterator start, iterator first, iterator last) {
		size_t n = last - first;
		if (n == 0) return;
		size_t pos = start - _data;
		if (_size + n > _cap) {
			int new_cap = cal_cap(_size + n);			
			reserve(new_cap);
		}
		int new_size = _size + n;
		assert(new_size <= _cap);
		assert(first != NULL && first <= last);

		if (end() > _data + pos + n) {
			for (iterator i = end(), j = end() - n; \
					j < end(); i++, j++) {
				_alloc.construct(i, *j);
			}
			
			std::copy_backward(_data + pos, end() - n, end());
			
			for (iterator i = _data + pos, j = first; i < (_data + pos + n); i++, j++) {
				_alloc.construct(i, *j);
			}
		} else {
			for (iterator i = _data + pos + n, j = _data + pos; j < end(); i++, j++) {
				_alloc.construct(i, *j);
			} 
			
			for (iterator i = _data + pos, j = first; i < (_data + pos + n); i++, j++) {
				_alloc.construct(i, *j);
			}
		}
		_size = new_size;	
		return ;
	}
	
	template <class T>
	void vector<T>::reserve(size_t new_cap) {
		if (_data == NULL) {	
			_cap = new_cap;
			_data = _alloc.allocate(_cap);	
		} else {			
			reallocate(new_cap);				
		}
	}
	
	template <class T>
	void vector<T>::clear() {
		for (int i = 0; i < _size; i++) {
			_alloc.destroy(_data + i);
		}
		_size = 0;
	}
	
	template <class T>
	bool vector<T>::empty() {
		if (_size == 0)
			return true;
		else
			return false;
	}

	template <class T>
	size_t vector<T>::cal_cap(size_t new_size) {
		size_t new_cap = _size << 1;
		if (new_size > new_cap)
			return new_size;
		else if (new_size > _size)
			return new_cap;
		return _size; 
	}
	
	template <class T>
	void vector<T>::reallocate(size_t new_cap) {
		if (new_cap <= _cap)
			return;
		
		iterator old_data = _data;
		size_t old_cap = _cap;
		_cap = new_cap;
		_data = _alloc.allocate(_cap);	
		
		for (size_t i = 0; i < _size; i++) {
			_alloc.construct(&_data[i], old_data[i]);
		}
		_alloc.deallocate(old_data, old_cap);
	}
}

#endif


