#ifndef __FUGU_BYTE_BUFFER__
#define __FUGU_BYTE_BUFFER__

#include <boost/cstdint.hpp>
#include <string>

namespace fugu {

static const int BYTE_BUFFER_DEFAULT_CAPACITY = 4096;
    
class ByteBuffer {
public:
    ByteBuffer(size_t capacity = BYTE_BUFFER_DEFAULT_CAPACITY);
    ByteBuffer(const char* bytes, size_t len);
    ByteBuffer(const char* bytes); // uses strlen
    ~ByteBuffer();

    const char* Data() const ;
    size_t Length() const ;
    size_t Capacity() const ;

    bool ReadUInt8(boost::uint8_t& val);
    bool ReadUInt16(boost::uint16_t& val);
    bool ReadUInt32(boost::uint32_t& val);
    bool ReadString(std::string& val, size_t len); // append to val
    bool ReadBytes(char* val, size_t len);

    void WriteUInt8(boost::uint8_t val);
    void WriteUInt16(boost::uint16_t val);
    void WriteUInt32(boost::uint32_t val);
    void WriteString(const std::string& val);
    void WriteBytes(const char* val, size_t len);

    void Resize(size_t size);
    void Shift(size_t size);
    void ResetMemory();

private:
    char* bytes_;
    size_t size_;
    size_t start_;
    size_t end_;
};

}

#endif