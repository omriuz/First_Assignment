#include "Studio.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;
static BaseAction* command(string s){
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
