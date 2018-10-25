#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>

template<class T>
static boost::asio::const_buffer convertToBuffer(const T& data)
{
    return boost::asio::buffer(reinterpret_cast<const void*>(&data), sizeof(T));
}

class UnexpectedPackageException: public std::exception
{
public:

    UnexpectedPackageException(uint16_t ID) :
            mSTID(ID)
    {
    }

    virtual const char*
    what() const noexcept
    {
        std::stringstream msg("Unknown Service Type-ID: 0x");
        msg << std::hex << mSTID << std::dec;
        return msg.str().c_str();
    }

private:
    uint16_t mSTID;
};

class Channel
{
public:
    Channel();
    boost::asio::ip::udp::endpoint& getEndpoint();
    boost::asio::ip::udp::socket& getSocket();
    void setIP(const std::string& ip);
    void setPort(unsigned short port);
    template<class T> void send(const T& buf);
    template<class T> T receive();
    void run();
private:
    boost::asio::ip::udp::endpoint mEndpoint;
    boost::asio::io_service mIOService;
    boost::asio::ip::udp::socket mSocket;
};

template<class T>
void Channel::send(const T& buf)
{
    mSocket.send_to(convertToBuffer(buf), mEndpoint);
}

template<class T>
T Channel::receive()
{
    namespace ip = boost::asio::ip;
    using ip::udp;

    udp::endpoint ep;
    T buffer;

    // receive package and create datagram from it
    size_t len = mSocket.receive_from(boost::asio::buffer(&buffer,
                                                          sizeof(buffer)),
                                      ep);

    if (T::SERVICE_TYPE_ID != buffer.header.service_type_identifier)
    {
        throw UnexpectedPackageException(buffer.header.service_type_identifier);
    }
    return buffer;
}
