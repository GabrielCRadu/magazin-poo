// POO - Proiect Echipa 9
// Membri: Virtic Razvan si Radu Gabriel

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

// ---------- Functii de citire ----------

int citesteInt(string mesaj) {
    int x;
    cout << mesaj;

    // cat timp nu s-a introdus un numar valid, cerem din nou
    while (!(cin >> x) || x < 0) {
        cout << "Valoare invalida! Reincearca: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cin.ignore(1000, '\n');   // sterge Enter-ul ramas dupa numar
    return x;
}

double citesteDouble(string mesaj) {
    double x;
    cout << mesaj;

    while (!(cin >> x) || x < 0) {
        cout << "Valoare invalida! Reincearca: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cin.ignore(1000, '\n');
    return x;
}

string citesteText(string mesaj) {
    string text;
    cout << mesaj;
    std::getline(cin, text);
    return text;
}

// ---------- Clasa de baza ----------

class Produs {
protected:
    int id_;
    string denumire_;
    double pret_;

    void afisComun() {
        cout << "ID: " << id_ << '\n';
        cout << "Denumire: " << denumire_ << '\n';
        cout << "Pret de baza: " << pret_ << " lei\n";
        cout << "Pret final: " << pretFinal() << " lei\n";
    }

public:
    Produs(int id, string denumire, double pret)
        : id_(id), denumire_(denumire), pret_(pret) {
        cout << "Constructor Produs\n";
    }

    virtual ~Produs() {
        cout << "Destructor Produs\n";
    }

    virtual void afis() = 0;   // functie virtuala pura

    virtual double pretFinal() {
        return pret_;
    }

    int id() {
        return id_;
    }
};

// ---------- Clase derivate ----------

class ProdusFizic : virtual public Produs {
protected:
    double greutate_;
    int stoc_;
    string culoare_;

public:
    ProdusFizic(int id, string denumire, double pret,
                double greutate, int stoc, string culoare)
        : Produs(id, denumire, pret),
          greutate_(greutate), stoc_(stoc), culoare_(culoare) {
        cout << "Constructor ProdusFizic\n";
    }

    ~ProdusFizic() override {
        cout << "Destructor ProdusFizic\n";
    }

    // pret + 10 lei transport
    double pretFinal() override {
        return pret_ + 10;
    }

    void afis() override {
        cout << "Tip: Fizic\n";
        afisComun();
        cout << "Greutate: " << greutate_ << " kg\n";
        cout << "Stoc: " << stoc_ << '\n';
        cout << "Culoare: " << culoare_ << '\n';
    }
};

class ProdusDigital : virtual public Produs {
protected:
    int dimensiune_;
    string format_;

public:
    ProdusDigital(int id, string denumire, double pret,
                  int dimensiune, string format)
        : Produs(id, denumire, pret),
          dimensiune_(dimensiune), format_(format) {
        cout << "Constructor ProdusDigital\n";
    }

    ~ProdusDigital() override {
        cout << "Destructor ProdusDigital\n";
    }

    // reducere de 10%
    double pretFinal() override {
        return pret_ * 0.9;
    }

    void afis() override {
        cout << "Tip: Digital\n";
        afisComun();
        cout << "Dimensiune: " << dimensiune_ << " GB\n";
        cout << "Format: " << format_ << '\n';
    }
};

// mostenire multipla: ProdusHibrid este si fizic, si digital
class ProdusHibrid : public ProdusFizic, public ProdusDigital {
public:
    // Produs este baza virtuala, deci se initializeaza aici
    ProdusHibrid(int id, string denumire, double pret,
                 double greutate, int stoc, string culoare,
                 int dimensiune, string format)
        : Produs(id, denumire, pret),
          ProdusFizic(id, denumire, pret, greutate, stoc, culoare),
          ProdusDigital(id, denumire, pret, dimensiune, format) {
        cout << "Constructor ProdusHibrid\n";
    }

    ~ProdusHibrid() override {
        cout << "Destructor ProdusHibrid\n";
    }

    // reducere de 10% + 10 lei transport
    double pretFinal() override {
        return pret_ * 0.9 + 10;
    }

    void afis() override {
        cout << "Tip: Hibrid\n";
        afisComun();
        cout << "Greutate: " << greutate_ << " kg\n";
        cout << "Stoc: " << stoc_ << '\n';
        cout << "Culoare: " << culoare_ << '\n';
        cout << "Dimensiune: " << dimensiune_ << " GB\n";
        cout << "Format: " << format_ << '\n';
    }
};

// ---------- Lista simplu inlantuita ----------

class ListaProduse {
    struct Nod {
        Produs* produs;
        Nod* urmator;
    };

    Nod* primul_ = nullptr;

public:
    ~ListaProduse() {
        while (primul_ != nullptr) {
            Nod* aux = primul_;
            primul_ = primul_->urmator;
            delete aux->produs;
            delete aux;
        }
    }

    void adauga(Produs* p) {
        Nod* nou = new Nod;
        nou->produs = p;
        nou->urmator = nullptr;

        if (primul_ == nullptr) {
            primul_ = nou;
            return;
        }

        Nod* q = primul_;
        while (q->urmator != nullptr) {
            q = q->urmator;
        }
        q->urmator = nou;
    }

    void afis() {
        if (primul_ == nullptr) {
            cout << "Lista este goala.\n";
            return;
        }

        Nod* q = primul_;
        while (q != nullptr) {
            cout << "--------------------\n";
            q->produs->afis();
            q = q->urmator;
        }
        cout << "--------------------\n";
    }

    // intoarce produsul gasit sau nullptr
    Produs* cauta(int id) {
        Nod* q = primul_;
        while (q != nullptr) {
            if (q->produs->id() == id) {
                return q->produs;
            }
            q = q->urmator;
        }
        return nullptr;
    }

    // intoarce true daca produsul a fost sters
    bool sterge(int id) {
        Nod* q = primul_;
        Nod* anterior = nullptr;

        while (q != nullptr) {
            if (q->produs->id() == id) {
                if (anterior == nullptr) {
                    primul_ = q->urmator;
                } else {
                    anterior->urmator = q->urmator;
                }

                delete q->produs;
                delete q;
                return true;
            }

            anterior = q;
            q = q->urmator;
        }
        return false;
    }
};

// ---------- Program principal ----------

int main() {
    ListaProduse lista;
    int optiune;

    do {
        cout << "\n===== GESTIUNE PRODUSE =====\n";
        cout << "1. Adauga produs fizic\n";
        cout << "2. Adauga produs digital\n";
        cout << "3. Adauga produs hibrid\n";
        cout << "4. Afiseaza produsele\n";
        cout << "5. Cauta produs dupa ID\n";
        cout << "6. Sterge produs dupa ID\n";
        cout << "0. Iesire\n";

        optiune = citesteInt("Optiune: ");

        if (optiune >= 1 && optiune <= 3) {
            int id = citesteInt("ID: ");

            if (lista.cauta(id) != nullptr) {
                cout << "Exista deja un produs cu acest ID!\n";
                continue;
            }

            string denumire = citesteText("Denumire: ");
            double pret = citesteDouble("Pret (lei): ");

            if (optiune == 1) {
                double greutate = citesteDouble("Greutate (kg): ");
                int stoc = citesteInt("Stoc: ");
                string culoare = citesteText("Culoare: ");

                lista.adauga(new ProdusFizic(id, denumire, pret,
                                             greutate, stoc, culoare));
            }
            else if (optiune == 2) {
                int dimensiune = citesteInt("Dimensiune (GB): ");
                string format = citesteText("Format fisier: ");

                lista.adauga(new ProdusDigital(id, denumire, pret,
                                               dimensiune, format));
            }
            else {
                double greutate = citesteDouble("Greutate (kg): ");
                int stoc = citesteInt("Stoc: ");
                string culoare = citesteText("Culoare: ");
                int dimensiune = citesteInt("Dimensiune (GB): ");
                string format = citesteText("Format fisier: ");

                lista.adauga(new ProdusHibrid(id, denumire, pret,
                                              greutate, stoc, culoare,
                                              dimensiune, format));
            }

            cout << "Produs adaugat!\n";
        }
        else if (optiune == 4) {
            lista.afis();
        }
        else if (optiune == 5) {
            int id = citesteInt("ID-ul cautat: ");
            Produs* p = lista.cauta(id);

            if (p != nullptr) {
                p->afis();
            } else {
                cout << "Produsul nu a fost gasit!\n";
            }
        }
        else if (optiune == 6) {
            int id = citesteInt("ID-ul de sters: ");

            if (lista.sterge(id)) {
                cout << "Produs sters!\n";
            } else {
                cout << "Produsul nu a fost gasit!\n";
            }
        }
        else if (optiune != 0) {
            cout << "Optiune invalida!\n";
        }

    } while (optiune != 0);

    cout << "Program incheiat.\n";
    return 0;
}