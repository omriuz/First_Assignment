#include "Studio.h"
#include <fstream>
#include <sstream>

//we need to build the default constructor
Studio :: Studio(){};

Studio :: Studio(const std::string &configFilePath):open(true),customerId(0){
    ifstream my_config_file(configFilePath);
    int num_of_trainers;
    vector<int> trainers_capacity;
    string line;
    stringstream ss; 
    vector<string> text;
    //turn the file into a vector of strings called text
    while (getline (my_config_file, line)) {
        if (line[0]!='#' && line.length() > 0 )
        text.push_back(line);
    }
    //turn the first line into an int and save it in a variable
    ss << text[0];
    ss >> num_of_trainers;
    //turn the second line into a vector of strings called trainers_capaity
    tokenize(text[1], ',', trainers_capacity);
    for(int i = 0;i<num_of_trainers;i++){
        trainers.push_back((new Trainer(trainers_capacity[i])));
    }
    //turn the rest of text into workouts_data
    vector<vector<string>> workouts_data(text.size()-2);
    for(int i = 2; i<text.size();i++){
        tokenize(text[i], ', ', workouts_data[i-2]);
        ss.clear();
        ss<<workouts_data[i-2][2];
        int price;
        ss >> price;
        WorkoutType type;
        if(workouts_data[i-2][1] == "Anaerobic")
            type = ANAEROBIC;
        else if (workouts_data[i-2][1] == "Mixed")
            type = MIXED;
        else type = CARDIO;
        std::string w_name = workouts_data[i-2][0];
        Workout a (i-1,w_name,price,type);
        workout_options.push_back(a);
    }
    my_config_file.close();
};
 void Studio::tokenize(string &str, char delim, vector<int> &out)
{
	size_t start;
	size_t end = 0;
    stringstream ss;
	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
        ss << str.substr(start, end - start);
        int temp;
        ss >> temp;
		out.push_back(temp);
        ss.clear();
	}
}
void Studio::tokenize(string &str, char delim, vector<string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start-1));
	}
}
void Studio::start(){
    open = true;
};
int Studio::getNumOfTrainers() const{
    return trainers.size();
};
Trainer* Studio::getTrainer(int tid){
    if(tid<0 || tid>=trainers.size()){
        return NULL;
    }
    //built upon the face that a trainer id is his order in the vecotr
    return trainers[tid];
};
int Studio::getCustomerId(){
    return customerId;
};
void Studio::incCustonerId(){
    this->customerId++;
};

// const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
// std::vector<Workout>& getWorkoutOptions();
std::vector<Workout>& Studio::getWorkoutOptions(){
    return workout_options;
};

