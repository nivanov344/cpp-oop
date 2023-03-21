#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_
class DynamicArray {
private:
	int* array;
	unsigned capacity;
	unsigned count;

	void cleanup();
	void copy(const DynamicArray&);
	void steal(DynamicArray&&);
	void allocate(unsigned);
	void checkCapacity();

public:
	DynamicArray(unsigned);
	DynamicArray(unsigned, int);
	DynamicArray(const DynamicArray&);
	DynamicArray& operator=(const DynamicArray&);
	DynamicArray(DynamicArray&&);
	DynamicArray& operator=(DynamicArray&&);
	~DynamicArray();
	void append(int);
	void insert(int, unsigned);
	int pop();
	void remove(unsigned);
	void clear();
	bool isEmpty();
	int size();
	int get(unsigned);
	void set(int, unsigned);
	int find(int);
	
};

DynamicArray::DynamicArray(unsigned initSize = 100) {
	int* arr = new int[initSize];
	array = arr;
	capacity = initSize;
	count = 0;
	//std::cout << "Default constructor" << count << " " << capacity << std::endl;
}

DynamicArray::DynamicArray(unsigned initSize, int init) {
	int* arr = new int[initSize] {init};
	array = arr;
	capacity = initSize;
	count = initSize;
	/*for (int i = 0; i < initSize; ++i) {
		array[i] = init;
	}*/
	//std::cout << "Param constructor" << count << " " << capacity << std::endl;
}

DynamicArray::DynamicArray(const DynamicArray& other) {
	//cleanup();
	copy(other);
	//std::cout << "Copy constructor " << count << " " << capacity << std::endl;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
	if (this != &other) {
		cleanup();
		copy(other);
	}
	return *this;
	//std::cout << "Copy operator " << count << " " << capacity << std::endl;
}

DynamicArray::DynamicArray(DynamicArray&& other) {
	steal((DynamicArray&&)other);
	//std::cout << "Move constructor " << count << " " << capacity << std::endl;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other) {
	if (this != &other) {
		cleanup();
		steal((DynamicArray&&)other);
	}
	//std::cout << "Move operator " << count << " " << capacity << std::endl;
	return *this;
}

DynamicArray::~DynamicArray() {
	cleanup();
	//std::cout << "Destructor" << std::endl;
}

void DynamicArray::append(int num) {
	checkCapacity();
	array[count] = num;
	++count;
}

void DynamicArray::insert(int num, unsigned pos) {
	if (pos < count) {
		checkCapacity();
		++count;
		for (int i = count - 1; i > pos; --i) {
			array[i] = array[i - 1];
		}
		array[pos] = num;
	}
}

int DynamicArray::pop() {
	--count;
	return array[count];
}

void DynamicArray::remove(unsigned pos) {
	for (int i = pos; i < count - 1; ++i) {
		array[i] = array[i + 1];
	}
	--count;
}

int DynamicArray::get(unsigned pos) {
	if (pos < count) {
		return array[pos];
	}
}

void DynamicArray::cleanup() {
	delete[] array;
}

void DynamicArray::copy(const DynamicArray& other) {
	if (other.capacity > capacity) {
		allocate(other.capacity);
	}
	for (int i = 0; i < other.count; ++i) {
		array[i] = other.array[i];
	}
	capacity = other.capacity;
	count = other.count;
}

void DynamicArray::steal(DynamicArray&& other) {
	array = other.array;
	capacity = other.capacity;
	count = other.count;

	other.array = nullptr;
}

void DynamicArray::allocate(unsigned size) {
	array = new int[size];
}

void DynamicArray::checkCapacity() {
	assert(count <= capacity);
	if (count == capacity) {
		int* old = array;
		allocate(2 * capacity);
		for (int i = 0; i < count; ++i) {
			array[i] = old[i];
		}
		capacity *= 2;
		delete[] old;
	}
}
#endif
