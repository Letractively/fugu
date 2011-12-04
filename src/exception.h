#ifndef __FUGU_EXCEPTION__
#define __FUGU_EXCEPTION__

#include <string>
#include <exception>

namespace fugu {

class Exception : public std::exception
{
public:
    Exception(const std::string& description, const std::string& source);
    Exception(const std::string& description, const std::string& source, const char* file, long line);
    // Copy constructor.
    Exception(const Exception& rhs);
	// Needed for  compatibility with std::exception
	~Exception() throw() {}
    // Assignment operator
    void operator = (const Exception& rhs);
    // Gets the _source function.
    virtual const std::string& Source() const { return _source; }
    // Gets _source _file name.
    virtual const std::string& File() const { return _file; }
    // Gets _line number.
    virtual long Line() const { return _line; }
	// Returns a string with only the '_description' field of this exception
	virtual const std::string& Description(void) const { return _description; }
    // Returns a string with the full _description of this error, 
    virtual const std::string& FullDescription(void) const;
	// Override std::exception::what
	const char* what() const throw() { return FullDescription().c_str(); }

protected:
	int _line;
	std::string _description;
	std::string _source;
	std::string _file;
	mutable std::string _fullDesc;
};

}

#ifndef FUGU_THROW
#define FUGU_THROW(desc, src) throw fugu::Exception(desc, src, __FILE__, __LINE__ );
#endif

#endif
