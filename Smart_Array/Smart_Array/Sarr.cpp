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
	if ((index >= size_) or (index < 0)) {
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
	capacity_ *= 2;
	int* new_data = new int[capacity_];

	// Копируем существующие данные
	std::memcpy(new_data, data_, size_ * sizeof(int));

	// Освобождаем старую память и обновляем указатель
	delete[] data_;
	data_ = new_data;
}

