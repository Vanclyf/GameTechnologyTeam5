#ifndef BASE_ITEMMANAGER_H
#define BASE_ITEMMANAGER_H

#pragma once
#include "ItemContainer.h"

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

private:
	ItemContainer* _itemContainer;

	// item generator
	void readFromDB();
};

#endif