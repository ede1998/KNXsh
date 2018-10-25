#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>


namespace KNX
{
    namespace datagrams
    {
        const uint8_t PROTOCOL_VERSION = 0x10;
        struct knx_header
        {
            boost::endian::big_uint8_t header_length;
            boost::endian::big_uint8_t protocol_version;
            boost::endian::big_uint16_t service_type_identifier;
            boost::endian::big_uint16_t total_length;

            knx_header(uint16_t sti, uint16_t len) :
                    service_type_identifier(sti),
                    header_length(sizeof(knx_header)),
                    protocol_version(PROTOCOL_VERSION),
                    total_length(len)
            {
            }
        };
    }
}
