#include "Sarr.h"

void smart_array::add_element(int element) {
	// Если массив заполнен, увеличиваем емкость
	if (size_ >= capacity_) {
		resize();
	}
	data_[size_] = element;
	size_++;
}

int smart_array::get_element(size_t index) const {
	if (index >= size_)  {                                  // удалена проверка на отрицательные значения index
		throw std::out_of_range("Индекс вне диапазона");
	}
	return data_[index];
}

size_t smart_array::get_size() const {
	return size_;
}

size_t smart_array::get_capacity() const {
	return capacity_;
}

size_t smart_array::get_count() const {
	return size_;
}

void smart_array::print() const {
	for (int i{ 0 }; i < size_;i++) {
		std::cout << data_[i] << ", ";
	}
	std::cout << "\t" << std::endl;
}

void smart_array::resize() {
	if (capacity_ == 0) {                            // Проверяем на ноль. P.S.  
		capacity_ = 1;								 // Если capacity_ == 0 при первом
	}											     // вызове, получится new int[0],
	capacity_ *= 2;									 // а потом memcpy с нулевым 
	int* new_data = new int[capacity_];				 // указателем → segmentation fault.

	// Копируем существующие данные
	std::copy(data_, data_+size_, new_data);  // Замена memcy на copy безопасный способ копирования

	// Освобождаем старую память и обновляем указатель
	delete[] data_;
	data_ = new_data;
}

