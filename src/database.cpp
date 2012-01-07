#include "database.h"
#include "config.h"
#include "jsonmodel.h"

namespace fugu {

Database::Database(ConfigPtr config)
	:_views(new JsonModelStorage(config->ViewsTable(), "Name"))
{
}

ViewsPtr Database::Views() const
{
	return _views;
}


}