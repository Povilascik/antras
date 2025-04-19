#ifndef DUOMENYS_H
#define DUOMENYS_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <ctime>
#include <unordered_map>
#include <chrono>
#include <list>
#include <deque>
#include <fstream>
#include <cwchar>
#include <sstream>
#include "zmogus.h"

const std::string test_file_location = TEST_FILE_LOCATION;      // skirtas naudoti SU CMake
// const std::string test_file_location = "";                   // skirtas naudoti BE CMake

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::string;
using std::vector;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::time;
using std::srand;
using std::rand;
//////////////////////////////////////////////////////////
///klases.

class Studentai {
private:
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
    double vid;
    double med;

public:
    // Default constructor
    Studentai() : egz(0), vid(0), med(0) {}
    void Studentai::clear();
    // Rule of Five
    ~Studentai();
    Studentai(const Studentai& other); // Copy constructor
    Studentai& operator=(const Studentai& other); // Copy assignment
    Studentai(Studentai&& other) noexcept; // Move constructor
    Studentai& operator=(Studentai&& other) noexcept; // Move assignment

    // Operators
    friend std::ostream& operator<<(std::ostream& os, const Studentai& student);
    friend std::ifstream& operator>>(std::ifstream& in, Studentai& student);

    // Getters
    string getVardas() const;
    string getPavarde() const;
    vector<int> getNd() const;
    int getEgz() const;
    double getVid() const;
    double getMed() const;

    // Setters
    void setVardas(const string &v);
    void setPavarde(const string &p);
    void setNd(const vector<int> &n);
    void addNd(int n);
    void setEgz(int e);
    void setVid(double v);
    void setMed(double m);
    void setReserveNd(int n);
};




//////////////////////////////////////////////////////////


void meniu(vector<Studentai> &studentai);

double galutinis_vid(vector<int> nd, int egz);

double galutinis_med(vector<int> nd, int egz);

void read(const string &filename, vector<Studentai> &studentai);

void ss_write(const string &filename, vector<Studentai> &studentai);

void write(vector<Studentai> &studentai);

void write_file(const std::string &filename, std::vector<Studentai> &studentai, int nd_skaicius);

void make_file(vector<Studentai>& studentai, const string& filename, int mok_sk, int paz_sk);

void generuoti_paz(Studentai &student, int paz_sk);

void generuoti_paz_ranka(vector<Studentai> &studentai);

void generuoti_vard(vector<Studentai> &studentai, int paz_sk1, int mok_sk);

void sortas(vector<Studentai> &studentai);

#endif //DUOMENYS_H
