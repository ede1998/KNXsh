#pragma once
namespace KNX
{
  namespace datagrams
  {

    struct package
    {
      protected:
        package() = default;
    };
  
    struct knx_header
    {
      unsigned char header_length;
      unsigned char protocol_version;
      unsigned short service_type_identifier;
      unsigned short total_length;
    };
    
    struct hpai_endpoint
    {
      unsigned char structure_length;
      unsigned char host_protocol_code;
      unsigned int ip_address;
      unsigned short ip_port;
    };
    
    struct connection_request_information
    {
      unsigned char structure_length;
      unsigned char connection_type;
      unsigned char knx_layer;
      const unsigned char reserved = 0;
    };
    
    struct connection_response_data_block
    {
      unsigned char structure_length;
      unsigned char connection_type;
      unsigned short knx_address;
    };
    
    struct cEMI
    {
      unsigned char mesage_code;
      unsigned char additional_information_length;
      unsigned char control_field_1;
      unsigned char control_field_2;
      unsigned short source_address;
      unsigned short destination_address;
      unsigned char npdu_length;
      unsigned char data[100]; //also has TPCI and APCI in it ???
    };
    struct knx_connection_request: package
    {
      knx_header header;
      hpai_endpoint body_discovery_endpoint;
      hpai_endpoint body_data_endpoint;
      connection_request_information body_information;
    };
    
    struct knx_connection_response: package
    {
      knx_header header;
      unsigned char body_communication_channel_id;
      unsigned char body_status;
      hpai_endpoint body_data_endpoint;
      connection_response_data_block body_response_data;
    };
    
    struct knx_connectionstate_request: package
    {
      knx_header header;
      unsigned char body_communication_channel_id;
      const unsigned char reserved = 0;
      hpai_endpoint body_control_endpoint;
    };
    
    struct knx_connectionstate_response: package
    {
      knx_header header;
      unsigned char body_communication_channel_id;
      unsigned char body_status;
    };
    
    struct knx_disconnect_request: package
    {
      knx_header header;
      unsigned char body_communication_channel_id;
      const unsigned char reserved = 0;
      hpai_endpoint body_control_endpoint;
    };
    
    struct knx_disconnect_response: package
    {
      knx_header header;
      unsigned char body_communication_channel_id;
      unsigned char body_status;
    };
    
    struct knx_tunneling_request: package
    {
      knx_header header;
      unsigned char body_structure_length;
      unsigned char body_communication_channel_id;
      unsigned char body_sequence_counter;
      const unsigned char reserved = 0;
      cEMI body_cEMI;
    };
    
    struct knx_tunneling_response: package
    {
      knx_header header;
      unsigned char body_structure_length;
      unsigned char body_communication_channel_id;
      unsigned char body_sequence_counter;
      unsigned char body_status;
    };
    
    enum ServiceTypeIdentifier
    {
      TUNNELING_REQUEST = 0x0420,
      TUNNELING_ACKNOWLEDGE = 0x0421,
      CONNECT_REQUEST = 0x0205,
      CONNECT_RESPONSE = 0x0206,
      CONNECTIONSTATE_REQUEST = 0x0207,
      CONNECTIONSTATE_RESPONSE = 0x0208,
      DISCONNECT_REQUEST = 0x0209,
      DISCONNECT_RESPONSE = 0x020A
    };

    static_assert(sizeof(unsigned char) == 1);
    static_assert(sizeof(unsigned short) == 2);
    static_assert(sizeof(unsigned int) == 4);
  } // namespace datagrams
} // namespace KNX
