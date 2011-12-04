#include "exception.h"
#include <iostream>
#include <sstream>

namespace fugu {

Exception::Exception(const std::string& desc, const std::string& src)
	:_line( 0 )
    ,_description(desc)
    ,_source(src)
{
}

Exception::Exception(const std::string& desc, const std::string& src, const char* file, long line)
	:_line(line)
	,_file(file)
    ,_description(desc)
    ,_source(src)
{
	//TODO: Log message
}

Exception::Exception(const Exception& rhs)
    : _line(rhs._line) 
	,_description(rhs._description)
	,_source(rhs._source)
	,_file(rhs._file)
{
}

void Exception::operator = ( const Exception& rhs )
{
    _description = rhs._description;
    _source = rhs._source;
    _file = rhs._file;
    _line = rhs._line;
}

const std::string& Exception::FullDescription() const
{
	if (_fullDesc.empty())
	{
		std::ostringstream builder;

		builder <<  "FUGU EXCEPTION: " << _description 
			<< " in " << _source;

		if( _line > 0 )
		{
			builder << " at " << _file << " (line " << _line << ")";
		}

		_fullDesc = builder.str();
	}

	return _fullDesc;
}

}

