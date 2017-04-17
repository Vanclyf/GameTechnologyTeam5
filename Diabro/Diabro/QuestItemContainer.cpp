#include "QuestItemContainer.h"

QuestItemContainer::QuestItemContainer() {

}

QuestItemContainer::~QuestItemContainer() {
	for (int i = 0; i < _items.size(); ++i) {
		delete _items[i];
	}
}


int QuestItemContainer::itemAmount() {
	return _items.size();
}