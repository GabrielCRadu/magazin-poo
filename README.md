# Gestiune Produse - Proiect POO, Echipa 9

Membri: Virtic Razvan, Radu Gabriel

Aplicatie de consola in C++ pentru gestionarea unei liste de produse. Proiectul foloseste mostenire, mostenire multipla cu baza virtuala, functii virtuale si o lista simplu inlantuita implementata manual.

## Structura claselor

- `Produs` - clasa de baza abstracta (ID, denumire, pret). Contine functia virtuala pura `afis()` si functia virtuala `pretFinal()`.
- `ProdusFizic` - adauga greutate, stoc si culoare. Pretul final include 10 lei transport.
- `ProdusDigital` - adauga dimensiune (GB) si format. Pretul final are o reducere de 10%.
- `ProdusHibrid` - mosteneste atat `ProdusFizic`, cat si `ProdusDigital`. `Produs` este mostenita virtual, ca sa existe o singura copie a datelor de baza (problema diamantului). Pretul final: reducere de 10% plus 10 lei transport.
- `ListaProduse` - lista simplu inlantuita de pointeri `Produs*`, cu operatii de adaugare, afisare, cautare si stergere dupa ID. Elibereaza memoria produselor la stergere si in destructor.

## Functionalitati

Meniul principal permite:

1. Adaugarea unui produs fizic
2. Adaugarea unui produs digital
3. Adaugarea unui produs hibrid
4. Afisarea tuturor produselor
5. Cautarea unui produs dupa ID
6. Stergerea unui produs dupa ID
0. Iesire

ID-urile trebuie sa fie unice. Citirea datelor este validata: valorile numerice invalide sau negative sunt respinse si se cere reintroducerea lor.

Constructorii si destructorii afiseaza un mesaj, pentru a se putea urmari ordinea apelurilor in ierarhie.

## Compilare si rulare

```
g++ -std=c++11 -Wall main.cpp -o produse
./produse
```
