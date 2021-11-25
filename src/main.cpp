#include "Studio.h"
#include <iostream>
#include <fstream>

/*
new comment
*/

using namespace std;

Studio* backup = nullptr;


static std::string getWord(std::string &input, char sep=' '){
    //std::cout << "get word \n";
    std::string word;
    std::size_t endIndex = input.find_first_of(sep);
    if(endIndex == std::string::npos){
    word = input;
    input = "";
    }else{
    word = input.substr(0, endIndex);
    input = input.substr(endIndex+1);
    }
   // *startIndex = endIndex + 1;
    //std::cout << "\nget word input :"  <<input <<"\n";
    return word;

}
static Customer* buildCustomer(std::string name, std::string strategy, Studio &studio){
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
    studio.incCustomerId();
            //  std::cout << "\nid: "<< customer->getId();
            //  std::cout << "\nname: "<< customer->getName();
    return customer;

    
}  
static BaseAction* buildAction(std::string input, Studio &studio){
    BaseAction *action;
    std::string stop;
    std::string actionType = getWord(input);
    if(actionType.compare("open") == 0){
        // <traner Id> <customer1_name>,<customer1_strategy> <customer2_name>,<customer2_strategy>
        int trainerId = std::stoi(getWord(input));
        Customer *newCustomer;
        std::vector<Customer*> customersList;
        while( input.length() != 0){
            std::string name = getWord(input, ',');
            std::string strategy = getWord(input);
            newCustomer = buildCustomer(name, strategy, studio);
            customersList.push_back(newCustomer);
        }
        action = new OpenTrainer(trainerId,customersList);  
    }

    else if(actionType.compare("order") == 0){
        int trainerId = std::stoi(getWord(input));
        action = new Order(trainerId);

    }else if(actionType.compare("move") == 0){
        int srcTrainerId = std::stoi(getWord(input));
        int dstTrainerId = std::stoi(getWord(input));
        int customerId = std::stoi(getWord(input));
        action = new MoveCustomer(srcTrainerId, dstTrainerId, customerId);

    }else if(actionType.compare("close") == 0){
        int trainerId = std::stoi(getWord(input));
        action = new Close(trainerId);
        
    }else if(actionType.compare("closeall") == 0){
        action = new CloseAll();
        
    }else if(actionType.compare("workout_options") == 0){
        action = new PrintWorkoutOptions();
        
     }
     
    else if(actionType.compare("status") == 0){
        int trainerId = std::stoi(getWord(input));
        action = new PrintTrainerStatus(trainerId);
        
    }
    else if(actionType.compare("log") == 0){
        action = new PrintActionsLog();
        
    }
    else if(actionType.compare("backup") == 0){
        action = new BackupStudio();
        
    }else if(actionType.compare("restore") == 0){
        action = new RestoreStudio();
    }
        return action;
}
static std::vector<std::string> text_to_strings(string textURL){
    ifstream my_text(textURL);
    vector<std::string> commands;
    string line;
    //turn the file into a vector of strings called text
    while (getline (my_text, line)) {
        commands.push_back(line);
    }
    return commands;
}   

int main(int argc, char** argv){
    if(argc==1){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    string testRunFile = argv[2];
    Studio studio(configurationFile);
    std::vector<string> test_commands = text_to_strings(testRunFile); 
    studio.start();
    bool run = true;
    std::string input;
    int i = 0;
    std::string hold;
    while(run){
        std::string input;
        input = test_commands[i];
        i++;
        // std::getline(std::cin, input);
        std::cout << input;
        std::cin.get();
        BaseAction *action = buildAction(input,studio);
        action->act(studio);
        action = nullptr;
        if(input=="closeall")
            break;
    }
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}