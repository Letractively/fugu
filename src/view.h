#ifndef __FUGU_VIEW_H__
#define __FUGU_VIEW_H__

#include "prerequisites.h"

namespace fugu {

class View
{
	friend class ViewFactory;

	public:
		View();
		virtual ~View();

		virtual void NotifiCreated();
		virtual void NotifiDestroyed();
		virtual void Process(QueryContextPtr ctx)=0;
};

class ViewFactory
{
	protected:			
		virtual View* CreateImpl(SessionPtr session)=0;
	public:
		virtual const std::string& Id() const=0;
		virtual ViewPtr Create(SessionPtr session);
};
}

#endif