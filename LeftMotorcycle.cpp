


#include "ecs36b_Common.h"
#include "AutoVehicle.h"
#include "Person.h"

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>
#include "ecs36b_Exception.h"

using namespace jsonrpc;
using namespace std;

Motorcycle left_moto;

// CLASS DECLARATION
class Myhw5Server : public hw5Server
{
  public:
    Myhw5Server(AbstractServerConnector &connector, serverVersion_t type);
    virtual Json::Value request(const Json::Value& json_object);
};

// CLASS DEFINITIONS
// constructor
Myhw5Server::Myhw5Server(AbstractServerConnector &connector, serverVersion_t type) : hw5Server(connector, type)
{
  std::cout << "LiftMotorcycle Object created" << std::endl;
}

// functions
Json::Value Myhw5Server::request (const Json::Value& json_object)
{
  Json::Value result;
  result = left_moto.responseMessage(json_object);

  cout << result.toStyledString() << endl;

  return result;
}



int main()
{
  cout << "-----Server for Left Motorcycle-----" << endl;

  // create passengers for left motorcycle
  bool helmet = true;
  int med = 6;
  int age = 40;
  Person passenger1(helmet, med, age);
  std::vector<Person> passengers;
  passengers.push_back(passenger1);

  // creating the left motorcycle
  string leftm_address = "http://localhost:8383";
  left_moto.setPassengers(passengers);
  left_moto.setAddress(leftm_address);
  left_moto.setType("Motorcycle");


  // server stuff
  HttpServer httpserver(8383);
  Myhw5Server srv(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  srv.StartListening();
  
  std::cout << "Hit enter to stop the Left Motorcycle server" << endl;
  getchar();
  srv.StopListening();

  return 0;
}


