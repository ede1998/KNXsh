#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>

#include "basic.hh"
#include "header.hh"
#include "hpai_endpoint.hh"
#include "con_req_info.hh"

namespace KNX
{
    namespace datagrams
    {
        struct knx_connection_request: package
        {
            static const uint16_t SERVICE_TYPE_ID = 0x0205;

            knx_header header;
            hpai_endpoint body_discovery_endpoint;
            hpai_endpoint body_data_endpoint;
            connection_request_information body_information;

            knx_connection_request(uint32_t ip, uint16_t discovery_port, uint16_t data_port) :
                    header(SERVICE_TYPE_ID, sizeof(knx_connection_request)),
                    body_discovery_endpoint(ip, discovery_port),
                    body_data_endpoint(ip, data_port),
                    body_information()
            {
            }
        };
    }
}
