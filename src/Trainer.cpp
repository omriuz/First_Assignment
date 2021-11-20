#include "Trainer.h"
#include <iostream>

using namespace std;
Trainer :: Trainer (int t_capacity):salary(0),capacity(t_capacity),open(false){};
int Trainer :: getCapacity() const{
    return capacity;
};
void Trainer::addCustomer(Customer* customer){
    if(!isFull())
        customersList.push_back(customer);
    //i think we need to update the order list but im not sure
    // how were gonna do that
    //because we need a ref to studio to get the workout options
    // this->order(customer->getId(),customer->order(Workout_options),Workout_options);
};
void Trainer::removeCustomer(int id){
    //TODO: we need to delete the customer from the heap??
    bool erased = false;
    int length = customersList.size();
    for(int i = 0; i<length & !erased;i++){
        if(customersList[i]->getId()==id){
            customersList.erase(customersList.begin()+i);
            erased = true;
        }
    }
    length = orderList.size();
    erased = false;
        for(int i = 0; i < length && !erased;i++){
        if(orderList[i].first == id){
            //erasing is impossible so were chaging the value of customer_id to -1 instead
            orderList[i].first=-1;
            erased = true;
        }
    }
    if(!erased){
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
void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){
    for(int workout_id : workout_ids){
        //using the fact that workout_id is an index in workout_options
        OrderPair pair(customer_id,workout_options[workout_id]);
        orderList.push_back(pair);
    }
};
void Trainer::openTrainer(){
    open = true;
};
void Trainer::closeTrainer(){
    open = false;
    updateSalary();
    //check in forum if we want to print the salary to the screen here or in the action
};
int Trainer::getSalary(){
    return salary;
};
bool Trainer::isOpen(){

    return open;
};
bool Trainer::isCustomerOfTrainer(int customerId){
        for(Customer* c :customersList){
        if(c->getId() == customerId)
            return true;
    }
    return false;
}
bool Trainer::isFull(){
    return customersList.size()<getCapacity();
}
bool Trainer::isEmpty(){
    return customersList.size()==0;
}
void Trainer::updateSalary(){
    int sum_of_orders = 0;
    for(OrderPair pair : orderList){
        if(pair.first != -1)
            sum_of_orders = sum_of_orders + pair.second.getPrice();
    }
    salary = salary + sum_of_orders;
}