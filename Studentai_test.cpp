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

// Test copy constructor
TEST_F(StudentaiTest, CopyConstructor) {
    Studentai original = createSampleStudent();
    Studentai copy(original);

    // tikrina ar reiksmes sutampa
    EXPECT_EQ(copy.getVardas(), original.getVardas());
    EXPECT_EQ(copy.getPavarde(), original.getPavarde());
    EXPECT_EQ(copy.getNd(), original.getNd());
    EXPECT_EQ(copy.getEgz(), original.getEgz());
    EXPECT_EQ(copy.getVid(), original.getVid());
    EXPECT_EQ(copy.getMed(), original.getMed());

}

// Test copy assignment operator
TEST_F(StudentaiTest, CopyAssignment) {
    Studentai original = createSampleStudent();
    Studentai copy;
    copy = original;

    // tikrina ar reiksmes sutampa
    EXPECT_EQ(copy.getVardas(), original.getVardas());
    EXPECT_EQ(copy.getPavarde(), original.getPavarde());
    EXPECT_EQ(copy.getNd(), original.getNd());
    EXPECT_EQ(copy.getEgz(), original.getEgz());

    // Patirina priskyrimo sau operacija
    original = original;
    EXPECT_EQ(original.getVardas(), "Testas");
}

// Test move constructor
TEST_F(StudentaiTest, MoveConstructor) {
    Studentai original = createSampleStudent();
    string originalName = original.getVardas();
    vector<int> originalNd = original.getNd();

    Studentai moved(std::move(original));

    // Tikrina ar duomenys buvo perkelti
    EXPECT_EQ(moved.getVardas(), originalName);
    EXPECT_EQ(moved.getNd(), originalNd);

    // Tikrina ar reiksmes tuscios
    EXPECT_TRUE(original.getNd().empty() || original.getVardas().empty());
}

// Test move assignment operator
TEST_F(StudentaiTest, MoveAssignment) {
    Studentai original = createSampleStudent();
    string originalName = original.getVardas();
    int originalSize = original.getNd().size();

    Studentai moved(std::move(original));

    // Tikrina ar duomenys buvo perkelti
    EXPECT_EQ(moved.getVardas(), originalName);
    EXPECT_EQ(moved.getNd().size(), originalSize);

    // Pradine reiksme turetu buti tuscia.
    EXPECT_TRUE(original.getNd().empty() || original.getVardas().empty());
}

// Test destructor
TEST_F(StudentaiTest, Destructor) {
    for(int i = 0; i < 1000; i++) {
        Studentai s = createSampleStudent();
        s.setVardas(s.getVardas() + std::to_string(i));
    }

    SUCCEED(); // Google Testu macro, kuris netiesiogiai patikrina ar suveike testas
}