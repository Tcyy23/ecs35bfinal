#include "Person.h"

//CONSTRUCTORS
Person::Person(bool argHelmet, int argMedical, int argAge) {
    this->wearingHelmet = argHelmet;
    this->medical = argMedical;
    this->age = argAge;
}

Person::Person() {
    this->wearingHelmet = true;
    this->medical = 0;
    this->age = 18;
}


//SET FUNCTIONS
void Person::setHelmet(bool argHelmet) {
    this->wearingHelmet = argHelmet;
}

void Person::setMedical(int argMedical) {
    this->medical = argMedical;
}

void Person::setAge(int argAge) {
    this->age = argAge;
}


//GET FUNCTIONS
bool Person::getHelmet() {
    return wearingHelmet;
}

int Person::getMedical() {
    return medical;
}

int Person::getAge() {
    return age;
}

//JSON
Json::Value Person::dup2JSON() {
    Json::Value result;

    int count = 1;
    for(Person human : this->passengers) {
        result["passenger"]
        result["medical"] = medical;
        result["age"] = age;
        result["helmet"] = wearinghelmet;
    }
}