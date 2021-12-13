#include "container_OO_design.h"
#include <iostream>

using namespace std;

int main() {

    srand(time(NULL)); // make sure every time the content of random number can generate differently

//// Vector ////
    PolyContainer_vector PC_vect;
    Area_Calculation *AC_vect = &PC_vect;

    PC_vect.Gen_Rect_vector(Rect_num, max_range_per_rect);

    int total_area_vect = AC_vect->total_rect_area();
    cout << "Vector total area = " << total_area_vect << endl;
    int overlapping_area_vect = AC_vect->overlapping_rect_area();
    cout << "Vector overlapping area = " << overlapping_area_vect <<endl;
    int total_covered_area_vect = AC_vect->total_rect_covered_area();
    cout << "Vector total covered area = " << total_covered_area_vect << endl;

//// List ////
    PolyContainer_list PC_list;
    Area_Calculation *AC_list = &PC_list;

    PC_list.Gen_Rect_list(Rect_num, max_range_per_rect);

    int total_area_list = AC_list->total_rect_area();
    cout << "List total area = " << total_area_list << endl;
    int overlapping_area_list = AC_list->overlapping_rect_area();
    cout << "List overlapping area = " << overlapping_area_list  << endl;
    int total_covered_area_list = AC_list->total_rect_covered_area();
    cout << "List total covered area = " << total_covered_area_list << endl;

    return 0;
}
