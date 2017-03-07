
#ifndef DATAGRAM_H_
#define DATAGRAM_H_

class Datagram {
  public:
    int destination;
    int command;
    int arg;

    Datagram(int destination, int command, int arg);
    bool isForId(int id);
    bool isForIdOtherThan(int id);

    static Datagram* parse(int* intArray) {
      return new Datagram(intArray[0], intArray[1], intArray[2]);
    }
};

#endif
