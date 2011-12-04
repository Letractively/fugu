#include "controller.h"
#include <exception>


namespace fugu {

	Controller::Controller()
	{
	}

	Controller::~Controller()
	{
		//NotifiDestroyed();
	}

	void Controller::NotifiCreated()
	{
		//_view = ViewsCreator::Inst().Create(_factory->Id(), _session);
	}

	void Controller::NotifiDestroyed()
	{
		//TODO: delete all subcontrollers
	}

	ControllerPtr ControllerFactory::Create(SessionPtr session)
	{
		/*
		try
		{
			if(session->Login())
			{
				Controller* controller = CreateImpl(session);
				if(controller)
				{
					controller->_factory = this;
					controller->_session = session;
					controller->NotifiCreated();
				}
				return controller;
			}

			return NULL;
		}
		catch(std::exception ex)
		{
			ErrorLog() << "An exception occured while trying to create controller with name: '" << Id() << "' \t\r ";// ex.what();
		}
		*/
		return ControllerPtr();
	}

	bool ControllerFactory::HasRights(SessionPtr session)
	{
		return true;
	}
}

