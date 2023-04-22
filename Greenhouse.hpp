#ifndef _GREENHOUSE_
#define _GREENHOUSE_
#include "PotRow.hpp"
#include "PlantsBook.hpp"
#include "PlantInfo.hpp"
#include "Plant.hpp"
class Greenhouse {
private:
	PlantsBook catalog;
	PotRow rows[3];

	void copy(const Greenhouse&);
	void steal(Greenhouse&&);
	void cleanup();
public:
	Greenhouse(PlantsBook _catalog, int shadyCap, int neutralCap, int sunnyCap) : catalog{ _catalog } {

	}
};
#endif