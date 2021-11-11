#include "Studio.h"
#include <fstream>
#include <sstream>
	
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

Studio :: Studio(const std::string &configFilePath):open(true){
    string line;
    stringstream ss; 
    vector<string> text;
    int num_of_trainers;
    vector<int> trainers_capacity;
    ifstream my_config_file(configFilePath);
    while (getline (my_config_file, line)) {
        if (line[0]!='#' && line.length() > 0 )
        text.push_back(line);
    }
    for(string s : text){
        std::cout << "this is a line: ";
        std::cout << s<< endl;
    }
    vector<vector<string>> workouts_data(text.size()-2);
    ss << text[0];
    ss >> num_of_trainers;
    tokenize(text[1], ',', trainers_capacity);
    for(int i = 0;i<num_of_trainers;i++){
        trainers.push_back((new Trainer(trainers_capacity[i])));
    }
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