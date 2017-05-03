#include "DatabaseManager.h"
#include "sqlite3.h"

#include<iostream>



DatabaseManager::DatabaseManager()
{
	int rc;

	rc = sqlite3_open("test.db", &db);

	if (rc){
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
		fclose(fp);
#endif
		return;
	}
	else{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("Opened database successfully\n");
		fclose(fp);
#endif
	}
}


DatabaseManager::~DatabaseManager()
{
	sqlite3_close(db);
}
