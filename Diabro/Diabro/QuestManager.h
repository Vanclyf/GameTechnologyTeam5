#ifndef QUEST_MANAGER_H
#define QUEST_MANAGER_H

#include "QuestContentManager.h"
#include "Action.h"

class QuestManager {
public:
	QuestContentManager* getQuestContentManager(void) { return _questContentManager; }

private:
	QuestContentManager* _questContentManager;

};

#endif