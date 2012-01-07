#ifndef __FUGU_DATABASE_H__
#define __FUGU_DATABASE_H__

#include "prerequisites.h"

namespace fugu {

typedef JsonModelStoragePtr ViewsPtr;

class Database : private boost::noncopyable
{
public:
	Database(ConfigPtr config);

public:
	ViewsPtr Views() const;

private:
	ViewsPtr _views;
};

}

#endif