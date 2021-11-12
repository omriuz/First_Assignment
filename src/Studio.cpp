#include "Studio.h"
#include <fstream>
#include <sstream>

using namespace std;
	
/*
in the start():
we need to construct all the trainers
then list them into a vector of pointers to those trainers(trainers)
then do the same thing to the workouts
for some reason this one is not of pointers
change the bool open to true
*/

//we need to build the default constructor
Studio :: Studio(){};

Studio :: Studio(const std::string &configFilePath):open(true),customerId(0){
    string line;
    vector<string> text;
    ifstream my_config_file(configFilePath);
    while (getline (my_config_file, line)) {
        if (line[0]!='#' && line.length() > 0 )
        text.push_back(line);
    }
    for(string s : text){
        std::cout << "this is a line: ";
        std::cout << s<< endl;
    }
    int num_of_trainers = (int) text[0][0] - '0';
    vector<int> trainers_capacity;
    for(char c : text[1]){
        if(c!=','){
            trainers_capacity.push_back((int)c-'0');
        }
    }
    for (int i = 0; i<num_of_trainers; i++){
        //we need to construct new trainers in the right way
        Trainer temp (trainers_capacity[i]);
        trainers.push_back(&temp);
    }
    //TODO: need to complete constructing the workouts
    my_config_file.close();
};

studio :: incrementCId(){
    this.customerId++;
}
}
void Studio::tokenize(string &str, char delim, vector<string> &out)
{
	size_t start;
	size_t end = 0;

studio :: getCustomerId(){
    return customerId;
}