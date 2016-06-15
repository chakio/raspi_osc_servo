#ifndef __libdacs1500rcp24__dacs1500rcp24__
#define __libdacs1500rcp24__dacs1500rcp24__


#include <iostream>
#include <string.h>
#include "oscpack/osc/OscReceivedElements.h"
#include "oscpack/osc/OscPacketListener.h"
#include "oscpack/ip/UdpSocket.h"


class ExamplePacketListener : public osc::OscPacketListener {
protected:

    virtual void ProcessMessage( const osc::ReceivedMessage& m,
                                 const IpEndpointName& remoteEndpoint );
};


#endif
