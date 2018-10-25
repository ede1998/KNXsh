#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>
#include <array>
#include "knxconnection.hh"

using boost::asio::ip::udp;

int main(int argc, char** argv)
{
  std::cout << "Hello from " << argv[0] << std::endl;

  KNX::Connection con;
  con.open("127.0.0.1", "192.168.140.43");
  con.send();
  con.close();
  
  //udp::endpoint receiver_endpoint(boost::asio::ip::make_address("127.0.0.1"), 13); //boost::asio::ip::make_address("192.168.140.43"), 25034);
  //udp::socket socket(io_service);
  //socket.open(udp::v4());
  //std::cout << "Socket opened." << std::endl;
  //std::array<char, 1> send_buf  = {{ 0 }};//{{ 'h', 'e', 'l', 'l', 'o' , '\0' }};
  //socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
  //std::cout << "Data sent." << std::endl;
  //std::array<char, 128> recv_buf;
  //udp::endpoint sender_endpoint;
  //size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

  //std::cout.write(recv_buf.data(), len);
 return 0;
}
