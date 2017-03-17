#include "chain-gang-protocol.h"

bool CGPInterface::sendSynAndWaitForAck(Stream* stream) {
  int tryCount = 0;
  do {
    stream->write(SYN);
    delay(10);
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

Stream* CGPInterface::waitForSynAndSendAck(Stream* stream) {
  return waitForSynAndSendAck(1, &stream);
}

Stream* CGPInterface::waitForSynAndSendAck(int nStreams, Stream** streams) {
  int i = 0;
  Stream* currStream;
  do {
    currStream = streams[i];
    i = (i + 1) % nStreams;
    delay(30);
  } while (currStream->available() == 0 || currStream->read() != SYN);
  currStream->write(ACK);
  // Eat up any extra SYNs that got sent during the delay
  while (currStream->available() > 0 && currStream->peek() == SYN) {
    currStream->read();
    delay(20);
  }
  return currStream;
}
