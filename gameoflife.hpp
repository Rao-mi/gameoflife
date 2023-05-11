#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdlib>

enum class Cell {Dead, Alive, Inexistent, Recovered}; // si potrebbe aggiungere recovered
using Grid = std::vector<Cell>;
using Rule = std::vector<int>;

class World {
//useremo per efficienza un unico vettore i=rxN+c
    int m_side;
    Grid m_grid;
//ridefinizione operatori
friend bool operator==(World const& left, World const& right);
friend bool operator!=(World const& left, World const& right);
    public:
/*indicatore della geometria con cui è stato creato l'inizio è 0 per default, altrimenti, 
si hanno 10 int per cella che indicano in ordine le celle i_0-j_0;i_1-j_1;i_2 
con i_0-j_0 cella che muta e 1,2,3,4 celle che definiscono la mutazione
quindi guardando i*N*10+j*10+k;i*N*10+j*10+k+1 con -1<k<5 troviamo i due interi che definiscono la cella
interagente (4 possibilità)*/ 
    Rule m_rule;
// construct a Grid of side x side Cells, all Dead
    World(int side);
// get a const reference to the Cell at position (r,c)
    Cell const& cell(int r, int c) const;
// get a mutable reference to the Cell at position (r,c)
    Cell& cell(int r, int c);
// stampa la griglia
    void print();
// returna la dimensione
    int side() const;
/* crea vincoli ovvero cell inexistent
x: occupa le diagonali
+: occupa le due linee a croce nella matrice
random: genera vincoli casuali*/
    void set_constrains(std::string a);
// setta vincoli, recovered e alive tramite grid    
    void set_grid (Grid a);  
// returna una griglia dei soli costrains e dead in tutte gli altri casi
    Grid extract_constrains ();
// returna il numero dei 4 tipi in ordine S-E-I-R, in un vector di interi
    std::vector<int> get_SEIR ();
};




/*tramite geometria possiamo definire chi sono le celle più vicine, si ha geometria
classic: per conway
SEIR: per l'implementazione (recovered),
random: ovvero i 4 primi vicini sono casuali
total random: sia il numero che la posizione dei primi vicini è randomica
*/
World evolve(World const& current, std::string geometria);

#endif