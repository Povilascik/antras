#include "duomenys.h"
#include <gtest/gtest.h>

class StudentaiTest : public ::testing::Test {
protected:
    void SetUp() override {
         testNd = {8, 9, 7, 10, 6};
    }
    vector<int> testNd;

    Studentai createSampleStudent() {
        Studentai s;
        s.setVardas("Testas");
        s.setPavarde("Studentas");
        s.setNd(testNd);
        s.setEgz(9);
        s.setVid(8.5);
        s.setMed(8.0);
        return s;
    }
};

// Test default constructor
TEST_F(StudentaiTest, DefaultConstructor) {
    Studentai s;
    EXPECT_EQ(s.getVardas(), "");
    EXPECT_EQ(s.getPavarde(), "");
    EXPECT_TRUE(s.getNd().empty());
    EXPECT_EQ(s.getEgz(), 0);
    EXPECT_EQ(s.getVid(), 0.0);
    EXPECT_EQ(s.getMed(), 0.0);
}

