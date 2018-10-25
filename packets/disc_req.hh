#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>

#include "basic.hh"
#include "header.hh"
#include "hpai_endpoint.hh"

namespace KNX
{
    namespace datagrams
    {
        struct knx_disconnect_request: package
        {
            static const uint16_t SERVICE_TYPE_ID = 0x0209;
            knx_header header;
            boost::endian::big_uint8_t body_communication_channel_id;
            uint8_t reserved;
            hpai_endpoint body_control_endpoint;

            knx_disconnect_request() :
                    header(SERVICE_TYPE_ID, sizeof(knx_disconnect_request)),
                    body_communication_channel_id(0),
                    reserved(0),
                    body_control_endpoint(0,0)
            {

            }
        };
    }
}
