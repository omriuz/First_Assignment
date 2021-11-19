#include "Customer.h"
#include <iostream>
#include <algorithm>
using namespace std;

Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id){}

//Customer::Customer(Customer customer):name(customer.getName),id(customer.getId){};

std::string Customer::getName() const{return name;}

int Customer::getId() const{return id;}

// _______________________SweatyCustomer______________________________

SweatyCustomer::SweatyCustomer(std::string c_name, int c_id):Customer(c_name,c_id){
}

std::vector<int> SweatyCustomer:: order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_order; // check if need to be new
    for (Workout w : workout_options){
        if(w.getType() == 2){
            workout_order.push_back(w.getId());
        }
    }
    return workout_order;
    //return vector of workouts that the customer ordered
}

std::string SweatyCustomer::toString() const{
    std::string s = "___Sweaty Customer___";
    return s;
}

// _______________________CheapCustomer______________________________

CheapCustomer::CheapCustomer(std::string c_name, int c_id):Customer(c_name,c_id){
}

std::vector<int> CheapCustomer:: order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_order; // check if need to be new
    int cheapest = INT32_MAX;
    int cheapestId =-1;
    for (Workout w : workout_options){
            if(w.getPrice() < cheapest){
                cheapestId = w.getId();
            }
    }
    workout_order.push_back(cheapestId);
    return workout_order;
    //return vector of workouts that the customer ordered
}

std::string CheapCustomer::toString() const{
    std::string s = "___Cheap Customer___";
    return s;
}

// _______________________HeavyMuscleCustomer______________________________

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string c_name, int c_id):Customer(c_name,c_id){
}

std::vector<int> HeavyMuscleCustomer:: order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_order; // check if need to be new
    std::vector<Workout> anaerobic_workouts; //need to be deleted
    for(Workout w : workout_options){
        if(w.getType() == 0){
            anaerobic_workouts.push_back(w);
        }
    }
    // std::sort(anaerobic_workouts.begin(),anaerobic_workouts.end());

    for(Workout w : anaerobic_workouts){
        workout_order.push_back(w.getId());
    }
    return workout_order;
}

std::string HeavyMuscleCustomer::toString() const{
    std::string s = "___Heavy Muscle Customer___";
    return s;
}

// _______________________FullBodyCustomer______________________________

FullBodyCustomer::FullBodyCustomer(std::string c_name, int c_id):Customer(c_name,c_id){
}

std::vector<int> FullBodyCustomer:: order(const std::vector<Workout> &workout_options){
    std::vector<int> workout_order; // check if need to be new
    std::vector<Workout> cardio_workouts; //need to be deleted
    std::vector<Workout> mixed_workouts; //need to be deleted
    std::vector<Workout> anaerobic_workouts; //need to be deleted
    for(Workout w : workout_options){
        switch (w.getType()){
            case 0:
                anaerobic_workouts.push_back(w);
                break;
            case 1:
                mixed_workouts.push_back(w);
                break;
            case 2:
                cardio_workouts.push_back(w);
        }   
    }
    // std::sort(cardio_workouts.begin(),cardio_workouts.end());
    // std::sort(mixed_workouts.begin(),mixed_workouts.end());
    // std::sort(anaerobic_workouts.begin(),anaerobic_workouts.end());

    workout_order.push_back(cardio_workouts.front().getId());
    workout_order.push_back(mixed_workouts.back().getId());
    workout_order.push_back(anaerobic_workouts.front().getId());
    
    return workout_order;
}

std::string FullBodyCustomer:: toString() const{
    std::string s = "___FullBodyCustomer___";
    return s;
}