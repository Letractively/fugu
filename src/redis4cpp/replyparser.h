#ifndef __REDIS4CPP_REPLY_PARSERH__
#define __REDIS4CPP_REPLY_PARSERH__

#include "interface.h"

namespace redis4cpp {

enum ReplyState
{
    REPLY_STRING
    ,REPLY_ARRAY
    ,REPLY_INTEGER
    ,REPLY_NIL
    ,REPLY_STATUS
    ,REPLY_ERROR
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
    ReplyState _currState;
    int _cursor;
    ReceiveBuffer& _reply;
    std::size_t _bytesRecvd;
};

}

#endif