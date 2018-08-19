#include "states.hh"

#include "knxconnection.hh"
#include "data_blocks.hh"
#include <iostream>

using namespace boost::asio;

namespace KNX
{
namespace ConnectionState
{

void State::changeState(KNX::Connection* con, const std::shared_ptr<State>& newState)
{
  con->mState = newState;
  std::cout << typeid(*newState).name() << std::endl;
}

Channel& State::getControlChannel(KNX::Connection* con)
{
  return con->mControl;
}

Channel& State::getDataChannel(KNX::Connection* con)
{
  return con->mData;
}

std::shared_ptr<State> Closed::getInstance()
{
  static auto instance = std::make_shared<Closed>();
  return instance;
}

std::shared_ptr<State> Opened::getInstance()
{
  static auto instance = std::make_shared<Opened>();
  return instance;
}

void Closed::open(KNX::Connection* con, const std::string& ip)
{
  Channel& chan = getControlChannel(con);
  chan.setPort(con->PORT);
  chan.setIP(ip);
  
  // configure data to send
  datagrams::knx_connection_request conReq;

  conReq.header.header_length = sizeof(datagrams::knx_header);
  conReq.header.protocol_version = 0x10;
  conReq.header.service_type_identifier = datagrams::CONNECT_REQUEST;
  conReq.header.total_length = sizeof(datagrams::knx_connection_request);

  conReq.body_discovery_endpoint; //TODO
  conReq.body_data_endpoint;
  conReq.body_information;


  // send CONNECT_REQUEST and wait for CONNECT_RESPONSE
  chan.send(conReq);
  using response = datagrams::knx_connection_response;
  auto data = std::unique_ptr<response>(static_cast<response*>(chan.receive()));
  // check if request was successful
  assert(typeid(data).hash_code() == typeid(response).hash_code());
  //std::cout << data-> << std::endl;
 // send CONNECTIONSTATE_REQUEST

 // wait for CONNECTIONSTATE_RESPONSE

 changeState(con, Opened::getInstance());
}

void Opened::close(KNX::Connection* con)
{
  // send DISCONNECT_REQUEST
  // wait for DISCONNECT_RESPONSE

  changeState(con, Closed::getInstance());
}

void Opened::send(KNX::Connection* con)
{
}


} // namespace ConnectionState
} // namespace KNX
