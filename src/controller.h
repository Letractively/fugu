#ifndef __FUGU_CONTROLER_H__
#define __FUGU_CONTROLER_H__

#include "prerequisites.h"

namespace fugu {

class Controller
{
	friend class ControllerFactory;

	public:
		Controller();
		virtual ~Controller();
		virtual ResponsePtr Process(QueryContextPtr ctx)=0;

	protected:
		virtual void NotifiCreated();
		virtual void NotifiDestroyed();

		ResponsePtr View();
		ResponsePtr PartialView();
		ResponsePtr Json(const std::string json);
		ResponsePtr Xml(const std::string json);
};

class ControllerFactory
{
	protected:			
		virtual Controller* CreateImpl(SessionPtr session)=0;
	public:
		virtual const std::string& Id() const=0;
		virtual ControllerPtr Create(SessionPtr session);
		static bool HasRights(SessionPtr Session);
};
}

#endif