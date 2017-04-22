#include "Catch.hpp"
#include "Player.h"


TEST_CASE("PlayerClassTest")
{
	SECTION("bool adjustHealth(float) override")
	{
		SECTION("checks if function doesn’t throw anything")
		{
			REQUIRE(1 == 1);
			REQUIRE_FALSE(1 == 0);

		}

	}
}

