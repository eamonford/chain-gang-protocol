#ifndef DATAGRAM_H_
#define DATAGRAM_H_

#ifdef ARDUINO
    #include <Arduino.h>
#else
  #include "Particle.h"
#endif

class Datagram {
  private:
    Datagram(int destination, int command, int arg, int id);

  public:
    int destination;
    int command;
    int arg;
    int id;

    Datagram(int destination, int command, int arg);
    bool isForId(int id);
    bool isForIdOtherThan(int id);

    static Datagram* parse(int* byteArray) {
      return new Datagram(byteArray[0], byteArray[1], byteArray[2], byteArray[3]);
    }
};

#endif
