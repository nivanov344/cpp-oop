#ifndef _POTROW_
#define _POTROW_
#include "Plant.hpp"
class PotRow {
private:
	Plant** plants;
	bool* spaces;
	unsigned capacity;
	unsigned location;

	void copy(const PotRow&);
	void steal(PotRow&&);
	void cleanup();
public:
	PotRow(const unsigned, const unsigned);
	PotRow(const PotRow&);
	PotRow& operator=(const PotRow&);
	~PotRow();

	PotRow(PotRow&&);
	PotRow& operator=(PotRow&&);

	void insert(const Plant&);
	void remove(int pos);
};

PotRow::PotRow(const unsigned capacity, const unsigned location) {
	plants = new Plant*[capacity];
	this->capacity = capacity;
	this->location = location;
}


#endif