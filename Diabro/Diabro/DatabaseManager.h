#pragma once
#include "sqlite3.h"

class DatabaseManager
{
public:
	DatabaseManager();
	~DatabaseManager();

private:
	sqlite3 *db;
};

