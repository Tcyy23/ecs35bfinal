
// hw3_miou_2022.cpp

#include "ecs36b_Common.h"
#include "AutoVehicle.h"

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

Motorcycle right_moto;


class MyServer : public Server
{
public:
  MyServer(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value request(const Json::Value& json_object);
};

MyServer::MyServer(AbstractServerConnector &connector, serverVersion_t type)
  : Server(connector, type)
{
  std::cout << "MyServer Object created" << std::endl;
}

// member functions

Json::Value
Myhw5Server::request
(const Json::Value& json_object)
{
  Json::Value result;
  result = right_moto.response_message(json_object);

  cout << result.toStyledString() << endl;

  return result;
}


int
main()
{
  cout << "----- Server for Right Motorcycle -----" << endl << endl;

  // create passengers for right motorcycle
  bool helmet = true;
  int med = 6;
  int age = 40;
  Person passenger1(true, med, age);
  std::vector<Person> passengers;
  passengers.push_back(passenger1);

  // creating the right motorcycle
  string rightm_address = "http://127.0.0.1:8384";
  right_moto.setPassengers(passengers);
  right_moto.setAddress(rightm_address);
  right_moto.setType("M");
    
  // server stuff
  HttpServer httpserver(8384);
  MyServer srv(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  srv.StartListening();
  
  std::cout << "Hit enter to stop the Right Motorcycle server" << endl;

  getchar();
  getchar();
  srv.StopListening();

  return 0;
}


