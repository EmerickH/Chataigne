/*
  ==============================================================================

    MIDIDeviceParameter.cpp
    Created: 20 Dec 2016 3:05:54pm
    Author:  Ben

  ==============================================================================
*/

#include "MIDIDeviceParameter.h"
#include "ui/MIDIDeviceParameterUI.h"

MIDIDeviceParameter::MIDIDeviceParameter(const String & name) :
	Parameter(CUSTOM, name, "MIDI Devices",var(), var(),var()),
	inputDevice(nullptr),
	outputDevice(nullptr)
{
	MIDIManager::getInstance()->addMIDIManagerListener(this);
	value.append("");
	value.append("");
}

MIDIDeviceParameter::~MIDIDeviceParameter()
{
	if (MIDIManager::getInstanceWithoutCreating() != nullptr)
	{
		MIDIManager::getInstance()->removeMIDIManagerListener(this);
	}
}



void MIDIDeviceParameter::setInputDevice(MIDIInputDevice * i)
{
	var val;
	val.append(i != nullptr ? i->name : "");
	val.append(value[1]);

	if(i != nullptr) ghostDeviceIn = value[0];

	inputDevice = i;

	setValue(val);
}

void MIDIDeviceParameter::setOutputDevice(MIDIOutputDevice * o)
{
	var val;
	val.append(value[0]);
	val.append(o != nullptr ? o->name : "");
	
	if(o != nullptr) ghostDeviceOut = val[1];

	outputDevice = o;

	setValue(val,false,true);
	
}

void MIDIDeviceParameter::midiDeviceInAdded(MIDIInputDevice * i)
{	
	DBG("Device In added " << i->name << " / " << ghostDeviceIn);
	if (inputDevice == nullptr && i->name == ghostDeviceIn)
	{
		setInputDevice(i);
	}
}

void MIDIDeviceParameter::midiDeviceOutAdded(MIDIOutputDevice * o)
{
	if (outputDevice == nullptr&& o->name == ghostDeviceOut)
	{
		setOutputDevice(o);
	}
}

void MIDIDeviceParameter::midiDeviceInRemoved(MIDIInputDevice * i)
{
	if (i == inputDevice)
	{
		if (i != nullptr)
		{
			ghostDeviceIn = i->name;
		}
		setInputDevice(nullptr);
	}
}

void MIDIDeviceParameter::midiDeviceOutRemoved(MIDIOutputDevice * o)
{
	if (o == outputDevice)
	{
		if(o != nullptr) ghostDeviceOut = o->name;
		setOutputDevice(nullptr);
	}
}


MIDIDeviceParameterUI * MIDIDeviceParameter::createMIDIParameterUI()
{
	return new MIDIDeviceParameterUI(this);
}

ControllableUI * MIDIDeviceParameter::createDefaultUI()
{
	return createMIDIParameterUI();
}

void MIDIDeviceParameter::loadJSONDataInternal(var data)
{
	Parameter::loadJSONDataInternal(data);
	setInputDevice(MIDIManager::getInstance()->getInputDeviceWithName(value[0]));

	if (inputDevice == nullptr) ghostDeviceIn = data.getProperty("value", var())[0];	

	setOutputDevice(MIDIManager::getInstance()->getOutputDeviceWithName(value[1]));

	if (outputDevice == nullptr) ghostDeviceOut = data.getProperty("value", var())[1];

}
