#include <qh_vector.cc>

namespace qh 
{
        
	template <class T>
	T& vector<T>::operator[](size_t index) {
		return *(_data + index);
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
		--_size;
		_alloc.destroy(end());		
		return;	
	}
	
	template <class T>
	void vector<T>::resize(size_t new_size, const T& element) {
		if (new_size > _cap) {
			int new_cap = cal_cap(new_size);			
			reserve(new_cap);
		}
		
		if (new_size < _size) {
			erase(begin() + new_size, end());
		} else if (new_size <= _cap) {
			insert(end(), new_size - _size, element);
		}
		
		_size = new_size;
		return;
	}
		
	template <class T>
	void vector<T>::resize(size_t new_size) {
		resize(new_size, T());
	}
	
	template <class T>
	void vector<T>::erase(iterator start, iterator end) {

	}

	template <class T>
	void vector<T>::insert(iterator start, size_t size, const T& element) {

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
	size_t new_cap(size_t new_size) {
		size_t new_cap = _size << 1;
		if (new_size > new_cap)
			return new_size;
		else if (new_size > _size)
			return new_cap;
		return _size; 
	}

	template <class T>
	void reallocate(size_t new_cap) {
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
