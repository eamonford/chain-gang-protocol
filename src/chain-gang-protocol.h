#ifdef ARDUINO
    #include <Arduino.h>
#else
  #include "Particle.h"
#endif

#include "Datagram.h"
#include "Constants.h"

class CGPInterface {
    public:
        virtual bool sendDatagram(Datagram* msg, int identity) = 0;
        bool sendSynAndWaitForAck(Stream* stream);
        Stream* waitForSynAndSendAck(Stream* stream);
        Stream* waitForSynAndSendAck(int nStreams, Stream** streams);
        int* readBytes(Stream* comm, int numBytesToRead);
};
