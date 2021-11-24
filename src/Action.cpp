#include "Action.h"
#include <iostream>
#include "Studio.h"

//class:BaseAction
BaseAction::BaseAction():errorMsg(""),status(COMPLETED){};
ActionStatus BaseAction::getStatus() const{
    return status;
};
void BaseAction::complete(){
    status = COMPLETED;
}
//TODO: need to complete method implenation
void BaseAction::error(std::string errorMsg){
    status = ERROR;
    this->errorMsg=errorMsg;
}
std::string BaseAction::getErrorMsg() const{
    return errorMsg;
}
BaseAction::~BaseAction()=default;

void BaseAction::set_status(ActionStatus status){
    this->status = status;
}
void BaseAction::set_error_msg(string errormsg){
    this->errorMsg = errormsg;
}
// class:openTrainer

OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id),customers(customersList),customers_descriptions(""){
};
void OpenTrainer::act( Studio& studio){
    Trainer* t = studio.getTrainer(trainerId);
    if (t==nullptr||t->isOpen()){
        BaseAction::error("Workout session does not exist or is already open.");
        std::cout<<BaseAction::getErrorMsg()<<endl;
        for(Customer* c :customers)
            delete c;
        customers.clear();
        }
        
    else {
        t->openTrainer();
        size_t length = customers.size(),capacity = t->getCapacity();
         for (size_t i = 0;i < length; i++)
         {
             //only add customer if there is space
             if(i<capacity)
                t->addCustomer(customers[i]);
            //else delete the customer to avoid memory leak
            else{
                delete customers[i];
                customers.erase(customers.begin()+i);
            }
         }
         complete();
    }
    for(Customer *c :customers){
        customers_descriptions+=c->toString() + " ";
    }
    
    studio.log_action(this);
}
std::string OpenTrainer::toString() const{
    string s = "open " + std::to_string(trainerId) + " " + customers_descriptions;
    string action_status = getStatus()==COMPLETED ? "Completed" : getErrorMsg();
    s = s + " " + action_status;
    return s;
}

OpenTrainer* OpenTrainer::clone(){
    OpenTrainer *t = new OpenTrainer(trainerId,customers);
    t->set_status(this->getStatus());
    t->set_error_msg(this->getErrorMsg());
    t->set_customers_descriptions(customers_descriptions);
    return t;
}
OpenTrainer::~OpenTrainer() = default;

void OpenTrainer::set_customers_descriptions(string Customers_descirption){
    this->customers_descriptions = Customers_descirption;
}

// class:Order


Order::Order(int id):trainerId(id){};
void Order::act(Studio &studio){
    Trainer* t = studio.getTrainer(trainerId);
    if(t==nullptr){
        BaseAction::error("Trainer does not exist or is not open");
        std::cout<< BaseAction::getErrorMsg()<<endl;
    }
    else{
        std::vector<Workout>& Workout_options= studio.getWorkoutOptions();
        std::vector <Customer*>& customers = t->getCustomers();
        for(Customer* c : customers){
            vector<int> orders = c->order(Workout_options);
            t->order(c->getId(),orders,Workout_options);
            string customer_name = c->getName();
            for(int order : orders){
            string workout_name =  Workout_options[order].getName();
            std::cout<< customer_name << " Is Doing " << workout_name<<endl;
            } 
        }
        complete();
    }
        studio.log_action(this);
    }

//keeping implenation for the actions log
std::string Order::toString() const{
    string s = "order " + std::to_string(trainerId);
    string action_status = getStatus()==COMPLETED ? "Completed" : getErrorMsg();
    s = s + " " + action_status;
    return s;
}
Order* Order::clone(){
    Order *action = new Order(trainerId);
    action->set_status(this->getStatus());
    action->set_error_msg(this->getErrorMsg());
    return (action);
}
Order::~Order()=default;

// class MoveCustomer:

MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src),dstTrainer(dst),id(customerId){};
void MoveCustomer::act(Studio &studio){
    bool valid = true;
    //check if 1.src or dst dont exist or closed,
    //2.customer don't belong to src tranier
    // 3.dst trainer is full
    Trainer* dst = studio.getTrainer(dstTrainer);
    Trainer* src = studio.getTrainer(srcTrainer);
    if(dst==NULL || !dst->isOpen() || src==NULL || !src->isOpen()||!src->isCustomerOfTrainer(id)
    ||dst->isFull())
        valid = false;
    if(!valid){
        BaseAction::error("Cannot move customer");
        std::cout<< BaseAction::getErrorMsg()<<endl;
    }
    else{
    Customer* customer = src->getCustomer(id);
    //add the customer to the dst trainer
    dst->addCustomer(customer);
    //add the customer orders to the new trainer
    vector<Workout>& workout_options=studio.getWorkoutOptions();
    vector<int> workouts_ids = customer->order(workout_options);
    dst->order(id,workouts_ids,workout_options);
    //remove the customer from the src trainer
    src->removeCustomer(id);
    //check if the src trainer is empty
    if(src->isEmpty())
        src->closeTrainer();
    complete();
    }
    studio.log_action(this);
}

std::string MoveCustomer::toString() const{
    string s = "move " + std::to_string(srcTrainer) + " " + std::to_string(dstTrainer);
    s = s + " " + std::to_string(id);
    string action_status = getStatus()==COMPLETED ? "Completed" : getErrorMsg();
    s = s + " " + action_status;
    return s;
}
MoveCustomer* MoveCustomer::clone(){
    MoveCustomer *action = new MoveCustomer(srcTrainer,dstTrainer,id);
    action->set_status(this->getStatus());
    action->set_error_msg(this->getErrorMsg());
    return (action);
}
MoveCustomer::~MoveCustomer()=default;
//class close:

Close::Close(int id):trainerId(id){};
void Close::act(Studio &studio){
    Trainer* trainer = studio.getTrainer(trainerId);
    if(trainer == nullptr || !trainer->isOpen()){
        BaseAction::error("Trainer does not exist or is not open");
        std::cout<<getErrorMsg()<<endl;
    }
    else{
    trainer->closeTrainer();
    int salary = trainer->getSalary();
    std::cout<< "Trainer "<< trainerId<<" closed. Salary "<< salary<<"NIS"<<endl;
    complete();
    }
    studio.log_action(this);

}
std::string Close::toString()const{
    string s = "close " + std::to_string(trainerId);
    string action_status = getStatus()==COMPLETED ? "Completed" : getErrorMsg();
    s = s + " " + action_status;
    return s;
}
Close* Close::clone(){
    Close *action = new Close(trainerId);
    action->set_status(this->getStatus());
    action->set_error_msg(this->getErrorMsg());
    return (action);
}
Close::~Close() = default;

//class closall

CloseAll::CloseAll(){};

void CloseAll::act(Studio &studio){
    studio.close();
    complete();
    studio.log_action(this);
};
std::string CloseAll::toString() const{
    string s = "closeall Completed";
    return s;
};
CloseAll* CloseAll::clone(){
    CloseAll *action = new CloseAll();
    action->set_status(this->getStatus());
    action->set_error_msg(this->getErrorMsg());
    return (action);
}
CloseAll::~CloseAll() = default;

//class PrintWorkoutOptions : public BaseAction 

PrintWorkoutOptions::PrintWorkoutOptions(){};
void PrintWorkoutOptions::act(Studio &studio){
    vector<Workout> workout_options = studio.getWorkoutOptions();
    for(Workout workout : workout_options){
        std::cout<<workout.getName()<<", "<<workout.get_type_name()<<", "<<workout.getPrice()<<endl;
    }
    complete();
    studio.log_action(this);
}

std::string PrintWorkoutOptions::toString() const{
    string s = "workout_options Completed";
    return s;
};
PrintWorkoutOptions* PrintWorkoutOptions::clone(){
    return (new PrintWorkoutOptions());
}
PrintWorkoutOptions::~PrintWorkoutOptions()=default;

//class PrintTrainerStatus : public BaseAction {

PrintTrainerStatus::PrintTrainerStatus(int id):trainerId(id){
};
void PrintTrainerStatus::act(Studio &studio){
    Trainer *trainer =studio.getTrainer(trainerId);
    if(trainer != nullptr){
        string status = trainer->isOpen() ? "open" : "close";
        std::cout<< "Trainer "<<trainerId<<" status: "<<status<<"\n";
        if(trainer->isOpen()){
        vector<Customer*> customers = trainer->getCustomers();
        std::cout<<"Customers:\n";
        for(Customer* c: customers){
            std::cout<<c->getId()<<" "<<c->getName()<<"\n";
        }
        vector<OrderPair>& orders = trainer->getOrders();
        std::cout<<"Orders:\n";
        for(OrderPair order : orders){
            if(order.first!=-1){
            std::cout<<order.second.getName()<<" "<<order.second.getPrice();
            std::cout<<"NIS "<<trainer->getCustomer(order.first)->getId()<<endl;
            }
        }
        cout<< "Current Trainer's Salary: "<<trainer->getSalary()<<" NIS\n";
    }
    }
    complete();
    studio.log_action(this);
}
string PrintTrainerStatus::toString() const{
    string s = "status " + std::to_string(trainerId) + " Completed";
    return s;

}

PrintTrainerStatus* PrintTrainerStatus::clone(){
    return (new PrintTrainerStatus(trainerId));
}
PrintTrainerStatus::~PrintTrainerStatus()=default;
//class PrintActionsLog : public BaseAction 

PrintActionsLog::PrintActionsLog():BaseAction(){};

void PrintActionsLog::act (Studio &studio){
    vector<BaseAction*> actions_log = studio.getActionsLog();
    for(BaseAction *action : actions_log){
        std::cout<<action->toString()<<endl;
    }
    complete();
    studio.log_action(this);
}
std::string PrintActionsLog::toString() const {
    string s = "log Completed";
    return s;
}
PrintActionsLog* PrintActionsLog::clone(){
    return (new PrintActionsLog());
}
PrintActionsLog::~PrintActionsLog() =default;

//class backupStudio:

BackupStudio::BackupStudio(){};
void BackupStudio::act(Studio &studio){
    //TODO : need to make sure there is no memory leak if used twice in a row
    *backup = studio;
    complete();
    studio.log_action(this);
}
std::string BackupStudio::toString() const{
    string s = "backup Completed";
    return s;
}
BackupStudio* BackupStudio::clone(){
    return new BackupStudio();
}
BackupStudio::~BackupStudio() = default;

//class RestoreStudio:

RestoreStudio::RestoreStudio(){};

void RestoreStudio::act(Studio &studio){
    if(backup==nullptr){
        BaseAction::error("No backup available");
        std::cout<<BaseAction::getErrorMsg()<<endl;
    }
    else{ 
        studio = *backup;
        complete();
    }
    studio.log_action(this);
}

std::string RestoreStudio::toString() const {
    string s = "restore";
    string action_status = getStatus()==COMPLETED ? "Completed" : getErrorMsg();
    s = s + " " + action_status;
    return s;
}
RestoreStudio* RestoreStudio::clone(){
    RestoreStudio *action = new RestoreStudio();
    action->set_status(this->getStatus());
    action->set_error_msg(this->getErrorMsg());
    return (action);
}
RestoreStudio::~RestoreStudio() = default;
