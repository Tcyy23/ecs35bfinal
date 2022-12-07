#include "AutoVehicle.h"


// Auto_V
Auto_V::Motorcycle(int p, string ad, string t, double m,
                    double s, double ag, bool helmet)
{
  passengers = p;
  address = ad;
  type = t;
  medical = m;
  speed = s;
  age = ag;
  wearinghelmet = helmet;
}

Json::Value
Auto_V::dump2JSON
()
{
  Json::Value result;
  result["passengers"] = passengers;
  
  result["address"] = address;
  result["type"] = type;
  result["medical"] = medical;
  result["speed"] = speed;
  result["age"] = age;
  result["helmet"] = wearinghelmet;

  return result;
}

Json::Value 
Auto_V::send_message
(string operation, Json::Value obj)
{
  Json::Value result;

  result["operation"] = operation;
  result["information"] = obj;

  return result;
}

Json::Value 
Auto_V::response_message
(Json::Value obj)
{
  Json::Value result;
  if (obj["operation"] == "emergency")
  {
    result = dump2JSON();
  }
    
  else if (obj["operation"] == "move")
    return dump2JSON();
  else 
    return result;
}




// Auto_M
Auto_M:: Motorcycle(int p, string ad, string t, double m,
                          double s, double ag, bool helmet)
      {
        passengers = p;
        address = ad;
        type = t;
        medical = m;
        speed = s;
        age = ag;
        wearinghelmet = helmet;
      }

Json::Value 
Auto_M::dump2JSON()
{
  Json::Value result;
  result = Auto_V::dump2JSON();
  return result;
}

class Motorcycle : public Auto_V
{
private:
public:
    void calcRating();
    int calcAgeScore();
    int calcMedicalScore();
    int calcHelmetScore();
    int getRating();
}


void calcRating(Json::Value obj) {
    int tempScore = 0;

    tempScore+=calcAgeScore();
    tempScore+=calcMedicalScore();
    tempScore+=calcHelmetScore();

    this->rating = tempScore;
    
}

// the higher the age, the more the car will hit that motorcycle
int calcAgeScore() {
    int ageScore = 0;
        int currentAge = age();

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
   return ageScore;
}

// medical is the severity of previous health issues of the passengers
// the higher the medical score, the less the car will hit that motorcycle
int calcMedicalScore() {
    int medicalScore = 0;
        int medical = med();

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
    return medicalScore;
}

// if they are wearing a helmet, the car is more likely to hit that motorcycle
int calcHelmetScore() {
    int helmetScore = 0;
        bool hasHelmet = helmet();

        if (hasHelmet) {
            helmetScore += 2;
        } else {
            helmetScore += 1;
        }
    }
    return helmetScore;
}

