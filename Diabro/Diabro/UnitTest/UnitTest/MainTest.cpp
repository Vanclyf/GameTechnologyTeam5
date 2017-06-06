#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
#include "LevelManager.h"
#include "Player.h"



TEST_CASE("First test case")
{
	REQUIRE(LevelManager::testunit(2) == 3);
}

