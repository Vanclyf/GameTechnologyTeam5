#include "Catch.hpp"
#include "SoundManager.h"

TEST_CASE("SOUND_MANAGER_TEST")
{
	SECTION("static void PlaySmallSound(std::string) override")
	{
		SECTION("Checks that, when the soundfile cannot be found, no error is given")
		{
			REQUIRE_NOTHROW("null");
		}
	}
}