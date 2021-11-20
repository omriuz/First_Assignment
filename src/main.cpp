#include "Studio.h"
#include <iostream>
#include <fstream>

/*
new comment


*/

using namespace std;

Studio* backup = nullptr;


static std::string getWord(std::string &input, char sep=' '){
    //std::cout << "get world \n";
    std::string word;
    std::size_t endIndex = input.find_first_of(sep);
    if(endIndex == std::string::npos){
    word = input;
    std::size_t endIndex = input.length();
    input = "";

    }else{
    word = input.substr(0, endIndex);
    input = input.substr(endIndex+1);
    }
   // *startIndex = endIndex + 1;
    //std::cout << "\nget word input :"  <<input <<"\n";
    return word;

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
            //  std::cout << "\nid: "<< customer->getId();
            //  std::cout << "\nname: "<< customer->getName();
    return customer;

    
}  


static BaseAction* buildAction(std::string input, Studio &studio){
    // std::size_t startIndex = 0;
    BaseAction *action;
    std::string stop;
    std::string actionType = getWord(input);

   // std::cout << actionType;


    if(actionType.compare("open") == 0){
        // <traner Id> <customer1_name>,<customer1_strategy> <customer2_name>,<customer2_strategy>
        int trainerId = std::stoi(getWord(input));

        // std::cout << "\n trainer ID = " << trainerId;

        Customer *newCostumer;
        std::vector<Customer*> *customersList = new vector<Customer*>();
        while( input.length() != 0){
            std::string name = getWord(input, ',');
            std::string strategy = getWord(input);
   
            // need to figure out how is deleting customers.
            newCostumer = builsCustomer(name, strategy, studio);

            // std::vector<int> workout_orders = newCostumer->order(studio.getWorkoutOptions());
            // std::cout << newCostumer->getName() << " orders:\n";
            // for(int i : workout_orders){
            //     std::cout << i << "\n";
            // }
            customersList->push_back(newCostumer);

            // set the trainer vector of customers
        }

        std::getline(std::cin, stop);
        action = new OpenTrainer(trainerId, *customersList);  

//     }else if(actionType.compare("order") == 0){
//         int trainerId = std::stoi(getWord(input));
//         action = new Order(trainerId);

//     }else if(actionType.compare("move") == 0){
//         int srcTrainerId = std::stoi(getWord(input));
//         int dstTrainerId = std::stoi(getWord(input));
//         int customerId = std::stoi(getWord(input));
//         action = new MoveCustomer(srcTrainerId, dstTrainerId, customerId);

//     }else if(actionType.compare("close") == 0){
//         int trainerId = std::stoi(getWord(input));
//         action = new Close(trainerId);
        
//     }else if(actionType.compare("closeall") == 0){
//         action = new CloseAll();
        
//     }else if(actionType.compare("workout_option") == 0){
//         action = new PrintWorkoutOptions();
        
//     }else if(actionType.compare("status") == 0){
//         int trainerId = std::stoi(getWord(input));
//         action = new PrintTrainerStatus(trainerId);
        
//     }else if(actionType.compare("log") == 0){
//         action = new PrintActionsLog();
        
//     }else if(actionType.compare("backup") == 0){
//         action = new BackupStudio();
        
//     }else if(actionType.compare("restore") == 0){
//         action = new RestoreStudio();

    }
    return action;


//     /*
//     decompose the string into the relevent action
//     using the first word in the string
//     switch : case or if,elif,else
//     to construct the right action and return a pointer to the action

//     1. for openTrainer:
//     we want to construct each customer
//     then use the addCustomer method of trainer
//     after we built all the customers
//     we want to send a refence of the customerList in the trainer to the action
// //     */
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
        std::cout << "please enter the requested action: "<< std::endl;
        std::getline(std::cin, input);
        buildAction(input,studio);
    }
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}
