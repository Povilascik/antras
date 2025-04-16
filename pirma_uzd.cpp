#include "duomenys.h"
#include  "saugojimas_masyve.h"

vector<duomenys> studentai;

int main() {
    srand(time(nullptr));
    int a;
    try {
    cout << "norint ivesti duomenis ranka, iveskite 1. \n"
            << "norint sugeneruoti pazymius, iveskite 2. \n"
            << "norint sugeneruotus pazymius ir vardus, iveskite 3. \n"
            << "norint nuskaityti vardus is failo, iveskite 4. \n"
            << "norint baigti darba, iveskite 5.";
    cin >> a;
    if (cin.fail()) {
        throw std::invalid_argument("Neteisingas ivestis.");
    }
    string path;
    switch (a) {
        case 1:
            ivedimas();
            write1("C:/Users/PC/Documents/GitHub/pirmas/rez.txt");
            break;
        case 2:
            generuoti_paz_ranka(studentai);
            write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt", studentai);
            break;
        case 3:
            generuoti_vard(studentai);
            write("C:/Users/PC/Documents/GitHub/pirmas/rez.txt", studentai);
            break;
        case 4:
            string filePath;
            int pasirinkimas;
            cout << "pasirinkite kuri faila norite nuskaityti: \n"
                    << "1. studentai10000.txt \n"
                    << "2. studentai100000.txt \n"
                    << "3. studentai1000000.txt \n";
            cin >> pasirinkimas;
        if(pasirinkimas==1) filePath="C:/Users/PC/Desktop/oop/pirmas-0.3_tag/pirmas-0.3_tag/studentai10000.txt";
            else if(pasirinkimas==2) filePath="C:/Users/PC/Desktop/oop/pirmas-0.3_tag/pirmas-0.3_tag/studentai100000.txt";
            else if(pasirinkimas==3) filePath="C:/Users/PC/Desktop/oop/pirmas-0.3_tag/pirmas-0.3_tag/studentai1000000.txt";
            else {
                cout << "Neteisingas pasirinkimas." << endl;
                break;
            }
            ifstream fileCheck(filePath);
            if (!fileCheck.good()) {
                cout << "Klaida: failas " << filePath << " neegzistuoja arba nepasiekiamas." << endl;
                return 0;
            }
            switch (pasirinkimas) {
                case 1:
                    read(filePath, studentai);
                    break;
                case 2:
                    read(filePath, studentai);
                    break;
                case 3:
                    read(filePath, studentai);
                    break;
                default:
                    cout << "Neteisingas pasirinkimas." << endl;
                    break;
            }
            sortas(studentai);
            ss_write("C:/Users/PC/Documents/GitHub/pirmas/kursiokai.txt", studentai);
            break;
        case 5:
            cout << "Darbas baigtas." << endl;
            break;
        default:
            cout << "Neteisingas pasirinkimas." << endl;
            break;
    }
    } catch (const std::exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }

    return 0;
}
