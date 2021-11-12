#include "Action.h"

//class:BaseAction
//TODO: check for diffrent initalization in constructor
BaseAction::BaseAction():errorMsg(""){};
ActionStatus BaseAction::getStatus() const{
    return status;
};
void BaseAction::complete(){
    status = COMPLETED;
}
void BaseAction::error(std::string errorMsg){
    std::cout<< errorMsg << endl;
};
std::string BaseAction::getErrorMsg() const{
    return errorMsg;
};

//class:openTrainer

// OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id){

// };