#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>

#include "basic.hh"
#include "header.hh"
#include "cemi.hh"

namespace KNX
{
    namespace datagrams
    {
        struct knx_tunneling_request: package
        {
            static const uint16_t SERVICE_TYPE_ID = 0x0420;
            knx_header header;
            boost::endian::big_uint8_t body_structure_length;
            boost::endian::big_uint8_t body_communication_channel_id;
            boost::endian::big_uint8_t body_sequence_counter;
            uint8_t reserved;
            cEMI body_cEMI;

            knx_tunneling_request() :
                    header(SERVICE_TYPE_ID, sizeof(knx_tunneling_request)),
                    body_structure_length(0),
                    body_communication_channel_id(0),
                    body_sequence_counter(0),
                    reserved(0),
                    body_cEMI()
            {

            }
        };
    }
}
