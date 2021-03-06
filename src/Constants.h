// LIMITS
#define MAX_MSG_LEN 3
#define MAX_SYNS 100
#define DATAGRAM_REPEATS 20

// COMMAND CODES
#define SET_ID 0x05
#define OPEN_VALVE 0x06
#define CLOSE_VALVE 0x07
#define IDENTIFY 0x08
#define SYN 0x09
#define ACK 0x10
#define END_OF_CHAIN 0x11
#define END_OF_DATAGRAM 0xFF

// DATAGRAM DESTINATION CODES
#define MASTER 0x01
#define EVERYONE 0x00
#define FIRST_UNIDENTIFIED 0x02
