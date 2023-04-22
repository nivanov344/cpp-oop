#ifndef _PLANT_
#define _PLANT_
#include <cstring>
#include <string>
#include<fstream>
#include "PlantInfo.hpp"
class Plant {
private:
	char* type;
	int location;
	int wateringFrequency;

	void copy(const Plant&);
	void steal(Plant&&);
	void cleanup();
public:
	Plant(const PlantInfo&, const int);
	Plant(const Plant&);
	Plant& operator=(const Plant&);
	~Plant();

	Plant(Plant&&);
	Plant& operator=(Plant&&);

	char* getType() {
		return type;
	}
	int getLocation() {
		return location;
	}
	int getWateringFrequency() {
		return wateringFrequency;
	}

	friend std::ostream& operator<<(std::ostream& os, const Plant& obj);
	friend std::istream& operator>>(std::istream& is, Plant& obj);
};

Plant::Plant(const PlantInfo& plant, const int location = -1) {
	type = new char[strlen(plant.getType()) + 1];
	strcpy(type, plant.getType());
	this->location = location;
	wateringFrequency = plant.getWateringFrequency();
	if (location == -1) {
		wateringFrequency = -1;
	}
}

Plant::Plant(const Plant& other) {
	copy(other);
}

Plant& Plant::operator=(const Plant& other) {
	if (this != &other) {
		cleanup();
		copy(other);
	}
	return *this;
}

Plant::~Plant() {
	cleanup();
}

Plant::Plant(Plant&& other) {
	steal((Plant&&)other);
}

Plant& Plant::operator=(Plant&& other) {
	if (this != &other) {
		cleanup();
		steal((Plant&&)other);
	}
	return *this;
}

void Plant::copy(const Plant& other) {
	type = new char[strlen(other.type) + 1];
	strcpy(type, other.type);
	location = other.location;
	wateringFrequency = other.wateringFrequency;
}

void Plant::steal(Plant&& other) {
	type = other.type;
	location = other.location;
	wateringFrequency = other.wateringFrequency;

	other.type = nullptr;
}

void Plant::cleanup() {
	delete[] type;
}

std::ostream& operator<<(std::ostream& os, const Plant& obj) {
	os << obj.type << " " << obj.location << " " << obj.wateringFrequency;
	return os;
}

std::istream& operator>>(std::istream& is, Plant& obj) {
	std::string t;
	is >> t >> obj.location >> obj.wateringFrequency;
	obj.cleanup();
	obj.type = new char[t.length() + 1];
	strcpy(obj.type, t.c_str());
	return is;
}
#endif