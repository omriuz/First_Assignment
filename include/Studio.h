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
    Studio(const Studio &Other);
    Studio(Studio &&other);
    //copy assignment:
    Studio & operator=(const Studio &other);
    Studio & operator=(Studio &&other);

    //TODO: move oprators???
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
    void copy(const Studio &other);
    void move_clean(Studio &other);
    

private:
    void clear();
    bool open;
    int customerId;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif