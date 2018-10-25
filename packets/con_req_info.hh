#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>


namespace KNX
{
    namespace datagrams
    {
        struct connection_request_information
        {
            static const uint8_t TUNNEL_CONNECTION = 0x04;
            static const uint8_t TUNNEL_LINKLAYER = 0x02;
            boost::endian::big_uint8_t structure_length;
            boost::endian::big_uint8_t connection_type;
            boost::endian::big_uint8_t knx_layer;
            boost::endian::big_uint8_t reserved = 0x0;

            connection_request_information() :
                 structure_length(sizeof(connection_request_information)),
                 connection_type(TUNNEL_CONNECTION),
                 knx_layer(TUNNEL_LINKLAYER),
                 reserved(0x0)
            {
            }
        };
    }
}
