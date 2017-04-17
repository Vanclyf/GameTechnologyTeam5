#include "ItemContainer.h"
ItemContainer::ItemContainer() {
	
}

ItemContainer::~ItemContainer() {
	for(int i = 0; i < _weapons.size(); ++i) {
		delete _weapons[i];
	}
}


int ItemContainer::itemAmount() {
	return _weapons.size();
}