#include "Trainer.h"
#include <iostream>

using namespace std;
Trainer :: Trainer (int t_capacity):capacity(t_capacity),open(false){};
int Trainer :: getCapacity() const{
    return this->capacity;
};
void Trainer::addCustomer(Customer* customer){
    customersList.push_back(customer);
};
void Trainer::removeCustomer(int id){
    bool not_earsed = true;
    for(int i = 0; i<customersList.size()&not_earsed;i++){
        if(customersList[i]->getId()==id){
            customersList.erase(customersList.begin()+i);
            not_earsed = true;
        }
    }
    if(!not_earsed){
        std::cout<< " customer not found"<<endl;}
};
Customer* Trainer::getCustomer(int id){
    Customer* c;
    bool found = false;
    for(int i = 0; i<customersList.size()&!found;i++){
        if(customersList[i]->getId()==id){
            c = customersList[i];
            found = true;
        }
    }
    if(!found){
        delete c;
        std::cout<< "customer not found"<<endl;
    }
};
std::vector<Customer*>& Trainer::getCustomers(){
    return customersList;
};
std::vector<OrderPair>& Trainer::getOrders(){
    return orderList;
};
void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){};
void Trainer::openTrainer(){
    open = true;
};
void Trainer::closeTrainer(){
    open = false;
};
int Trainer::getSalary(){
    //need to add salary
};
bool Trainer::isOpen(){
    return open;
};