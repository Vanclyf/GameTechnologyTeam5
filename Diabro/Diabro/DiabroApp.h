#include "AppStateManager.h"

class DiabroApp
{
public:
	DiabroApp();
	~DiabroApp();

	void startGame();

private:
	AppStateManager*		m_pAppStateManager;
};

