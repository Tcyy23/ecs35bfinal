
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

Auto_M left_moto;

class Myhw5Server : public hw5Server
{
public:
  Myhw5Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value request(const Json::Value& json_object);
};

Myhw5Server::Myhw5Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Server(connector, type)
{
  std::cout << "Myhw5Server Object created" << std::endl;
}

// member functions

Json::Value
Myhw5Server::request
(const Json::Value& json_object)
{
  Json::Value result;
  result = l_moto.response_message(json_object);

  cout << result.toStyledString() << endl;

  return result;
}


int
main()
{
  cout << ">>>> Program for Left motorcycle <<<<\n\n";
  //number of passager
  int nop = 1;
  //if the passager is wearing helmet or not
  bool helmet = true;
   
  //number of medical
    int med = 6;
    int spd = 40;
    int disbetweencar = 30;
    int age = 40;
    
    right_moto.passengers = nop;
    right_moto.helmet = helmet;
    right_moto.age = age;
    right_moto.medical = med;
    right_moto.speed = spd;
    right_moto.disbetween_car = disbetweencar
    right_moto.rightm_address = "http://127.0.0.1:8384";
    
  HttpServer httpserver(8384);
  Myhw5Server srv(httpserver, 
                  JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  srv.StartListening();
  
  std::cout << "Hit enter to stop the LeftMotorcycle server" << endl;
  // avoid line break character
  getchar();
  getchar();
  srv.StopListening();

  return 0;
}


