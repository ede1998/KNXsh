#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>

#include "basic.hh"
#include "header.hh"


namespace KNX
{
    namespace datagrams
    {
        struct knx_connectionstate_response: package
        {
            static const uint16_t SERVICE_TYPE_ID = 0x0208;
            knx_header header;
            boost::endian::big_uint8_t body_communication_channel_id;
            boost::endian::big_uint8_t body_status;
            knx_connectionstate_response() :
                    header(SERVICE_TYPE_ID, sizeof(knx_connectionstate_response)),
                    body_communication_channel_id(0),
                    body_status(0)
            {

            }
        };
    }
}
