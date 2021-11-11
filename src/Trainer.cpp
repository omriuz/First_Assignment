#include "Trainer.h"

using namespace std;

Trainer :: Trainer (int t_capacity):capacity(t_capacity),open(false){};
int Trainer :: getCapacity() const{
    return this->capacity;
};