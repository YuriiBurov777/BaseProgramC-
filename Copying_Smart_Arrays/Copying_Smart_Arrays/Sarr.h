#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

class smart_array {

public:

	// Конструктор, принимающий начальную емкость
	/*   explicit запрещает неявное преобразование(защита от smart_array arr = 5;)
		 Список инициализации : size_(0), capacity_(initial_capacity), count_(0) инициализирует поля ДО тела конструктора
		 Проверка initial_capacity == 0 - защита от некорректных данных
		 new int[capacity_] - выделение памяти под массив*/

	explicit smart_array(size_t initial_capacity) : size_(0), capacity_(initial_capacity) {
		if (initial_capacity == 0) {
			throw std::invalid_argument("Вместимость должна быть больше, чем 0");
		}
		data_ = new int[capacity_];
	}

	// Деструктор
	~smart_array() {
		delete[] data_;
	}

	// Функция добавления нового элемента
	/*   Процесс расширения :
		 Проверка - если size_ >= capacity_, значит массив заполнен
		 Увеличение емкости - обычно в 2 раза(оптимально для амортизированной сложности O(1))
		 Выделение новой памяти - new int[capacity_]
		 Копирование данных - memcpy быстрее поэлементного копирования
		 Освобождение старой памяти - delete[] data_
		 Обновление указателя - data_ = new_data*/

	void add_element(int element);

	//Оператор присваивания. Копирвание массива в массив.
	smart_array& operator=(const smart_array& other);

	// Функция получения элемента по индексу
	int get_element(size_t index) const;

	// Получение текущего размера (количество добавленных элементов)
	size_t get_size() const;

	// Получение текущей емкости
	size_t get_capacity() const;

	// Получение общего количества добавленных элементов
	size_t get_count() const;

	// Вывод масисва в консоль
	void print() const;

private:

	int* data_;
	size_t size_;         //текущее количество элементов
	size_t capacity_;     //текущая емкость массива

	// Увеличение емкости массива
	void resize();
};