#include "Catch.hpp"

#include "LevelGenerator.h"
#include "Zone.h"
#include "City.h"

TEST_CASE("level generator : city spaces", "[level-generation][cities]") {
	
	SECTION("city sizes") {
		GIVEN("a new zone is created")
		{
			Zone zone = Zone(9, 9, 3, 3, 2, 100);
			WHEN("maximum city size is 3")
			{
				THEN("no rooms exist with a size bigger than 3")
				{
					REQUIRE(zone.cities.size() > 0);
					int maxX = 0;
					int maxZ = 0;
					for (int i = 0; i < zone.cities.size(); ++i)
					{
						maxX = (maxX < zone.cities[i].width) ? zone.cities[i].width : maxX;
						maxZ = (maxZ < zone.cities[i].width) ? zone.cities[i].width : maxZ;
					}
					REQUIRE(maxX <= 3);
					REQUIRE(maxZ <= 3);
				}
			}
		}
	}
}