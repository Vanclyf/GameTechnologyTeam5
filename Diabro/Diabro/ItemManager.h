#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#pragma once
#include "ItemContainer.h"
#include "ItemGenerator.h"

/// <summary>
/// The ItemManager class is responsible for initializing the
/// ItemContainer and ItemGenerator. 
/// All communication regarding items passes through this manager.
/// </summary>
class ItemManager {
public:
	ItemManager();
	~ItemManager();
	// properties for container + generator

	ItemContainer* getItemContianer() { return _itemContainer; }
	ItemGenerator* getItemGenerator() { return _itemGenerator; }

private:
	ItemContainer* _itemContainer;
	ItemGenerator* _itemGenerator;

	// item generator
	void readFromDB();
};

#endif