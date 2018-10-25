#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>

#include "basic.hh"
#include "header.hh"
#include "hpai_endpoint.hh"
#include "con_resp_data_block.hh"

namespace KNX
{
    namespace datagrams
    {
        struct knx_connection_response: package
        {
            static const uint16_t SERVICE_TYPE_ID = 0x0206;
            knx_header header;
            boost::endian::big_uint8_t body_communication_channel_id;
            boost::endian::big_uint8_t body_status;
            hpai_endpoint body_data_endpoint;
            connection_response_data_block body_response_data;

            knx_connection_response() :
                    header(SERVICE_TYPE_ID, sizeof(knx_connection_response)),
                    body_communication_channel_id(0),
                    body_status(0),
                    body_data_endpoint(0,0),
                    body_response_data()
            {

            }
        };
    }
}
