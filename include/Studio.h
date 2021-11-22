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
    Studio(Studio &Other);
    //copy assignment:
    Studio & operator=(const Studio &other);
    //TODO: move oprators???
    //destructor
    ~Studio();
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid) const;
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
    std::vector<Trainer*>& getTrainers();
    bool is_open() const;
    int getCustomerId() const;
    void tokenize(string &str, char delim, vector<int> &out);
    void tokenize(string &str, char delim, vector<string> &out);
    void log_action(BaseAction *action);
    void close();
    void incCustomerId();
    
    

private:
    void clear();
    bool open;
    int customerId;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif