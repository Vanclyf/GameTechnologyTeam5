#ifndef QUEST_ITEM_H
#define QUEST_ITEM_H

#pragma once
#include <OgrePrerequisites.h>
#include "BaseQuestItem.h"
#include "IQuestContent.h"

enum QuestItemQuality {
	NormalQI,
	MysticalQI,
	ValuableQI,

	AMOUNT_OF_QUEST_ITEM_QUALITIES
};

class QuestItem : public IQuestContent {
public:
	QuestItem(BaseQuestItem* pBaseItem, QuestItemQuality pQuality) : _info(pBaseItem), _quality(pQuality) {};
	~QuestItem();

	BaseQuestItem* getInfo() { return _info; }
	QuestItemQuality getQuality() { return _quality; }

private:
	BaseQuestItem* _info;
	QuestItemQuality _quality;

	//Quest _quest; or action?
};

#endif
