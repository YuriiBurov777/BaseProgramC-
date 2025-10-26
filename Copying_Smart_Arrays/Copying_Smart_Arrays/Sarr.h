#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

class smart_array {

public:

	// �����������, ����������� ��������� �������
	/*   explicit ��������� ������� ��������������(������ �� smart_array arr = 5;)
		 ������ ������������� : size_(0), capacity_(initial_capacity), count_(0) �������������� ���� �� ���� ������������
		 �������� initial_capacity == 0 - ������ �� ������������ ������
		 new int[capacity_] - ��������� ������ ��� ������*/

	explicit smart_array(size_t initial_capacity) : size_(0), capacity_(initial_capacity) {
		if (initial_capacity == 0) {
			throw std::invalid_argument("����������� ������ ���� ������, ��� 0");
		}
		data_ = new int[capacity_];
	}

	// ����������
	~smart_array() {
		delete[] data_;
	}

	// ������� ���������� ������ ��������
	/*   ������� ���������� :
		 �������� - ���� size_ >= capacity_, ������ ������ ��������
		 ���������� ������� - ������ � 2 ����(���������� ��� ���������������� ��������� O(1))
		 ��������� ����� ������ - new int[capacity_]
		 ����������� ������ - memcpy ������� ������������� �����������
		 ������������ ������ ������ - delete[] data_
		 ���������� ��������� - data_ = new_data*/

	void add_element(int element);

	//�������� ������������. ���������� ������� � ������.
	smart_array& operator=(const smart_array& other);

	// ������� ��������� �������� �� �������
	int get_element(size_t index) const;

	// ��������� �������� ������� (���������� ����������� ���������)
	size_t get_size() const;

	// ��������� ������� �������
	size_t get_capacity() const;

	// ��������� ������ ���������� ����������� ���������
	size_t get_count() const;

	// ����� ������� � �������
	void print() const;

private:

	int* data_;
	size_t size_;         //������� ���������� ���������
	size_t capacity_;     //������� ������� �������

	// ���������� ������� �������
	void resize();
};