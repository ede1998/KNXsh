#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>


namespace KNX
{
    namespace datagrams
    {
        struct connection_response_data_block
        {
            boost::endian::big_uint8_t structure_length;
            boost::endian::big_uint8_t connection_type;
            boost::endian::big_uint16_t knx_address;

            connection_response_data_block() = default;
        };
    }
}
