
#ifndef _AUTOVEHICLE_H_
#define _AUTOVEHICLE_H_

// AutoVehicle.h

#include "ecs36b_Common.h"
#include "Person.h"

class Auto_V
{
  private:

  public:
    string address;
    string type;
    int numPassengers=1;
    std::vector<Person> passengers;
    Auto_V(std::vector<Person> argPeople, string argAddress, string argType);
    Auto_V();

    void setPassengers(std::vector<Person> argPeople);
    void setAddress(string argAddress);
    void setType(string argType);

    virtual Json::Value dump2JSON();
    virtual Json::Value sendMessage(string, Json::Value);
    virtual Json::Value responseMessage(Json::Value);

};


class Motorcycle: public Auto_V
{
  private:
    int calcAgeScore();
    int calcMedicalScore();
    int calcHelmetScore();
    int rating;
    // the higher the rating, the more likely we will hit them
    
  public:

    Motorcycle(std::vector<Person> argPeople, string argAddress, string argType);
    Motorcycle();

    Json::Value dump2JSON();

    int getRating();
    void calcRating();
  
};


class Car: public Auto_V
{
  private:
  public:
    Car(std::vector<Person> argPeople, string argAddress, string argType);
    Car();
    
    Json::Value dump2JSON();

    void makeDecision(Json::Value, Json::Value);
    int compareNumPeople(Json::Value, Json::Value);
    int compareScores(Json::Value, Json::Value);
};

#endif  // _AUTOVEHICLE_H_


