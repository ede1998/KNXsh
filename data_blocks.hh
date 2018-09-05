#pragma once

#include <cstdint>

namespace KNX
{
  const uint8_t PROTOCOL_VERSION = 0x10;
  namespace datagrams
  {

    struct package
    {
    protected:
      package () = default;
    };

    struct knx_header
    {
      uint8_t header_length;
      uint8_t protocol_version;
      uint16_t service_type_identifier;
      uint16_t total_length;

      knx_header (uint16_t sti, uint16_t len) :
	  service_type_identifier (sti), header_length (sizeof(knx_header)), protocol_version (
	      PROTOCOL_VERSION), total_length (len)
      {
      }
    };

    struct hpai_endpoint
    {
      uint8_t structure_length;
      uint8_t host_protocol_code;
      uint32_t ip_address;
      uint16_t ip_port;
    };

    struct connection_request_information
    {
      uint8_t structure_length;
      uint8_t connection_type;
      uint8_t knx_layer;
      const uint8_t reserved = 0;
    };

    struct connection_response_data_block
    {
      uint8_t structure_length;
      uint8_t connection_type;
      uint16_t knx_address;
    };

    struct cEMI
    {
      uint8_t message_code;
      uint8_t additional_information_length;
      uint8_t control_field_1;
      uint8_t control_field_2;
      uint16_t source_address;
      uint16_t destination_address;
      uint8_t npdu_length;
      uint8_t data[100]; //also has TPCI and APCI in it ???
    };

    struct knx_connection_request : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x0205;

      knx_header header;
      hpai_endpoint body_discovery_endpoint;
      hpai_endpoint body_data_endpoint;
      connection_request_information body_information;

      knx_connection_request () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    struct knx_connection_response : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x0206;
      knx_header header;
      uint8_t body_communication_channel_id;
      uint8_t body_status;
      hpai_endpoint body_data_endpoint;
      connection_response_data_block body_response_data;

      knx_connection_response () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    struct knx_connectionstate_request : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x0207;
      knx_header header;
      uint8_t body_communication_channel_id;
      const uint8_t reserved = 0;
      hpai_endpoint body_control_endpoint;
      knx_connectionstate_request () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    struct knx_connectionstate_response : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x0208;
      knx_header header;
      uint8_t body_communication_channel_id;
      uint8_t body_status;
      knx_connectionstate_response () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    struct knx_disconnect_request : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x0209;
      knx_header header;
      uint8_t body_communication_channel_id;
      const uint8_t reserved = 0;
      hpai_endpoint body_control_endpoint;

      knx_disconnect_request () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    struct knx_disconnect_response : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x020A;
      knx_header header;
      uint8_t body_communication_channel_id;
      uint8_t body_status;
      knx_disconnect_response () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    struct knx_tunneling_request : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x0420;
      knx_header header;
      uint8_t body_structure_length;
      uint8_t body_communication_channel_id;
      uint8_t body_sequence_counter;
      const uint8_t reserved = 0;
      cEMI body_cEMI;

      knx_tunneling_request () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    struct knx_tunneling_response : package
    {
      static const uint16_t SERVICE_TYPE_ID = 0x0421;
      knx_header header;
      uint8_t body_structure_length;
      uint8_t body_communication_channel_id;
      uint8_t body_sequence_counter;
      uint8_t body_status;

      knx_tunneling_response () :
	  header (SERVICE_TYPE_ID, sizeof(knx_connection_request))
      {

      }
    };

    static_assert(sizeof(uint8_t) == 1);
    static_assert(sizeof(uint16_t) == 2);
    static_assert(sizeof(uint32_t) == 4);
  } // namespace datagrams
} // namespace KNX
