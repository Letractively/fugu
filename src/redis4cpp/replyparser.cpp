#include "replyparser.h"

namespace redis4cpp {
    
static long long ReadLongLong(char *s) {
    long long v = 0;
    int dec, mult = 1;
    char c;

    if (*s == '-') {
        mult = -1;
        s++;
    } else if (*s == '+') {
        mult = 1;
        s++;
    }

    while ((c = *(s++)) != '\r') {
        dec = c - '0';
        if (dec >= 0 && dec < 10) {
            v *= 10;
            v += dec;
        } else {
            /* Should not happen... */
            return -1;
        }
    }

    return mult*v;
}

ReplyParser::ReplyParser(ReceiveBuffer& buff, std::size_t bytesRecvd)
    :_reply(buff)
    ,_bytesRecvd(bytesRecvd)
    ,_cursor(0)
{
}

RerplyPtr ReplyParser::NextReply()
{
    if(_cursor >= _bytesRecvd)
        return RerplyPtr();
    
    return ParseNext(_reply.begin() + _cursor);
}

RerplyPtr ReplyParser::ParseNext(ReceiveBufferIter iter)
{
    char type = _reply[_cursor];
    _cursor++;
    switch(type)
    {
        // Single line reply
        case '+':
            _currState = REPLY_STATUS;
            return ParseLine(_reply.begin());
            
        // Error message
        case '-':
            _currState = REPLY_ERROR;
            return ParseLine(_reply.begin());

        // Integer number    
        case ':':
            _currState = REPLY_INTEGER;
            return ParseLine(_reply.begin());
            
        // Bulk reply
        case '$':
            _currState = REPLY_STRING;
            return ParseBulk(_reply.begin());
            
        // Multi-bulk reply
        case '*':
            _currState = REPLY_ARRAY;
            return ParseMultiBulk(_reply.begin());
            
        default:
            //"Protocol error, got %s as reply type byte"
            std::cout << "Unknown reply" << std::endl;
    };
    
    return RerplyPtr();
}

RerplyPtr ReplyParser::ParseLine(ReceiveBufferIter iter)
{
    int begin = _cursor;
    while(_cursor <= _bytesRecvd)
    {
        if(_reply[_cursor] == '\r' && _reply[_cursor +1] == '\n')
        {
            int len = _cursor - begin;
            char* ret = new char[len];
            memcpy(ret, _reply.data() + begin, len);
            _cursor += len + 2;
            return  RerplyPtr(ret);
        }
        
        _cursor++;
    }
    
    return RerplyPtr();
}

RerplyPtr ReplyParser::ParseBulk(ReceiveBufferIter iter)
{
    // $6\r\nfoobar\r\n
    
    long long len = ReadLongLong(_reply.data() + _cursor);
    _cursor += 3;
    if(len < 0) {
        return RerplyPtr(new char[1]{'\0'} );
    }
    else {
        char* ret = new char[len];
        memcpy(ret, _reply.data() + _cursor, len);
        _cursor += (len + 2);
        return  RerplyPtr(ret);
    }
    
    return RerplyPtr();
}

RerplyPtr ReplyParser::ParseMultiBulk(ReceiveBufferIter iter)
{
    return RerplyPtr();
}
    
}