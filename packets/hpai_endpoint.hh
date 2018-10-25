#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>


namespace KNX
{
    namespace datagrams
    {
        struct hpai_endpoint
        {
            static const uint8_t IPV4_UDP = 0x1;
            boost::endian::big_uint8_t structure_length;
            boost::endian::big_uint8_t host_protocol_code;
            boost::endian::big_uint32_t ip_address;
            boost::endian::big_uint16_t ip_port;

            hpai_endpoint(uint32_t ip, uint16_t port) :
                structure_length(sizeof(hpai_endpoint)),
                host_protocol_code(IPV4_UDP),
                ip_address(ip),
                ip_port(port)
            {
            }
        };
    }
}
