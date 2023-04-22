#include <iostream>
#include "PlantInfo.hpp"
#include "PlantsBook.hpp"
#include "Plant.hpp"
int main()
{
    PlantInfo pi1("z", -1, 3);
    PlantInfo pi2("a", 1, 8);
    PlantInfo pi3("b", -1, 69);
    
    Plant p1(pi1, 18);
    std::cout << p1;
    //PlantInfo* plants = new PlantInfo [3];
    //plants[0] = pi1;
    //plants[1] = pi2;
    //plants[2] = pi3;

    //PlantsBook book("another_test.txt");
    //std::cout << book << std::endl;
    //book.add("doo", 69, 5);
    //
    //book.save();
    ///*std::cin >> book;*/
    ////std::cout << book;
    //delete[] plants;
    return 0;
}
