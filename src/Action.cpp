#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"

enum ActionStatus{
    COMPLETED, ERROR
};

//Forward declaration
class Studio;

class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Studio& studio)=0;
    virtual std::string toString() const=0;
protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
private:
    std::string errorMsg;
    ActionStatus status;
};


class OpenTrainer : public BaseAction {
public:
    /*
    in the constructor:
    we need to update the fields.

    in the act:
    *we need to figure how were gonna use the studio method (get trainer())
    checks if the trainer exists and not open allready
    we need to change the open field of the trainer to true
    send the message in case of error or succses

    in the toString:
    turn the arguemts into string
    */
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    void act(Studio &studio);
    std::string toString() const;
private:
	const int trainerId;
	std::vector<Customer *> customers;
};

/*
in the constructor:
update the trainer id
in act:
need to check if the trainer dosent exist or isnt open
we proably need to use the trainer order method so it can:
use the costumer method of order and to print the workout for each one
we need to think about how to save the data for future need
*/
class Order : public BaseAction {
public:
    Order(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};

/*
in the constructor:
upadate the fields
in the act:
check all the bad cases
lets say we have the source costumer = 1 and the dest =2
we want to do 2.addCustomer(1.getCustomer(id))
then we want to do 1.removeCustomer(id)
we need to implement those methods in trainer correctly according to this
after that we need to check all the bad cases that might have happend
like an empty trainer
we need to remember to transfer the order in the order
*/
class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};

/*
in the constructor=
usual
in the act:
salary - uses the getSalary method of the trainer(which sums the vector)

*/

class Close : public BaseAction {
public:
    Close(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    void act(Studio &studio);
    std::string toString() const;
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    void act(Studio &studio);
    std::string toString() const;
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;

};


#endif