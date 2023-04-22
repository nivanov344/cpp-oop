#ifndef _PLANT_INFO_
#define _PLANT_INFO_
#include <cstring>
#include <string>
#include <fstream>
#pragma warning(disable : 4996)
class PlantInfo {
private:
	char* type;
	int preferredLocation;
	unsigned wateringFrequency;

	void copy(const PlantInfo&);
	void steal(PlantInfo&&);
	void cleanup();
public:
	PlantInfo(const char*, const int, const unsigned);
	PlantInfo(const PlantInfo&);
	PlantInfo(PlantInfo&&);
	PlantInfo& operator=(const PlantInfo&);
	PlantInfo& operator=(PlantInfo&&);
	~PlantInfo();

	char* getType() const{
		return type;
	}

	unsigned getWateringFrequency() const{
		return wateringFrequency;
	}

	friend std::ostream& operator<<(std::ostream& os, PlantInfo& obj);
	friend std::istream& operator>>(std::istream& is, PlantInfo& obj);
};

PlantInfo::PlantInfo(const char* _type = "", const int _preferredLocation = 0, const unsigned _wateringFrequency = 3) {
	type = new char[strlen(_type) + 1];
	strcpy(type, _type);
	preferredLocation = _preferredLocation;
	wateringFrequency = _wateringFrequency;
}

PlantInfo::PlantInfo(const PlantInfo& other) {
	copy(other);
}

PlantInfo::PlantInfo(PlantInfo&& other) {
	steal((PlantInfo&&)other);
}

PlantInfo& PlantInfo::operator=(const PlantInfo& other) {
	if (this != &other) {
		cleanup();
		copy(other);
	}
	return *this;
}

PlantInfo& PlantInfo::operator=(PlantInfo&& other) {
	if (this != &other) {
		cleanup();
		steal((PlantInfo&&)other);
	}
	return *this;
}

PlantInfo::~PlantInfo() {
	cleanup();
}

void PlantInfo::copy(const PlantInfo& other) {
	type = new char[strlen(other.type) + 1];
	strcpy(type, other.type);
	preferredLocation = other.preferredLocation;
	wateringFrequency = other.wateringFrequency;
}

void PlantInfo::steal(PlantInfo&& other) {
	type = other.type;
	preferredLocation = other.preferredLocation;
	wateringFrequency = other.wateringFrequency;

	other.type = nullptr;
}

void PlantInfo::cleanup() {
	delete[] type;
}

std::ostream& operator<<(std::ostream& os, PlantInfo& obj) {
	os << obj.type << " " << obj.preferredLocation << " " << obj.wateringFrequency;
	return os;
}

std::istream& operator>>(std::istream& is, PlantInfo& obj) {
	std::string t;
	is >> t >> obj.preferredLocation >> obj.wateringFrequency;
	obj.cleanup();
	obj.type = new char[t.length() + 1];
	strcpy(obj.type, t.c_str());
	return is;
}
#endif