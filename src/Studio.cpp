#include "Studio.h"
#include <fstream>
#include <sstream>

typedef std::pair<int, int> trainerPair;
//constructors:
Studio :: Studio():open(false),customerId(0),trainers(),workout_options(),actionsLog(){};
Studio :: Studio(const std::string &configFilePath):open(true),customerId(0),trainers(),workout_options(),actionsLog(){
    ifstream my_config_file(configFilePath);
    int num_of_trainers;
    vector<int> trainers_capacity;
    string line;
    stringstream ss; 
    vector<std::string> text;
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
    for(size_t i = 2; i<text.size();i++){
        tokenize(text[i], ',', workouts_data[i-2]);
        ss.clear();
        ss<<workouts_data[i-2][2];
        int price;
        ss >> price;
        WorkoutType type;
        if(workouts_data[i-2][1] == " Anaerobic")
            type = ANAEROBIC;
        else if (workouts_data[i-2][1] == " Mixed")
            type = MIXED;
        else if (workouts_data[i-2][1] == " Cardio")
            type = CARDIO;
        
        std::string w_name = workouts_data[i-2][0];
        Workout a (i-2,w_name,price,type);
        workout_options.push_back(a);
    }
    my_config_file.close();
};
//copy constructor:
Studio :: Studio(const Studio &other):open(other.open), customerId(other.customerId),trainers(),workout_options(),actionsLog(){
    copy(other);
}
//copy assignment operator
Studio & Studio::operator=(const Studio &other){
    if(this==&other)
        return *this;
    clear();
    copy(other);
    return *this;

}
//move constructor:
Studio :: Studio(Studio &&other):open(other.open), customerId(other.customerId),trainers(),workout_options(),actionsLog(){
    move_clean(other);
}
//move assignment:
Studio & Studio::operator=(Studio &&other){
   if(this==&other)
        return *this;
    clear();
    this->open = other.open;
    this->customerId = other.customerId;
    move_clean(other);
    return *this; 
}
//destructor:
Studio::~Studio(){
    clear();
}
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
		out.push_back(str.substr(start, end - start));
	}
}
void Studio::start(){
    open = true;
    std::cout<<"Studio is now open!"<<endl;
    backup = new Studio();
};
int Studio::getNumOfTrainers() const{
    return trainers.size();
};
Trainer* Studio::getTrainer(int tid){
    if(tid<0 || tid >= (int)trainers.size()){
        return nullptr;
    }
    //built upon the face that a trainer id is his order in the vecotr
    return trainers[tid];
};
void Studio::close(){
    size_t length = getNumOfTrainers();
    vector <trainerPair> closed_trainers;
    for (size_t i = 0; i < length; i++)
    {
        if(trainers[i]->isOpen()){
            trainers[i]->closeTrainer();
            trainerPair p(i,trainers[i]->getSalary());
            closed_trainers.push_back(p);
}}
    for(trainerPair pair : closed_trainers){
        std::cout<<"Trainer "<< pair.first<<" closed. Salary "<<pair.second<<"NIS"<<endl;
    }
    open = false;
}
const std::vector<BaseAction*>& Studio::getActionsLog() const{
    return actionsLog;
} 
std::vector<Workout>& Studio::getWorkoutOptions(){
    return workout_options;
};
int Studio::getCustomerId(){
    return customerId;
};
void Studio::incCustomerId(){
    this->customerId++;
};
void Studio::log_action(BaseAction *action){
    actionsLog.push_back(action);
};
void Studio::clear(){
    for(Trainer *t : trainers){
        delete t;
    }
    //TODO: should we delete the workouts???
    // for(Workout w : workout_options){
    //     delete w;
    // }
    for(BaseAction *b : actionsLog){
        delete b;
    }
    //TODO: it's okay to clear or should we turn pointers in to nullptr?
    trainers.clear();
    workout_options.clear();
    actionsLog.clear();
}
void Studio::copy(const Studio &other){
    for(Trainer* t : other.trainers){

        Trainer *next_trainer = new Trainer(*t);
        trainers.push_back(next_trainer);
    }
    for(Workout w : other.workout_options){
        Workout next_workout(w);
        this->workout_options.push_back(next_workout);
    }
    for(BaseAction* a : other.actionsLog){
        BaseAction* next_action = a->clone();
        this->actionsLog.push_back(next_action);
    }
}
void Studio::move_clean(Studio &other){
        for(Trainer* t : other.trainers){
        this->trainers.push_back(t);
    }
    for(Workout w : other.workout_options){
        this->workout_options.push_back(w);
    }
    for(BaseAction* a : actionsLog){
        this->actionsLog.push_back(a);
    }
    other.open = NULL;
    other.customerId = 0;
    trainers.clear();
    workout_options.clear();
    actionsLog.clear();
}