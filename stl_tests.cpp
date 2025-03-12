#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <queue>
#include <algorithm>

class Car {

    std::string m_model;
    int m_prod_year;

public:

    Car(std::string model, int year) :
            m_model(model), m_prod_year(year) { }

    std::string get_model() {
        return m_model;
    }
    
    int get_production_year() {
        return m_prod_year;
    }

    static bool comparator(const Car& left, const Car& right){
        return left.m_prod_year < right.m_prod_year; 
    }

    friend std::ostream& operator<<(std::ostream &os, Car c)
    {
        os << "\tModel: " << c.m_model << "\n";
        os << "\tYear: " << c.m_prod_year;
        return os;
    }

    // void print_my_cars(const Car& my_cars){
    //     for(auto &i : my_cars){
    //         std::cout << i << std::endl;
    //     }
    // }
};

int main(){
    std::vector<Car> my_cars {
        {"Toyota",2002},
        {"UAZ",1970},
        {"BMW",1998},
        {"Mersedes",1995},
        {"Honda",2001}
    };

    auto print = [](const Car& n) {std::cout << n << std::endl; };

    sort(begin(my_cars),end(my_cars), [](Car &a, Car &b)->bool {
        return a.get_model() < b.get_model();
    });
    //default alfabetical sort by names
    std::cout << "Sorted by Model:\n";
    std::for_each(my_cars.cbegin(),my_cars.cend(),print);
    // print_my_cars(my_cars);

    std::cout << "Sorted by year:\n";
    sort(begin(my_cars),end(my_cars), Car::comparator);
    //sotring by my comparator for production year
    std::for_each(my_cars.cbegin(),my_cars.cend(),print);
    // print_my_cars(my_cars);


}