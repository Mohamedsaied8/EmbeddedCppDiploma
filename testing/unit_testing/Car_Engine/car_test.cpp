#include <gtest/gtest.h>
#include "car.h"
#include "engine_mock.h"

class CarTest : public ::testing::Test {
protected:
    void SetUp() override {
        mockEngine = std::make_unique<MockEngine>();
    }

    std::unique_ptr<MockEngine> mockEngine;
};

TEST_F(CarTest, Drive_StartsEngine) {
    EXPECT_CALL(*mockEngine, Start()).Times(1);
    Car testCar(std::move(mockEngine));
    testCar.Drive();
}

TEST_F(CarTest, Stop_StopsEngine) {
    EXPECT_CALL(*mockEngine, Stop()).Times(1);
    Car testCar(std::move(mockEngine));
    testCar.Stop();
}

TEST_F(CarTest, DriveAndStop_StartsAndStopsEngine) {
    EXPECT_CALL(*mockEngine, Start()).Times(1);
    EXPECT_CALL(*mockEngine, Stop()).Times(1);
    Car testCar(std::move(mockEngine));
    testCar.Drive();
    testCar.Stop();
}