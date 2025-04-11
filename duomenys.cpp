#include "duomenys.h"
#include "saugojimas_masyve.h"

std::unordered_map<int, string> umap;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Getters
string Studentai::getVardas() const { return vardas; }
string Studentai::getPavarde() const { return pavarde; }
vector<int> Studentai::getNd() const { return nd; }
int Studentai::getEgz() const { return egz; }
double Studentai::getVid() const { return vid; }
double Studentai::getMed() const { return med; }

// Setters
void Studentai::setVardas(const string &v) { vardas = v; }
void Studentai::setPavarde(const string &p) { pavarde = p; }
void Studentai::setNd(const vector<int> &n) { nd = n; }
void Studentai::addNd(int n) { nd.push_back(n); }
void Studentai::setEgz(int e) { egz = e; }
void Studentai::setVid(double v) { vid = v; }
void Studentai::setMed(double m) { med = m; }
void Studentai::setReserveNd(int n) { nd.reserve(n); }

//Destruktor

Studentai::~Studentai(){
    vardas=" ";
    pavarde=" ";
    egz=0;
    nd=0;
    vid=0;
    med=0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Container>
void readas(const string &filename, Container &studentai) {
    ifstream in(filename);
    string line;
    getline(in, line); // Skip header
    studentai.reserve(10000000);
    while (getline(in, line)) {
        stringstream iss(line);
        string vardas, pavarde;
        Studentai studentai_klase;
        iss >> vardas >> pavarde;
        studentai_klase.setVardas(vardas);
        studentai_klase.setPavarde(pavarde);

        vector<int> nd;
        int paz;
        while (iss >> paz) {
            if (paz >= 0 && paz <= 10) nd.push_back(paz);
        }

        studentai_klase.setNd(vector<int>(nd.begin(), nd.end() - 1));
        studentai_klase.setEgz(nd.back());
        studentai_klase.setVid(galutinis_vid(studentai_klase.getNd(), studentai_klase.getEgz()));
        studentai_klase.setMed(galutinis_med(studentai_klase.getNd(), studentai_klase.getEgz()));

        studentai.push_back(move(studentai_klase));
    }
    cout << "read- baigta\n";
    in.close();
}

template<typename Container>
double dalina(Container &studentai, Container &blogis) {
    auto start = chrono::high_resolution_clock::now();
    stable_sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
        return a.getVid() < b.getVid();
    });
    auto end = chrono::high_resolution_clock::now();
    auto it = find_if(studentai.begin(), studentai.end(), [](const Studentai &student) {
        return student.getVid() >= 5;
    });

    blogis.insert(blogis.end(), make_move_iterator(studentai.begin()), make_move_iterator(it));
    studentai.erase(studentai.begin(), it);
    cout << "dalina - baigta\n";
    return chrono::duration<double>(end - start).count();
}

template<typename Container>
void sortass(Container &studentai) {
    cout << "Pasirinkite pagal ka norite rusiuoti studentus: \n"
         << "1. Pagal varda \n"
         << "2. Pagal pavarde \n"
         << "3. Pagal galutini bala (vidurkis) \n"
         << "4. Pagal galutini bala (mediana) \n";
    try {
        int pasirinkimas;
        cin >> pasirinkimas;
        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 4) {
            throw invalid_argument("Neteisingas ivestis.");
        }

        switch (pasirinkimas) {
            case 1:
                stable_sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getVardas() < b.getVardas();
                });
            break;
            case 2:
                stable_sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getPavarde() < b.getPavarde();
                });
            break;
            case 3:
                stable_sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getVid() > b.getVid();
                });
            break;
            case 4:
                stable_sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getMed() > b.getMed();
                });
            break;
        }
    } catch (const exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}

template<typename Container>
void write_to_file(const string &filename, const Container &studentai) {
    ofstream out(filename);
    out << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    out << "------------------------------------------------------------" << endl;
    for (const auto &student: studentai) {
        out << setw(20) << left << student.getVardas() << " " << setw(20) << left << student.getPavarde() << " " << setw(20) <<
                left << fixed << setprecision(2) << student.getVid() << setw(20) << left << fixed << setprecision(2) <<
                student.getMed() << "\n";
    }
    cout << "write - baigta\n";
    out.close();
}

template<typename Container>
void split_into_two_containers(const Container& studentai, Container& vargsiukai, Container& kietiakai) {
    for (const auto& student : studentai) {
        if (student.getVid() < 5) vargsiukai.push_back(student);
        else kietiakai.push_back(student);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void meniu(vector<Studentai> &studentai) {
    try {
        int a;
        cout << "norint ivesti duomenis ranka, iveskite 1. \n"
                << "norint sugeneruoti pazymius, iveskite 2. \n"
                << "norint sugeneruotus pazymius ir vardus, iveskite 3. \n"
                << "norint nuskaityti vardus is failo, iveskite 4. \n"
                << "norint sugeneruoti arba atlikti tyrimus su duomenimis spauskite 5. \n"
                << "norint baigti darba, iveskite 6.";
        cin >> a;
        if (cin.fail() || a < 1 || a > 6) {
            throw invalid_argument("Neteisingas ivestis.");
        }
        string path;
        switch (a) {
            case 1:
                ivedimas();
                write1();
                break;
            case 2:
                generuoti_paz_ranka(studentai);
                write(studentai);
                break;
            case 3:
                generuoti_vard(studentai, 2, 0);
                write(studentai);
                break;
            case 4: {
                int pasirinkimas;
                cout << "pasirinkite kuri faila norite nuskaityti: \n"
                        << "1. studentai10000.txt \n"
                        << "2. studentai100000.txt \n"
                        << "3. studentai1000000.txt \n";
                cin >> pasirinkimas;
                if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 3) {
                    throw invalid_argument("Neteisingas ivestis.");
                }
                try {
                    switch (pasirinkimas) {
                        case 1:
                            read(test_file_location + "studentai10000.txt", studentai);
                            break;
                        case 2:
                            read(test_file_location + "studentai100000.txt", studentai);
                            break;
                        case 3:
                            read(test_file_location + "studentai1000000.txt", studentai);
                            break;
                        default:
                            cout << "Neteisingas pasirinkimas." << endl;
                            break;
                    }
                } catch (const exception &e) {
                }
                if (studentai.empty()) {
                    cout << "Nepavyko nuskaityti failo." << endl;
                } else {
                    sortas(studentai);
                    ss_write(test_file_location + "kursiokai.txt", studentai);
                }
                break;
            }
            case 5: {
                umap[1] = test_file_location + "tyrimas_studentai1000";
                umap[2] = test_file_location + "tyrimas_studentai10000";
                umap[3] = test_file_location + "tyrimas_studentai100000";
                umap[4] = test_file_location + "tyrimas_studentai1000000";
                umap[5] = test_file_location + "tyrimas_studentai10000000";
                int pasirinkimas1;
                cout << "1. sugeneruoti failus." << endl
                        << "2. tirti failus" << endl;
                try {
                    cin >> pasirinkimas1;
                } catch (exception &e) {
                    cout << "Klaida: " << e.what() << endl;
                }

                switch (pasirinkimas1) {
                    case 1: {
                        int paz_sk;
                        cout << "Iveskite pazymiu skaiciu: ";
                        cin >> paz_sk;
                        if (cin.fail() || paz_sk < 2) {
                            throw invalid_argument("Neteisingas ivestis.");
                        }
                        auto start = chrono::high_resolution_clock::now();
                        make_file(studentai, test_file_location + "tyrimas_studentai1000.txt", 1000, paz_sk);
                        make_file(studentai, test_file_location + "tyrimas_studentai10000.txt", 10000,
                                  paz_sk);
                        make_file(studentai, test_file_location + "tyrimas_studentai100000.txt", 100000,
                                  paz_sk);
                        make_file(studentai, test_file_location + "tyrimas_studentai1000000.txt",
                                  1000000, paz_sk);
                        make_file(studentai, test_file_location + "tyrimas_studentai10000000.txt",
                                  10000000, paz_sk);
                        auto end = chrono::high_resolution_clock::now();
                        chrono::duration<double> duration = end - start;
                        cout << "laikas, kuri uztruko sugeneruoti visus duomenis: " << duration.count() << " seconds."
                                << endl;
                        break;
                    }
                    case 2: {
                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        double sorto_laikas = 0;
                        cout << "Pasirinkite konteinerio tipa: \n"
                                << "1. std::vector \n"
                                << "2. std::list \n"
                                << "3. std::deque \n";
                        int pasirinkimas;
                        cin >> pasirinkimas;
                        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 3) {
                            throw invalid_argument("Neteisinga ivestis.");
                            break;
                        }

                        using ContainerType = vector<Studentai>;
                        if (pasirinkimas == 1) using ContainerType = std::vector<Studentai>;
                        else if (pasirinkimas == 2) using ContainerType = std::list<Studentai>;
                        else if (pasirinkimas == 3) using ContainerType = std::deque<Studentai>;
                        else cout << "Neteisingas pasirinkimas." << endl;
                        ContainerType studentai;
                        ContainerType blogis;
                        ContainerType kietiakai;

                        // cout << "pasirinkite, kuria strategija norite naudoti: \n"
                        //         << "1 Strategija \n"
                        //         << "2 Strategija \n"
                        //         << "3 Strategija \n";
                        int strategija=2;
                        //cin >> strategija;
                        if (cin.fail() || strategija < 1 || strategija > 3) {
                            throw invalid_argument("Neteisinga ivestis.");

                        }

                        cout << "Pasirinkite kuri faila norite nuskaityti: \n"
                                << "1. studentai1000.txt \n"
                                << "2. studentai10000.txt \n"
                                << "3. studentai100000.txt \n"
                                << "4. studentai1000000.txt \n"
                                << "5. studentai10000000.txt \n";
                        cin >> pasirinkimas1;
                        if (cin.fail() || pasirinkimas1 < 1 || pasirinkimas1 > 5) {
                            throw invalid_argument("Neteisingas ivestis.");
                        }
                        // if (pasirinkimas1 > 5 || pasirinkimas1 < 1 || !umap.count(pasirinkimas1) + ".txt") {
                        //     throw invalid_argument("Failas " + umap[pasirinkimas1] + ".txt nerastas.");
                        // }
                        auto nuskaitymas_pradzia = chrono::high_resolution_clock::now();
                        readas(umap[pasirinkimas1] + ".txt", studentai);
                        auto nuskaitymas_pabaiga = chrono::high_resolution_clock::now();
                        ////////////////////////////////////////////////////////////////////////////////////
                        auto dalinimo_pradzia = chrono::high_resolution_clock::now();
                        switch (strategija) {
                            case 1:
                                split_into_two_containers(studentai, blogis, kietiakai);
                                break;

                            case 2: {
                                sorto_laikas = dalina(studentai, blogis);
                                break;
                            }
                            case 3: {
                                sorto_laikas = dalina(studentai, blogis);
                                break;
                            }
                            default: {
                                cout << "Neteisingas pasirinkimas." << endl;
                                break;
                            }
                        }


                        auto dalinimo_pabaiga = chrono::high_resolution_clock::now();

                        ////////////////////////////////////////////////////////////////////////////////////
                        cout << "Pazangus studentai: \n";

                        switch (strategija) {
                            case 1: {
                                sortass(kietiakai);
                                break;
                            }
                            case 2: {
                                sortass(studentai);
                                break;
                            }
                            case 3: {
                                sortass(studentai);
                                break;
                            }
                            default:
                                cout << "Neteisingas pasirinkimas." << endl;
                                break;
                        }

                        cout << "Nepazangus studentai: \n";
                        sortass(blogis);
                        switch (strategija) {
                            case 1: {
                                write_to_file(umap[pasirinkimas1] + "_stud_rez.txt", kietiakai);
                                write_to_file(umap[pasirinkimas1] + "_blogi_rez.txt", blogis);
                                break;
                            }
                            case 2:
                                write_to_file(umap[pasirinkimas1] + "_stud_rez.txt", studentai);
                                write_to_file(umap[pasirinkimas1] + "_blogi_rez.txt", blogis);
                                break;
                            case 3:
                                write_to_file(umap[pasirinkimas1] + "_stud_rez.txt", studentai);
                                write_to_file(umap[pasirinkimas1] + "_blogi_rez.txt", blogis);
                                break;
                            default:
                                cout << "Neteisingas pasirinkimas." << endl;
                                break;
                        }

                        cout << "\n Nuskaitymo laikas: " << chrono::duration<double>(
                            nuskaitymas_pabaiga - nuskaitymas_pradzia).count() << "s" << endl;
                        cout << "\n rusiavimo didejimo tvarka laikas: " << sorto_laikas << "s" << endl;
                        cout << "\n dalinimo laikas: " << chrono::duration<double>(
                            dalinimo_pabaiga - dalinimo_pradzia).count() << "s" << endl;
                        cout << "\n Is viso laiko: " << chrono::duration<double>(
                            nuskaitymas_pabaiga - nuskaitymas_pradzia).count() + sorto_laikas + chrono::duration<
                            double>(
                            dalinimo_pabaiga - dalinimo_pradzia).count() << "s" << endl;
                        break;
                    }
                    default:
                        cout << "Neteisingas pasirinkimas." << endl;
                        break;
                }
            }
            case 6: {
                cout << "\nDarbas baigtas." << endl;
                break;
            }
            default:
                cout << "Neteisingas pasirinkimas." << endl;
                break;
        }
    } catch (const exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}

void galutinis_vid(vector<int> nd, int egz, vector<Studentai> &studentai) {
    // Calculate final grade using average
    Studentai student;
    double vid = 0;
    try {
        for (int i = 0; i < nd.size(); i++) {
            vid += nd[i];
        }
        vid = nd.empty() ? 0 : vid / nd.size();

        student.setVid(0.4 * vid + 0.6 * egz);
        studentai.push_back(student);
    } catch (const exception &e) {
        cerr << "Error calculating average: " << e.what() << endl;
    }
}

double galutinis_vid(vector<int> nd, int egz) {
    // skaiciuoja galutini bala pagal vidurki
    double vid = 0;
    try {
        for (int i = 0; i < nd.size(); i++) {
            vid += nd[i];
        }
        vid /= nd.size();
    } catch (const std::exception &e) {
        cerr << "Error calculating average: " << e.what() << endl;
    }
    return 0.4 * vid + 0.6 * egz;
}

void galutinis_med(vector<int> nd, int egz, vector<Studentai> &studentai) {
    // Calculate final grade using median
    Studentai student;
    sort(nd.begin(), nd.end());
    double med;
    if (nd.size() == 0) {
        med = 0;
    } else if (nd.size() % 2 == 0) {
        med = (nd[nd.size() / 2 - 1] + nd[nd.size() / 2]) / 2.0;
    } else {
        med = nd[nd.size() / 2];
    }
    student.setMed(0.4 * med + 0.6 * egz);
    studentai.push_back(student);
}

double galutinis_med(vector<int> nd, int egz) {
    // skaiciuoja galutini bala pagal mediana
    sort(nd.begin(), nd.end());
    double med;
    if (nd.size() == 0) {
        med = 0;
    } else if (nd.size() % 2 == 0) {
        med = (nd[nd.size() / 2 - 1] + nd[nd.size() / 2]) / 2.0;
    } else {
        med = nd[nd.size() / 2];
    }
    return 0.4 * med + 0.6 * egz;
}

void read(const string &filename, vector<Studentai> &studentai) {
    ifstream in(filename); // atidarymas is failo
    string line;
    getline(in, line);
    while (getline(in, line)) {
        stringstream iss(line);
        Studentai student;
        string vardas, pavarde;
        iss >> vardas >> pavarde;
        student.setVardas(vardas);
        student.setPavarde(pavarde);


        vector<int> nd;
        int paz;
        while (iss >> paz) {
            if (paz >= 0 && paz <= 10) nd.push_back(paz);
        }

        int egz = nd.back();
        nd.pop_back();

        student.setNd(nd);
        student.setEgz(egz);
        student.setVid(galutinis_vid(nd, egz));
        student.setMed(galutinis_med(nd, egz));

        studentai.push_back(student);
    }
    in.close(); //uzdaromas failas
}

void ss_write(const string &filename, vector<Studentai> &studentai) {
    ofstream out(filename);
    stringstream ss;
    ss << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    ss << "------------------------------------------------------------" << endl;
    for (const auto& student : studentai) {
        ss << setw(20) << left << student.getVardas() << setw(20) << left << student.getPavarde() << setw(20) <<
                left << fixed << setprecision(2) << student.getVid() << setw(20) <<
                left << fixed << setprecision(2) << student.getMed() << endl;
    }
    out << ss.str();
    out.close();
}

void write(vector<Studentai> &studentai) {
    // Output function
    cout << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde" << setw(20) << left <<
            "Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < studentai.size(); i++) {
        cout << setw(20) << left << studentai[i].getVardas() << setw(20) << left << studentai[i].getPavarde() << setw(20) <<
                left << fixed << setprecision(2) << studentai[i].getVid() << setw(20) << left <<
                fixed << setprecision(2) << studentai[i].getMed() << endl;
    }
}

void write_file(const string &filename, vector<Studentai> &studentai, int nd_skaicius) {
    ofstream out(filename);
    if (!out) {
        throw runtime_error("negalima atidaryti failo: " + filename);
    }
    stringstream ss;
    ss << setw(20) << left << "Vardas" << setw(20) << left << "Pavarde";
    for (int i = 1; i <= nd_skaicius - 1; i++) {
        ss << setw(20) << left << "ND" + to_string(i);
    }
    ss << setw(20) << left << "EGZAMINAS" << endl;
    while (!studentai.empty()) {
        for (auto& i : studentai) {
            ss << setw(20) << left << i.getVardas()
                    << setw(20) << left << i.getPavarde();
            for (auto k : i.getNd()) {
                ss << setw(20) << left << k;
            }
            ss << setw(20) << left << i.getEgz();
            ss << endl;
        }
        out << ss.str();
        studentai.erase(studentai.begin(), studentai.end());
    }

    out.close();
}

void make_file(vector<Studentai>& studentai, const string& filename, int mok_sk, int paz_sk) {
    generuoti_vard(studentai, paz_sk, mok_sk);
    write_file(filename, studentai, paz_sk);
}

void generuoti_paz(Studentai &student, int paz_sk) {
    while (paz_sk < 2) paz_sk = rand() % 10 + 1;
    vector<int> nd;
    for (int i = 0; i < paz_sk; i++) {
        int paz = rand() % 10 + 1;
        nd.push_back(paz);
    }
    int egz = nd.back();
    nd.pop_back();

    student.setNd(nd);
    student.setEgz(egz);
    student.setVid(galutinis_vid(nd, egz));
    student.setMed(galutinis_med(nd, egz));
}

void generuoti_paz_ranka(vector<Studentai> &studentai) {
    Studentai student;
    while (true) {
        try {
            cout << "Iveskite studento varda (iveskite 'p' norint uzbaigti): ";
            string vardas;
            cin >> vardas;
            if (vardas == "p") break;
            student.setVardas(vardas);

            cout << "Iveskite studento pavarde: ";
            string pavarde;
            cin >> pavarde;
            if (cin.fail()) {
                throw invalid_argument("Neteisingas ivestis.");
            }
            student.setPavarde(pavarde);

            int paz_sk = rand() % 10 + 1;
            generuoti_paz(student, paz_sk);
            studentai.push_back(student);
        } catch (const exception &e) {
            cout << "Klaida: " << e.what() << endl;
            cin.clear();
        }
    }
}

void generuoti_vard(vector<Studentai> &studentai, int paz_sk1, int mok_sk) {
    int vard_sk;
    if (mok_sk != 0) vard_sk = mok_sk;
    else vard_sk = rand() % 100 + 1;

    int paz_sk;
    if (paz_sk1 != 0) paz_sk = paz_sk1;
    else paz_sk = rand() % 10 + 1;

    for (int i = 0; i < vard_sk; i++) {
        Studentai student;
        string vardas = string(1, char(rand() % 26 + 65)) + ".";
        string pavarde = string(1, char(rand() % 26 + 65)) + ".";

        student.setVardas(vardas);
        student.setPavarde(pavarde);

        vector<int> nd;
        for (int j = 0; j < paz_sk - 1; j++) {
            nd.push_back(rand() % 10 + 1);
        }
        int egz = rand() % 10 + 1;

        student.setNd(nd);
        student.setEgz(egz);
        student.setVid(galutinis_vid(nd, egz));
        student.setMed(galutinis_med(nd, egz));

        studentai.push_back(student);
    }
}

void sortas(vector<Studentai> &studentai) {
    cout << "Pasirinkite pagal ka norite rusiuoti studentus: \n"
            << "1. Pagal varda \n"
            << "2. Pagal pavarde \n"
            << "3. Pagal galutini bala (vidurkis) \n"
            << "4. Pagal galutini bala (mediana) \n";
    try {
        int pasirinkimas;
        cin >> pasirinkimas;
        if (cin.fail() || pasirinkimas < 1 || pasirinkimas > 4) {
            throw invalid_argument("Neteisingas ivestis.");
        }

        switch (pasirinkimas) {
            case 1:
                sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getVardas() < b.getVardas();
                });
            break;
            case 2:
                sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getPavarde() < b.getPavarde();
                });
            break;
            case 3:
                sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getVid() > b.getVid();
                });
            break;
            case 4:
                sort(studentai.begin(), studentai.end(), [](const Studentai &a, const Studentai &b) {
                    return a.getMed() > b.getMed();
                });
            break;
        }
    } catch (const exception &e) {
        cout << "Klaida: " << e.what() << endl;
    }
}
