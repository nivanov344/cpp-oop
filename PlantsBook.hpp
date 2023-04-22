#ifndef _PLANTS_BOOK_
#define _PLANTS_BOOK_
#include <cstring>
#include <fstream>
#include "PlantInfo.hpp"
class PlantsBook {
private:
	char bookName[129];
	PlantInfo* plants;
	unsigned length;

	void open(const char*);
	void insert(const PlantInfo&, const unsigned);
	void sort(int, int);
	void copy(const PlantsBook&);
	void steal(PlantsBook&&);
	void cleanup();
public:
	PlantsBook(const PlantInfo*, const unsigned, const char*);
	PlantsBook(const char*);
	PlantsBook(const PlantsBook&);
	PlantsBook& operator=(const PlantsBook&);
	PlantsBook(PlantsBook&&);
	PlantsBook& operator=(PlantsBook&&);

	void add(const PlantInfo&);
	void add(const char*, const int, const unsigned);
	void save();

	friend std::ostream& operator<<(std::ostream& os, const PlantsBook& obj);
	friend std::istream& operator>>(std::istream& is, PlantsBook& obj);
};

PlantsBook::PlantsBook(const PlantInfo* _plants, const unsigned _length, const char* _bookName) {
	plants = new PlantInfo [_length];
	for (int i = 0; i < _length; ++i) {
		plants[i] = _plants[i];
	}
	length = _length;
	strcpy(bookName, _bookName);
	sort(0, length - 1);
}

PlantsBook::PlantsBook(const char* filename) {
	open(filename);
}

PlantsBook::PlantsBook(const PlantsBook& other) {
	copy(other);
}

PlantsBook& PlantsBook::operator=(const PlantsBook& other) {
	if (this != &other) {
		cleanup();
		copy(other);
	}
	return *this;
}

PlantsBook::PlantsBook(PlantsBook&& other) {
	steal((PlantsBook&&)other);
}

PlantsBook& PlantsBook::operator=(PlantsBook&& other) {
	if (this != &other) {
		cleanup();
		steal((PlantsBook&&)other);
	}
	return *this;
}

void PlantsBook::add(const char* type, int preferredLocation = 1, unsigned wateringFrequency = 3) {
	unsigned ind = 0;
	while (strcmp(type, plants[ind].getType()) >= 0 && ind < length) {
		if (strcmp(type, plants[ind].getType()) == 0) {
			throw std::invalid_argument("Plant already exists!");
		}
		++ind;
	}
	PlantInfo obj{ type, preferredLocation, wateringFrequency };
	insert(obj, ind);
}

void PlantsBook::open(const char* filename) {
	strcpy(bookName, filename);
	std::ifstream fin(bookName);
	if (!fin) {
		throw std::invalid_argument("Could not open file for reading!");
	}
	fin >> *this;
}

void PlantsBook::save() {
	std::ofstream fout(bookName);
	fout << length << std::endl << *this;
}

void PlantsBook::insert(const PlantInfo& obj, const unsigned pos) {
	PlantInfo* newArr = new PlantInfo[length + 1];
	for (int i = 0; i < pos; ++i) {
		newArr[i] = plants[i];
	}
	newArr[pos] = obj;
	for (int i = pos + 1; i < length + 1; ++i) {
		newArr[i] = plants[i - 1];
	}
	delete[] plants;
	plants = newArr;
	++length;
}

void PlantsBook::sort(int left, int right) {
	int i, j;
	char* x;
	PlantInfo temp;

	i = left;
	j = right;
	x = plants[(left + right) / 2].getType();

	do {
		while ((strcmp(plants[i].getType(), x) < 0) && (i < right)) {
			i++;
		}
		while ((strcmp(plants[j].getType(), x) > 0) && (j > left)) {
			j--;
		}
		if (i <= j) {
			temp = plants[i];
			plants[i] = plants[j];
			plants[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) {
		sort( left, j);
	}
	if (i < right) {
		sort( i, right);
	}
}

void PlantsBook::copy(const PlantsBook& other) {
	strcpy(bookName, other.bookName);
	plants = new PlantInfo [other.length];
	for (int i = 0; i < other.length; ++i) {
		plants[i] = other.plants[i];
	}
	length = other.length;
}

void PlantsBook::steal(PlantsBook&& other) {
	strcpy(bookName, other.bookName);
	plants = other.plants;
	length = other.length;

	other.plants = nullptr;
}

void PlantsBook::cleanup() {
	delete[] plants;
}

std::ostream& operator<<(std::ostream& os, const PlantsBook& obj) {
	//os << obj.bookName << std::endl << obj.length << std::endl;
	for (int i = 0; i < obj.length; ++i) {
		os << obj.plants[i] << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, PlantsBook& obj) {
	obj.cleanup();
	is >> obj.length;
	obj.plants = new PlantInfo[obj.length];
	for (int i = 0; i < obj.length; ++i) {
		is >> obj.plants[i];
	}
	obj.sort(0, obj.length - 1);
	return is;
}
#endif