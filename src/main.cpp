#include "Studio.h"
#include <iostream>
#include <fstream>

/*
new comment


*/

using namespace std;

Studio* backup = nullptr;


static std::string getWorld(std::size_t* startIndex, char sep, const std::string input){
    std::size_t endIndex = input.find_first_of(sep);
    std::size_t len = endIndex - *startIndex + 1;
    std::string output = input.substr(*startIndex, len);
    *startIndex = endIndex + 1;

}


static Customer* builsCustomer(std::string name, std::string strategy, Studio &studio){
    Customer *customer;
    if(strategy.compare("swt") == 0){ //Sweaty Customer
        customer = new SweatyCustomer(name,studio.getCustomerId());
    }else if(strategy.compare("chp") == 0){ //Cheap Customer
        customer = new CheapCustomer(name,studio.getCustomerId());
    }else if(strategy.compare("mcl") == 0){ //Heavy Muscle Customer
        customer = new HeavyMuscleCustomer(name,studio.getCustomerId());
    }else if(strategy.compare("fbd") == 0){ //Full Body Customer
        customer = new FullBodyCustomer(name,studio.getCustomerId());
    }
    studio.incCustonerId();
    return customer;

    
}  


static BaseAction* buildAction(string input, Studio &studio){
    std::size_t startIndex = 0;
    BaseAction *action;
    std::string actionType = getWorld(&startIndex, ' ', input);
    if(actionType.compare("open") == 0){
        // <traner Id> <customer1_name>,<customer1_strategy> <customer2_name>,<customer2_strategy>
        int trainerId = std::stoi(getWorld(&startIndex,' ', input));
        Customer *newCostumer;
        // std::vector<Customer*> customersList = new vector<Customer*>();
        while(startIndex != input.length()){
            std::string name = getWorld(&startIndex, ',', input);
            std::string strategy = getWorld(&startIndex, ' ', input);
            // need to figure out how is deleting customers.
            newCostumer = builsCustomer(name, strategy, studio);
            // customerList.push_back(&newCostumer);
            // set the trainer vector of customers
            studio.getTrainer(trainerId)->addCustomer(newCostumer);
        }
              
        // OpenTrainer(int id, std::vector<Customer *> &customersList);
        action = new OpenTrainer(trainerId, studio.getTrainer(trainerId)->getCustomers());  

    }else if(actionType.compare("order") == 0){
        int trainerId = std::stoi(getWorld(&startIndex , ' ', input));
        action = new Order(trainerId);

    }else if(actionType.compare("move") == 0){
        int srcTrainerId = std::stoi(getWorld(&startIndex , ' ', input));
        int dstTrainerId = std::stoi(getWorld(&startIndex , ' ', input));
        int customerId = std::stoi(getWorld(&startIndex , ' ', input));
        action = new MoveCustomer(srcTrainerId, dstTrainerId, customerId);

    }else if(actionType.compare("close") == 0){
        int trainerId = std::stoi(getWorld(&startIndex , ' ', input));
        action = new Close(trainerId);
        
    }else if(actionType.compare("closeall") == 0){
        action = new CloseAll();
        
    }else if(actionType.compare("workout_option") == 0){
        action = new PrintWorkoutOptions();
        
    }else if(actionType.compare("status") == 0){
        int trainerId = std::stoi(getWorld(&startIndex , ' ', input));
        action = new PrintTrainerStatus(trainerId);
        
    }else if(actionType.compare("log") == 0){
        action = new PrintActionsLog();
        
    }else if(actionType.compare("backup") == 0){
        action = new BackupStudio();
        
    }else if(actionType.compare("restore") == 0){
        action = new RestoreStudio();

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
//     */
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
    while(run){
        std::string input;
        std::cout << "please enter the requested action";
        std::cin >> input;
        buildAction(input,studio);
    }
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}
