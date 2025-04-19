#ifndef ZMOGUS_H
#define ZMOGUS_H
#include <string>

using std::string;

class Zmogus {
protected:
    string vardas;
    string pavarde;

public:
    virtual string getVardas() const = 0;
    virtual string getPavarde() const = 0;
    virtual void setVardas(const string &v) = 0;
    virtual void setPavarde(const string &p) = 0;

    // Virtual destructor
    virtual ~Zmogus() = default;
};
#endif //ZMOGUS_H
