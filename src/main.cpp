#include "Studio.h"
#include <iostream>
#include <fstream>

using namespace std;

Studio* backup = nullptr;

static std::string getWorld(std::size_t* startIndex, char sep, const std::string input){
    std::size_t endIndex = input.find_first_of(sep);
    std::size_t len = endIndex - *startIndex + 1;
    std::string output;
    input.copy(output, len, *startIndex);
    *startIndex = endIndex + 1;

}

static Customer* builsCustomer(std::string name, std::string strategy, studio &studio){
    Customer customer;
    if(strategy.comper("swt") == 0){ //Sweaty Customer
        Customer = new SweatyCustomer(name,studio.getCustomerId());
    }else if(strategy.comper("chp") == 0){ //Cheap Customer
        Customer = new CheapCustomer(name,studio.getCustomerId());
    }else if(strategy.comper("mcl") == 0){ //Heavy Muscle Customer
        Customer = new HeavyMuscleCustomer(name,studio.getCustomerId());
    }else if(strategy.comper("fbd") == 0){ //Full Body Customer
        Customer = new FullBodyCustomer(name,studio.getCustomerId());
    }
    studio.incrementCId();
    return customer&;
    
}  

static BaseAction* buildAction(string input, studio &studio){
    std::size_t tartIndex = 0;
    BaseAction action;
    actionType = getWorld(startIndex&,' ', input);
    if(actionType.comper("open") == 0){
        // <traner Id> <customer1_name>,<customer1_strategy> <customer2_name>,<customer2_strategy>
        int trainerId = std::stoi(getWorld(startIndex& , ' ', input));
        Costumer *newCostumer;
        std::vector<Customer*> customersList = new vector();
        while(startIndex != input.len()){
            std::string name = getWorld(startIndex&, ',', input);
            std::string strategy = getWorld(startIndex&, ' ', input);
            // need to figure out how is deleting customers.
            newCostumer = builsCustomer(name, strategy, studio);
            customerList.push_back(&newCostumer);
            // set the trainer vector of customers
            studio.getTrainer(trainerId).addCustomer(&newCostumer)
        }
              
        // OpenTrainer(int id, std::vector<Customer *> &customersList);
        action = new OpenTrainer(trainerId, customerList);  

    }else if(actionType.comper("order") == 0){
        int trainerId = std::stoi(getWorld(startIndex& , ' ', input));
        action = new Order(trainerId);

    }else if(actionType.comper("move") == 0){
        
    }else if(actionType.comper("close") == 0){
        
    }else if(actionType.comper("closeall") == 0){
        
    }else if(actionType.comper("workout_option") == 0){
        
    }else if(actionType.comper("status") == 0){
        
    }else if(actionType.comper("log") == 0){
        
    }else if(actionType.comper("backup") == 0){
        
    }else if(actionType.comper("restore") == 0){
        
    }
    return action;


    /*
    decompose the string into the relevent action
    using the first word in the string
    switch : case or if,elif,else
    to construct the right action and return a pointer to the action

    1. for openTrainer:
    we want to construct each customer
    then use the addCustomer method of trainer
    after we built all the customers
    we want to send a refence of the customerList in the trainer to the action
    */
}  
int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    Studio studio(configurationFile);
    studio.start();
    bool run = true;
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}
