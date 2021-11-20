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
    std::vector<std::pair<int,int>> anaerobic_pairs; //need to be deleted
    for(Workout w : workout_options){
        if(w.getType() == 0){
            anaerobic_pairs.push_back(std::make_pair(w.getId(),w.getPrice()));
        }
    }
    std::sort(anaerobic_pairs.begin(),anaerobic_pairs.end(),
    [](const std::pair<int,int> left, const std::pair<int,int> right){

        return left.second < right.second;
    });

    for(std::pair<int,int> p : anaerobic_pairs){
        workout_order.push_back(p.first);
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
    std::vector<std::pair<int,int>> cardio_pairs; //need to be deleted
    std::vector<std::pair<int,int>> mixed_pairs; //need to be deleted
    std::vector<std::pair<int,int>> anaerobic_pairs; //need to be deleted


    for(Workout w : workout_options){
        switch (w.getType()){
            case 0:
                anaerobic_pairs.push_back(std::make_pair(w.getId(),w.getPrice()));
                break;
            case 1:
                mixed_pairs.push_back(std::make_pair(w.getId(),w.getPrice()));
                break;
            case 2:
                cardio_pairs.push_back(std::make_pair(w.getId(),w.getPrice()));
        }   
    }

        std::sort(anaerobic_pairs.begin(),anaerobic_pairs.end(),
    [](const std::pair<int,int> left, const std::pair<int,int> right){

        return left.second < right.second;
    });
            std::sort(mixed_pairs.begin(),mixed_pairs.end(),
    [](const std::pair<int,int> left, const std::pair<int,int> right){

        return left.second < right.second;
    });
            std::sort(cardio_pairs.begin(),cardio_pairs.end(),
    [](const std::pair<int,int> left, const std::pair<int,int> right){

        return left.second < right.second;
    });

    workout_order.push_back(cardio_pairs.front().first);
    workout_order.push_back(mixed_pairs.back().first);
    workout_order.push_back(anaerobic_pairs.front().first);
    
    return workout_order;
}

std::string FullBodyCustomer:: toString() const{
    std::string s = "___FullBodyCustomer___";
    return s;
}