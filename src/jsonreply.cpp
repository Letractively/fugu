#include "jsonreply.h"

namespace fugu {

JsonReply::JsonReply()
	:_blockedError(false)
{
}

JsonReply::~JsonReply()
{
}

void JsonReply::SetError(const std::string& error, bool blocked)
{
	_error = error;
	_blockedError = blocked;
}

bool JsonReply::HadError() const
{
	return _error.empty() || _blockedError;
}

bool JsonReply::BlockedError() const
{
	return _blockedError;
}

}