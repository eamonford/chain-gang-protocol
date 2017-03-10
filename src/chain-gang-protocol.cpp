#include "chain-gang-protocol.h"

bool CGPInterface::sendSynAndWaitForAck(Stream* stream) {
  int tryCount = 0;
  do {
    stream->write(SYN);
    if (tryCount++ == MAX_SYNS) {
      return false;
    }
  } while (stream->available() == 0 || stream->read() != ACK);
  return true;
}

int* CGPInterface::readBytes(Stream* stream, int numBytesToRead) {
  int* datagram = (int*)malloc(sizeof(int)*numBytesToRead);
  int numBytesReceived = 0;
  while (numBytesReceived < numBytesToRead) {
    if (stream->available() > 0) {
      datagram[numBytesReceived++] = stream->read();
    }
  }
  return datagram;
}
