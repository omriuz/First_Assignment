#include "Action.h"
#include <iostream>
#include "Studio.h"


////
//
//class:BaseAction
//TODO: check for diffrent initalization in constructor
BaseAction::BaseAction(){};
ActionStatus BaseAction::getStatus() const{
    return status;
};
void BaseAction::complete(){
    status = COMPLETED;
}
//TODO: need to complete method implenation
void BaseAction::error(std::string errorMsg){
};
std::string BaseAction::getErrorMsg() const{
    return errorMsg;
};

// class:openTrainer

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id),customers(customersList){
        BaseAction::error("Workout session does not exist or is already open.");
        // we need to make sure if the customers can be init in the init list?
        // for(Customer* cus_1 : customersList){
        //     Customer* x = cus_1;
        //     customers.push_back(x);
        // }
};
void OpenTrainer::act( Studio& studio){
    Trainer* t = studio.getTrainer(trainerId);
    if (t==NULL||t->isOpen())
        std::cout<<BaseAction::getErrorMsg()<<endl;
    else {
        t->openTrainer();
        for(Customer* c : customers){
            t->addCustomer(c);
        }

    }
    //need to delete pointer??
    delete t;
};
std::string OpenTrainer::toString() const{};
