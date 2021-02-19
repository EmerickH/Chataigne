/*
  ==============================================================================

    BaseCommandHandlerManagerUI.h
    Created: 2 Jan 2018 6:19:33pm
    Author:  Ben

  ==============================================================================
*/

#pragma once

#include "../BaseCommandHandler.h"
#include "../CommandFactory.h"

template <class T>
class BaseCommandHandlerManagerEditor :
	public GenericManagerEditor<T>
{
public:
	BaseCommandHandlerManagerEditor(BaseManager<T>* manager, CommandContext context, bool isRoot, bool multiplexMode) :
		GenericManagerEditor<T>(manager, isRoot),
		context(context),
		multiplexMode(multiplexMode)
	{

	}

	CommandContext context;
	bool multiplexMode;

	~BaseCommandHandlerManagerEditor() {}

	
	void showMenuAndAddItem(bool /*isFromAddButton*/) override
	{
		CommandDefinition * def = CommandFactory::showMenuAndGetCommand(context, nullptr, multiplexMode);
		if (def == nullptr) return;
		else
		{
			T * item = this->manager->createItem();
			BaseCommandHandler * c = dynamic_cast<BaseCommandHandler *>(item);
			c->setCommand(def);
			this->manager->addItem(item);
			this->setCollapsed(false, true);
		}
	}
};
