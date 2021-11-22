#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"

typedef std::pair<int, Workout> OrderPair;
/*
in the getSalary:
we need to sum workouts in the orderList
*/
class Trainer{
public:
    //constructors:
    Trainer(int t_capacity);
    //copy constructor:
    Trainer(const Trainer &other);
    //copy assignment operator:
    Trainer & operator=(const Trainer &other);
    //destructor:
    ~Trainer();
    //move constructor:
    //TODO: ???
    //move assignment:
    //TODO: ???
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();
    bool isCustomerOfTrainer(int customerId);
    bool isFull();
    bool isEmpty();
    void dec_salary(int amount);
    void inc_salary(int amount);

private:
    void copy(const Trainer &other) const;
    void clear();
    int salary;
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif