#include "queue.h"
#include <gtest/gtest.h>

// Typed Test Class
template <typename T>
class QueueTest : public ::testing::Test {
protected:
    Queue<T> q;
};

using TestTypes = ::testing::Types<int, double, std::string>;
TYPED_TEST_SUITE(QueueTest, TestTypes);

TYPED_TEST(QueueTest, EnqueueTest) {
    this->q.enqueue(TypeParam{});
    EXPECT_EQ(this->q.getSize(), 1);
}

TYPED_TEST(QueueTest, DequeueTest) {
    this->q.enqueue(TypeParam{});
    this->q.dequeue();
    EXPECT_TRUE(this->q.empty());
}

TYPED_TEST(QueueTest, PeekTest) {
    this->q.enqueue(TypeParam{});
    EXPECT_NO_THROW(this->q.peek());
    EXPECT_EQ(this->q.getSize(), 1);
}

// Example usage
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}