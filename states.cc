#include "states.hh"

#include "knxconnection.hh"
#include "packets/packets.hh"
#include <iostream>
#include <typeinfo>

using namespace boost::asio;

namespace KNX
{
    namespace ConnectionState
    {

        void State::changeState(KNX::Connection* con,
                                const std::shared_ptr<State>& newState)
        {
            con->mState = newState;
            std::cout << typeid(*newState).name() << std::endl;
        }

        Channel&
        State::getControlChannel(KNX::Connection* con)
        {
            return con->mControl;
        }

        Channel&
        State::getDataChannel(KNX::Connection* con)
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

        void Closed::open(KNX::Connection* con, const std::string& dest_ip, const std::string& src_ip)
        {
            Channel& chan = getControlChannel(con);
            chan.setPort(con->PORT);
            chan.setIP(dest_ip);

            uint32_t src_ip_long = boost::asio::ip::make_address(src_ip).to_v4().to_ulong();

            // configure data to send
            datagrams::knx_connection_request conReq(src_ip_long,
                                                     chan.getEndpoint().port(),
                                                     getDataChannel(con).getEndpoint().port());

            // send CONNECT_REQUEST and wait for CONNECT_RESPONSE
            chan.send(conReq);

            datagrams::knx_connection_response conResp;
            try
            {
                conResp = chan.receive<datagrams::knx_connection_response>();
            } catch (const UnexpectedPackageException& upe)
            {
                std::cerr << "Received wrong package: " << upe.what()
                        << std::endl;
                return;
            }

            // configure data to send
            datagrams::knx_connectionstate_request stateReq; //TODO

            // send CONNECTIONSTATE_REQUEST and wait for CONNECTIONSTATE_RESPONSE
            chan.send(stateReq);

            datagrams::knx_connectionstate_response stateResp;
            try
            {
                conResp = chan.receive<datagrams::knx_connection_response>();
            } catch (const UnexpectedPackageException& upe)
            {
                std::cerr << "Received wrong package: " << upe.what()
                        << std::endl;
                return;
            }

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
