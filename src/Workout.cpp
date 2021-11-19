#include "Workout.h"

Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):id(w_id),name(w_name), price(w_price), type(w_type){};

int Workout::getId() const{
    return this->id;
}
std::string Workout::getName() const{
    return this->name;
}
int Workout::getPrice() const{
    return this->price;
}
WorkoutType Workout::getType() const{
    return this->type;
}

//Workout& Workout::operator=(Workout &other);

// Workout& Workout::operator=(Workout &other){
//     if(this != &other){
//         id = other.getId();
//         name = other.getName();
//         this->price = other.getPrice();
//         this->type = other.getType();
//     }
//     return *this;
// }
bool operator<(const Workout &first,const Workout &second){
    return (first.getPrice() < second.getPrice());
}
bool operator>(const Workout &first,const Workout &second){
    return (first.getPrice() > second.getPrice());
}

// bool Workout::operator<(const Workout &other) const{
//     return (this->getPrice() < other.getPrice());
// }
// bool Workout::operator>(const Workout &other) const{
//     return (this->getPrice() > other.getPrice());
// }