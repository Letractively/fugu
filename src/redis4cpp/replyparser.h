#ifndef __REDIS4CPP_REPLY_PARSERH__
#define __REDIS4CPP_REPLY_PARSERH__

#include "interface.h"

namespace redis4cpp {

enum ReplyType
{
    BAD_REPLY           = 0,
    STATUS_REPLY        = 1,
    ERROR_REPLY         = 2,
    INTEGER_REPLY       = 3,
    BULK_REPLY          = 4,
    MULTI_BULK_REPLY    = 5
};

class Reply
{
};

class ReplyParser
{
public:
    typedef ReceiveBuffer::iterator ReceiveBufferIter;
    ReplyParser(ReceiveBuffer& buff, std::size_t bytesRecvd);
    
    RerplyPtr NextReply();
    
private:
    RerplyPtr ParseNext(ReceiveBufferIter iter);
    RerplyPtr ParseLine(ReceiveBufferIter iter);
    RerplyPtr ParseBulk(ReceiveBufferIter iter);
    RerplyPtr ParseMultiBulk(ReceiveBufferIter iter);
    
private:
    ReplyType _currState;
    int _cursor;
    ReceiveBuffer& _reply;
    std::size_t _bytesRecvd;
};

}

#endif