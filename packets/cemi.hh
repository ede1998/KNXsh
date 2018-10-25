#pragma once

#include <cstdint>
#include <boost/endian/arithmetic.hpp>


namespace KNX
{
    namespace datagrams
    {
        struct cEMI
        {
            boost::endian::big_uint8_t message_code;
            boost::endian::big_uint8_t additional_information_length;
            boost::endian::big_uint8_t control_field_1;
            boost::endian::big_uint8_t control_field_2;
            boost::endian::big_uint16_t source_address;
            boost::endian::big_uint16_t destination_address;
            boost::endian::big_uint8_t npdu_length;
            boost::endian::big_uint8_t data[100]; //also has TPCI and APCI in it ???

            cEMI() = default;
        };
    }
}
