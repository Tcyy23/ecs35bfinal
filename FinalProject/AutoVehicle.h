
#ifndef _AUTOVEHICLE_H_
#define _AUTOVEHICLE_H_

// AutoVehicle.h

#include "ecs36b_Common.h"

class Auto_V
{
private:
public:
    Auto_V(int p = 0, string hu = "", string t = "M",double m = 0,
           double s = 0, double age = 0, bool helmet = true);

virtual Json::Value dump2JSON();
virtual Json::Value send_message(string, Json::Value);
virtual Json::Value response_message(Json::Value);


virtual double cal_rating(Json::Value);
virtual void make_decision(double, double, double);

};


class Motorcycle: public Auto_V
{
 private:
 public:

    Motorcycle(int p = 0, string hu = "", string t = "M",double m = 0,
               double s = 0, double age = 0, bool helmet = true);

  virtual Json::Value dump2JSON();
  virtual double cal_rating(Json::Value);
  virtual void make_decision(double, double);
  
};

#endif  /* _AUTOVEHICLE_H_ */


