#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"

using namespace std;

class Studio{		
public:
    //constructors:
	Studio();
    Studio(const std::string &configFilePath);
    //copy constructor
    Studio(const Studio &Other);
    //copy assignment:
    Studio & operator=(const Studio &other);
    //move constructor:
    Studio(Studio &&other);
    //move assignment:
    Studio & operator=(Studio &&other);
    //destructor
    ~Studio();
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    void close();
    void incCustomerId();
    int getCustomerId();
    void tokenize(string &str, char delim, vector<int> &out);
    void tokenize(string &str, char delim, vector<string> &out);
    void log_action(BaseAction *action);
    

private:
    void move_clean(Studio &other);
    void copy(const Studio &other);
    void clear();
    bool open;
    int customerId;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif