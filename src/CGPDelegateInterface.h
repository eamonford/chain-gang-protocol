#ifndef CGP_DELEGATE_INTERFACE_H_
#define CGP_DELEGATE_INTERFACE_H_

class CGPDelegateInterface {
public:
  virtual void processDatagram(Datagram* datagram) = 0;
  virtual int getStreamIndexForDatagram(Datagram* datagram) = 0;
  virtual bool shouldForwardDatagram(Datagram* datagram) = 0;
};

#endif
