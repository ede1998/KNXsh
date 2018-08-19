#pragma once

enum ServiceTypeIdentifier
{
  TUNNELING_REQUEST = 0x0420,
  TUNNELING_ACK = 0x0421,
  CONNECT_REQUEST = 0x0205,
  CONNECT_RESP = 0x0206,
  CONNECTIONSTATE_REQUEST = 0x0207,
  CONNECTIONSTATE_RESPONSE = 0x0208,
  DISCONNECT_REQUEST = 0x0209,
  DISCONNECT_RESPONSE = 0x020A
}

class Message
{
  public:
    void setServiceTypeIdentifier(ServiceTypeIdentifier sti);
    ServiceTypeIdentifier getServiceTypeIdentifier();

  private:
    ServiceTypeIdentifier mServiceTypeId;
    static const unsigned short PROTOCOL_VERSION = 0x10;

    unsigned short calculateHeaderLen();
    unsigned short calculateTotalLen();

};
