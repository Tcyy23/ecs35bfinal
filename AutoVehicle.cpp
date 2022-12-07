#include "AutoVehicle.h"

// AUTO_V DEFINITIONS
//Constructor
Auto_V::Auto_V(std::vector<Person> argPeople, string argAddress, string argType)
{
  passengers = argPeople;
  numPassengers = passengers.size();
  address = argAddress;
  type = argType;
}

Auto_V::Auto_V()
{
    std::vector<Person> person;
    person.push_back(Person {});
    passengers = person;

    numPassengers = 1;
    address = "";
    type = "Vehicle";
}

//setting functions
void Auto_V::setPassengers(std::vector<Person> argPeople)
{
    passengers = argPeople;
}

void Auto_V::setAddress(string argAddress)
{
    address = argAddress;
}

void Auto_V::setType(string argType)
{
    type = argType;
}

//JSON
Json::Value Auto_V::dump2JSON()
{
  Json::Value result;
  result["passengers"] = numPassengers;
  result["address"] = address;
  result["type"] = type;

  return result;
}

Json::Value Auto_V::sendMessage(string operation, Json::Value argJson)
{
  Json::Value result;

  result["operation"] = operation;
  result["information"] = argJson;

  return result;
}

Json::Value Auto_V::responseMessage(Json::Value argJson)
{
  Json::Value result;
  if (argJson["operation"] == "emergency")
    {
        result = dump2JSON();
    } 
    
  return result;
}



// MOTORCYCLE DEFINITIONS
// Constructors
Motorcycle::Motorcycle(std::vector<Person> argPeople, string argAddress, string argType)
{
    passengers = argPeople;
    numPassengers = passengers.size();
    address = argAddress;
    type = argType;
    calcRating();
}

Motorcycle::Motorcycle()
{
    std::vector<Person> person;
    person.push_back(Person {});
    passengers = person;

    numPassengers = 0;
    address = "";
    type = "Motorcycle";
    rating = 0;
}

// JSON
Json::Value Motorcycle::dump2JSON()
{
  Json::Value result;
  result = Auto_V::dump2JSON();
  result["rating"] = rating;

  return result;
}

// calc functions
void Motorcycle::calcRating() 
{
    int tempScore = 0;

    tempScore+=calcAgeScore();
    tempScore+=calcMedicalScore();
    tempScore+=calcHelmetScore();

    rating = tempScore;
    
}

// the higher the age, the more the car will hit that motorcycle
int Motorcycle::calcAgeScore()
{
    int ageScore = 0;
        for(Person human : passengers) {
            int currentAge = human.getAge();

            if (currentAge > 0 && currentAge <= 10) {
              ageScore += 1;
            } else if (currentAge >= 11 && currentAge <= 21) {
                ageScore += 2;
            } else if (currentAge >= 22 && currentAge <= 40) {
                ageScore += 3;
            } else if (currentAge >= 41 && currentAge <= 79) {
                ageScore += 4;
            } else if (currentAge >= 80) {
                ageScore += 5;
            } else {
                ageScore += 0;
            }
        }


   return ageScore;
}

// medical is the severity of previous health issues of the passengers
// the higher the medical score, the less the car will hit that motorcycle
int Motorcycle::calcMedicalScore()
{
    int medicalScore = 0;
        for(Person human : passengers) {
            int medical = human.getMedical();

            if (medical >= 0 && medical <= 2) {
                medicalScore += 5;
            } else if (medical >= 3 && medical <= 5) {
                medicalScore += 4;
            } else if (medical >= 6 && medical <= 7) {
                medicalScore += 3;
            } else if (medical >= 8 && medical <= 9) {
                medicalScore += 2;
            } else if (medical >= 10) {
                medicalScore += 1;
            } else {
                medicalScore += 0;
            }
        }


    return medicalScore;
}

// if they are wearing a helmet, the car is more likely to hit that motorcycle
int Motorcycle::calcHelmetScore()
{
    int helmetScore = 0;

    for(Person human : passengers) {
        bool hasHelmet = human.getHelmet();

        if (hasHelmet) {
            helmetScore += 2;
        } else {
            helmetScore += 1;
        }

    }

    return helmetScore;
}



// CAR DEFINITIONS
// Constructors
Car::Car(std::vector<Person> argPeople, string argAddress, string argType)
{
    passengers = argPeople;
    numPassengers = passengers.size();
    address = argAddress;
    type = argType;
}

Car::Car()
{
    std::vector<Person> person;
    person.push_back(Person {});
    passengers = person;

    numPassengers = 0;
    address = "";
    type = "C";
}


// JSON
Json::Value Car::dump2JSON() 
{
    Json::Value result;
    result = Auto_V::dump2JSON();

    return result;
}

// comparison functions
void Car::makeDecision(Json::Value jsonL, Json::Value jsonR)
{
    Json::Value leftInfo = jsonL["information"];
    Json::Value rightInfo = jsonR["information"];

    cout << "The car will ";
    // number of people has highest priority
    if(compareNumPeople(leftInfo, rightInfo) == 0)
    {
        cout << " stay in lane" << endl;
    } else if (compareNumPeople(leftInfo, rightInfo) == 1)
    {
        cout << " turn left" << endl;
    } else if (compareNumPeople(leftInfo, rightInfo) == 2) {
        cout << " turn right" << endl;
    } else if (compareNumPeople(leftInfo, rightInfo) == 0)
    {
        // if our car has the same number or more passengers than the other vehicles
        // we will compare the scores of the left and right vehicle and
        // crash into one of them
        if(compareScores(leftInfo, rightInfo) == 1)
        {
            cout << " turn left" << endl;
        } else if (compareScores(leftInfo, rightInfo) == 2)
        {
            cout << " turn right" << endl;
        } else if (compareScores(leftInfo, rightInfo) == 0)
        {
            cout << " turn right" << endl;
            // if both scores are the safe, the car will default swerve left
            // since the driver seat is assumed to be on the left side
        }
    }
}

// return
// 0 if our vehicle has the least amount of people
// 1 if the first(left) vehicle has less people
// 2 if the second(right) vehicle has less people
// else send -1
int Car::compareNumPeople(Json::Value jsonL, Json::Value jsonR){
    string leftNumPeopleStr = jsonL["passengers"].asString();
    string rightNumPeopleStr = jsonR["passengers"].asString();

    int leftNumPeople = stoi(leftNumPeopleStr);
    int rightNumPeople = stoi(rightNumPeopleStr);
    int ourNumPeople = this->passengers.size();

    if(ourNumPeople < leftNumPeople && ourNumPeople < rightNumPeople)
    {
        return 0;
    } else if (leftNumPeople < rightNumPeople)
    {
        return 1;
    } else if (leftNumPeople > rightNumPeople)
    {
        return 2;
    } else
    {
        return -1;
    }
}


// return
// 0 if they're equal
// 1 if the first(left) vehicle has higher score
// 2 if the second(right) vehicle has higher score
int Car::compareScores(Json::Value jsonL, Json::Value jsonR) {
    string leftRatingStr = jsonL["rating"].asString();
    string rightRatingStr = jsonR["rating"].asString();

    int leftRating = stoi(leftRatingStr);
    int rightRating = stoi(rightRatingStr);
    if (leftRating > rightRating) {
        return 1;
    } else if (leftRating < rightRating) {
        return 2;
    } else {
        return 0;
    }
}
