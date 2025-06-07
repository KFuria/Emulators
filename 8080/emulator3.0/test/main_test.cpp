#include <gtest/gtest.h>

#include "logger.h"

int main(int argc, char** argv)
{

    std::shared_ptr<TLogger> logger = TLogger::getInstance();

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}