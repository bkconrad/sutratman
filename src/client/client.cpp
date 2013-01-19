#include "client.h"

Client::Client()
{
   //ctor
}

Client::~Client()
{
   //dtor
}

/** @brief Main client entry point
  */
void Client::go()
{
   Video v;
   while (v.run());
}

