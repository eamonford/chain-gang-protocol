#ifndef CGP_H_
#define CGP_H_

#ifdef ARDUINO
    #include <Arduino.h>
#else
  #include "Particle.h"
#endif

#include "Datagram.h"
#include "Constants.h"
#include "CGPDelegateInterface.h"

class CGP {
private:
      int numStreams;
      Stream** streams;
      int* lastDatagramIds;
      CGPDelegateInterface* delegate;

      int readUntil(int bufferLen, int* buffer, Stream* stream, int terminal, long timeout);
      void writeDatagramToStream(Stream* stream, Datagram* datagram);
      Datagram* getDatagramOnAnyStream(long timeout);
      Datagram* getDatagramOrEatJunk(Stream* stream, long timeout);

public:
  CGP(int numStreams, Stream** newStreams, CGPDelegateInterface* newDelegate);
  void sendDatagram(Datagram* datagram);
  void getAndProcessDatagram();
  void getAndProcessDatagram(long timeout);
};

#endif
