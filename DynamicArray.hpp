#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_
class DynamicArray {
private:
	int* array;
	int capacity;
	int count;

	void cleanup();
	void copy(const DynamicArray&);

public:
	DynamicArray(int, int);
	DynamicArray(const DynamicArray&);
	DynamicArray& operator=(const DynamicArray&);
	DynamicArray(DynamicArray&&);
	DynamicArray& operator=(DynamicArray&&);
	~DynamicArray();
	void append(int);
	void insert(int, int );
	void pop();
	void remove(int);
	void clear();
	bool isEmpty();
	int size();
	int get(int);
	void set(int, int);
	int find(int);
};

DynamicArray::DynamicArray(int initSize = 100, int init = 0) {
	int* arr = new int[initSize] {init};
	array = arr;
	capacity = initSize;
	count = 0;
	if (init != 0) {
		count = initSize;
	}
	std::cout << "Default " << count << " " << capacity << std::endl;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
	copy(other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	if (this != &other) {
		cleanup();
		copy(other);
	}
	return *this;
}

DynamicArray::DynamicArray(DynamicArray&& other) {
	
}

DynamicArray::~DynamicArray() {
	delete[] array;
	std::cout << "destructor" << std::endl;
}

void DynamicArray::cleanup() {
	delete[] array;
}

void DynamicArray::copy(const DynamicArray& other) {
	if (other.capacity > capacity) {
		cleanup();
		int* newArr = new int[other.capacity];
		array = newArr;
	}
	for (int i = 0; i < other.count; ++i) {
		array[i] = other.array[i];
	}
	capacity = other.capacity;
	count = other.count;
}
#endif
