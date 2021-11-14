#include "Trainer.h"
#include <iostream>

using namespace std;
Trainer :: Trainer (int t_capacity):capacity(t_capacity),open(false){};
int Trainer :: getCapacity() const{
    return this->capacity;
};
void Trainer::addCustomer(Customer* customer){
    customersList.push_back(customer);
    //i think we need to update the order list but im not sure
    // how were gonna do that
    //because we need a ref to studio to get the workout options
    // this->order(customer->getId(),customer->order(Workout_options),Workout_options);
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
    // i think we need to delete this customer orders from the orders list
    // but i'm waiting until we solve the problem in the add customer method
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
    //need to compute salary
};
bool Trainer::isOpen(){
    return open;
};