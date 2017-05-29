#include "ItemContainer.h"
ItemContainer::ItemContainer() {
	
}

ItemContainer::~ItemContainer() {
	for(int i = 0; i < _weapons.size(); ++i) {
		delete _weapons[i];
	}

	for (int i = 0; i < _armors.size(); ++i) {
		delete _armors[i];
	}
}


int ItemContainer::itemAmount() {
	return _armors.size();
}