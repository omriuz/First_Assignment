#include "Trainer.h"
#include <iostream>

using namespace std;
//constructor:
Trainer :: Trainer (int t_capacity):salary(0),capacity(t_capacity),open(false),customersList(),orderList(){};
//copy constructor:
Trainer :: Trainer(const Trainer &other):salary(other.salary),capacity(other.capacity),open(other.open),customersList(),orderList(){
    copy(other);
}
//copy assignment operator:
Trainer&  Trainer::operator=(const Trainer &other){
    if(this == &other)
        return *this;
    clear();
    open = other.open;
    capacity = other.capacity;
    salary = other.salary;
    copy(other);
    return *this;

}
//destructor:
Trainer :: ~Trainer(){
    clear();
}
//Move constructor:
Trainer::Trainer(Trainer && other):salary(other.salary),capacity(other.capacity),open(other.open),customersList(),orderList(){
    move_copy(other);
}
//Move Assignemnt:
Trainer& Trainer::operator=(Trainer &&other){
    if(this != &other){
        clear();
        capacity = other.capacity;
        open = other.open;
        salary = other.salary;
        move_copy(other);
    }
    return *this;
}
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
    for(int i = 0; (i<length) & (!erased);i++){
        if(customersList[i]->getId()==id){
            customersList.erase(customersList.begin()+i);
            erased = true;
        }
    }
    if(erased){
        length = orderList.size();
        int sum_of_orders = 0;
            for(int i = 0; i < length;i++){
            if(orderList[i].first == id){
                //erasing is impossible so were chaging the value of customer_id to -1 instead
                orderList[i].first=-1;
                sum_of_orders = sum_of_orders + orderList[i].second.getPrice();
            }
        }
        dec_salary(sum_of_orders);
    }
   else
        std::cout<< " customer not found"<<endl;
};
Customer* Trainer::getCustomer(int id){
    Customer* c;
    bool found = false;
    for(size_t i = 0; (i<customersList.size())&(!found);i++){
        if(customersList[i]->getId()==id){
            c = customersList[i];
            found = true;
        }
    }
    if(!found){
        std::cout<< "customer not found"<<endl;
    }
    return c;
};
std::vector<Customer*>& Trainer::getCustomers(){
    return customersList;
};
std::vector<OrderPair>& Trainer::getOrders(){
    return orderList;
};
void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){
    int sum_of_orders = 0;
    for(int workout_id : workout_ids){
        //using the fact that workout_id is an index in workout_options
        OrderPair pair(customer_id,workout_options[workout_id]);
        orderList.push_back(pair);
        sum_of_orders = sum_of_orders + pair.second.getPrice();
    }
    inc_salary(sum_of_orders);
};
void Trainer::openTrainer(){
    open = true;
};
void Trainer::closeTrainer(){
    for(Customer *customer : customersList){
        delete customer;
    }
    customersList.clear();
    open = false;
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
    return ((int)customersList.size()>=getCapacity());
}
bool Trainer::isEmpty(){
    return customersList.size()==0;
}
void Trainer::dec_salary(int amount){
    salary = salary - amount;
}
void Trainer::inc_salary(int amount){

    salary = salary + amount;
}
void Trainer::copy(const Trainer &other){
    // deep copy customer list:
    for(Customer *c : other.customersList){
        Customer *customer = c->clone();
        customersList.push_back(customer);
    }
    //deep copy order list:
    for(OrderPair pair : other.orderList){
        OrderPair p(pair.first,pair.second);
        this->orderList.push_back(p);
    }
}
void Trainer::clear(){
    for(Customer *c:customersList)
        delete c;
    customersList.clear();
    orderList.clear();
}
void Trainer::move_copy(Trainer &other){
    for(Customer *c:other.customersList)
        customersList.push_back(c);
    for(OrderPair pair:other.orderList)
        orderList.push_back(pair);
    other.orderList.clear();
    other.customersList.clear();

}