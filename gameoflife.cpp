
#include "gameoflife.hpp"

 //ridefinizione operatori
bool operator==(World const& left, World const& right){
        return left.m_grid == right.m_grid;
    };
bool operator!=(World const& left, World const& right){
        return left.m_grid != right.m_grid;
    };
// construct a Grid of side x side Cells, all Dead
    World::World(int side)
    : m_side{side}, m_grid (side*side+1, Cell::Dead), m_rule (side*side*10, 0)  //uso di rule
    {Cell& last_cell = m_grid.back();
    last_cell= Cell::Inexistent;}
// restituisce la dimensione
    int World::side() const {
        return m_side;
    }
// get a const reference to the Cell at position (r,c)
    Cell const& World::cell(int r, int c) const{
        if (r>=0 && r<m_side+1 && c>=0 && c<m_side+1) {
        return m_grid[r*m_side+c];
        }
        else return m_grid.back();
    };
// get a mutable reference to the Cell at position (r,c)
    Cell& World::cell(int r, int c) {
        if (r>=0 && r<m_side+1 && c>=0 && c<m_side+1) {
        return m_grid[r*m_side+c];
        }
        else return m_grid.back();
    };
// stampa la griglia
void World::print() {
        int N = m_side;
 for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
        if (m_grid[i*m_side+j]==Cell::Alive && j==N-1)
        {std::cout<<" +"<<std::endl;}
        else {
            if (m_grid[i*m_side+j]==Cell::Alive) {std::cout<<" +  ";}
            else {
                if (m_grid[i*m_side+j]==Cell::Dead && j==N-1) {
                    std::cout<<" x"<<std::endl;
                }
                else {
                    if (m_grid[i*m_side+j]==Cell::Dead) {std::cout<<" x  ";}
                    else {
                        if (m_grid[i*m_side+j]==Cell::Recovered && j==N-1) 
                        {std::cout<<" *  "<<std::endl;}
                        else {
                            if (m_grid[i*m_side+j]==Cell::Recovered) {std::cout<<" *  ";}
                            else {
                                if (j==N-1) {std::cout<<"    "<<std::endl;}
                                else {std::cout<<"    ";}
                        }
                    }
                }
            } 
        }
    }
  }
}};



// crea vincoli ovvero cell inexistent per ora a croce a x e random!
void World::set_constrains(std::string a){
    int rnd_n = std::rand() % (m_side*m_side);
    int rnd_r;
    int rnd_c;
    if (a=="x") {
        for (int i=0; i<m_side; i++) {
            m_grid[i+m_side*i]= Cell::Inexistent;
            m_grid[m_side+m_side*i] = Cell::Inexistent;
        }}

else {
    if (a=="+" && ((m_side % 2)==0)) {
        for (int i=0; i<m_side; i++) {
        m_grid[i+((m_side-1)/2)*m_side]= Cell::Inexistent;
        m_grid[i+((m_side+1)/2)*m_side]= Cell::Inexistent;
        m_grid[((m_side-1)/2)+m_side*i]= Cell::Inexistent;
        m_grid[((m_side+1)/2)+m_side*i]= Cell::Inexistent;
    }}

else {
    if  (a=="+") {
        for (int i=0; i<m_side; i++) {
        m_grid[i+(m_side/2)*m_side]= Cell::Inexistent;
        m_grid[(m_side/2)+m_side*i]= Cell::Inexistent;
    }}
 else {
    if (a=="random") {
        for (int i=0; i<rnd_n; i++) {
            rnd_r = rand() % m_side;
            rnd_c = rand() % m_side;
            m_grid[rnd_r+m_side*rnd_c]= Cell::Inexistent;
    }}


}}}
// versione con grid
};
void World::set_grid(Grid a) {
int N = m_side;
for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) { 
    if (a[i*N+j]==Cell::Inexistent){    
        m_grid[i*N+j]=Cell::Inexistent;}
    else {
        if (a[i*N+j]==Cell::Recovered){    
        m_grid[i*N+j]=Cell::Recovered;}
    else {
        if (a[i*N+j]==Cell::Alive){    
        m_grid[i*N+j]=Cell::Alive;}

    }}}
    }
};



// estrae un grid con i vincoli 
Grid World::extract_constrains (){
int N = m_side;
Grid constrains (N*N+1, Cell::Dead);
for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
    if (m_grid[i*N+j]!=Cell::Inexistent) {
        constrains[i*N+j]=Cell::Dead;
      }
    }}  
return constrains;
};

// returna i 4 tipi SEIR
std::vector<int> World::get_SEIR (){
    std::vector<int> SEIR(4,0);
        int N = m_side;
        
 for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
        int count=0;
    count = m_grid[(i-1)*m_side+j]== Cell::Alive ? count+1 : count;
    count = m_grid[(i+1)*m_side+j]== Cell::Alive ? count+1 : count;
    count = m_grid[i*m_side+j+1]== Cell::Alive ? count+1 : count;
    count = m_grid[i*m_side+j-1]== Cell::Alive ? count+1 : count;
        if (m_grid[i*m_side+j]==Cell::Alive && (count==2 || count==3))
        {SEIR[1]+=1;}
        else {
            if (m_grid[i*m_side+j]==Cell::Dead) 
            {SEIR[2]+=1;}
            else {
                if (m_grid[i*m_side+j]==Cell::Recovered) 
                {SEIR[3]+=1;}
                else {
                  if (m_grid[i*m_side+j]==Cell::Alive) 
                 {SEIR[0]+=1;}  
                }
                }
            } 
        }
    }
return SEIR;
};
// tramite geometria possiamo definire chi sono le celle più vicine
//World evolve(World const& current, std::string geometria){
World evolve(World const& current, std::string geometry){
    int N= current.side();
World next{N};
if (geometry=="classic") {
 for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
    int count=0;
    count = current.cell(i-1,j)== Cell::Alive ? count+1 : count;
    count = current.cell(i+1,j)== Cell::Alive ? count+1 : count;
    count = current.cell(i,j+1)== Cell::Alive ? count+1 : count;
    count = current.cell(i,j-1)== Cell::Alive ? count+1 : count;

    //uso di rule
    next.m_rule[i*N*5+j*5+1]=i; next.m_rule[i*N*5+j*5+2]=j;
    next.m_rule[i*N*10+j*10+3]=i-1; next.m_rule[i*N*10+j*10+4]=j;
    next.m_rule[i*N*10+j*10+5]=i+1; next.m_rule[i*N*10+j*10+6]=j;
    next.m_rule[i*N*10+j*10+7]=i; next.m_rule[i*N*10+j*10+8]=j+1;
    next.m_rule[i*N*10+j*10+9]=i; next.m_rule[i*N*10+j*10+10]=j+1;

     if (current.cell(i,j)==Cell::Dead && count==3) {
        next.cell(i,j)=Cell::Alive;
      }
     else {
        if (current.cell(i,j)==Cell::Alive && count!=3 && count!=2) {
            next.cell(i,j)=Cell::Dead;
        }
        else {
            if (current.cell(i,j)!=Cell::Inexistent||current.cell(i,j)!=Cell::Dead) {
                next.cell(i,j)=Cell::Alive;
            }

        }
     }
    }
 }}
 else {
    if (geometry=="random") {
        for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
        int count=0;
        for (int k=0; k<5; k++) {
        int rnd_r = rand() % N;
        int rnd_c = rand() % N;
        //uso di rule
        next.m_rule[i*N*5+j*5+1+k]=rnd_r; next.m_rule[i*N*5+j*5+k+2]=rnd_c;
        count = current.cell(rnd_r,rnd_c)== Cell::Alive ? count+1 : count;}
     if (current.cell(i,j)==Cell::Dead && count==3) {
        next.cell(i,j)=Cell::Alive;
      }
     else {
        if (current.cell(i,j)==Cell::Alive && count!=3 && count!=2) {
            next.cell(i,j)=Cell::Dead;
        }
        else {
            if (current.cell(i,j)!=Cell::Inexistent||current.cell(i,j)!=Cell::Dead) {
                next.cell(i,j)=Cell::Alive;
            }
            }
     }}
     }
    }
  else {
    if(geometry=="total_random") {
        for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
        int count=0;
        int rnd= rand()% (N*N);
        for (int k=0; k<rnd; k++) {
        int rnd_r = rand() % N;
        int rnd_c = rand() % N;
        // uso di rule
        next.m_rule[i*N*5+j*5+1+k]=rnd_r; next.m_rule[i*N*5+j*5+k+2]=rnd_c;
        count = current.cell(rnd_r,rnd_c)== Cell::Alive ? count+1 : count;}
     if (current.cell(i,j)==Cell::Dead && count==3) {
        next.cell(i,j)=Cell::Alive;
      }
     else {
        if (current.cell(i,j)==Cell::Alive && count!=3 && count!=2) {
            next.cell(i,j)=Cell::Dead;
        }
        else {
            if (current.cell(i,j)!=Cell::Inexistent||current.cell(i,j)!=Cell::Dead) {
                next.cell(i,j)=Cell::Alive;
            }
            }
     }}}
    }
    else {
        if (geometry=="SEIR") {
 for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
    int count=0;
    count = current.cell(i-1,j)== Cell::Alive ? count+1 : count;
    count = current.cell(i+1,j)== Cell::Alive ? count+1 : count;
    count = current.cell(i,j+1)== Cell::Alive ? count+1 : count;
    count = current.cell(i,j-1)== Cell::Alive ? count+1 : count;

    //uso di rule
    next.m_rule[i*N*5+j*5+1]=i; next.m_rule[i*N*5+j*5+2]=j;
    next.m_rule[i*N*10+j*10+3]=i-1; next.m_rule[i*N*10+j*10+4]=j;
    next.m_rule[i*N*10+j*10+5]=i+1; next.m_rule[i*N*10+j*10+6]=j;
    next.m_rule[i*N*10+j*10+7]=i; next.m_rule[i*N*10+j*10+8]=j+1;
    next.m_rule[i*N*10+j*10+9]=i; next.m_rule[i*N*10+j*10+10]=j+1;

// MODIFICA IN RECOVERD
     if (current.cell(i,j)==Cell::Dead && count==3) {
        next.cell(i,j)=Cell::Recovered;
      }
     else {
        if (current.cell(i,j)==Cell::Alive && count!=3 && count!=2) {
            next.cell(i,j)=Cell::Dead;
        }
        else {
            if (current.cell(i,j)!=Cell::Inexistent||current.cell(i,j)!=Cell::Dead) {
                next.cell(i,j)=Cell::Alive;
            }

        }
     }
    }
        }
    }
  }
 }}
 return next;
};

/*int main() {
int N=0;
int M=0;
std::cout<<"Inserisci la dimensione della griglia"<<std::endl;
std::cin>>N;
World mondo1(N);
int ran = rand() % (N*N);
for (int j=0; j< ran+1; j++) {
    int r1 = rand() % N;
    int r2 = rand() % N;
    mondo1.cell(r1, r2)= Cell::Alive;
}
mondo1.print();

std::cout<<"Inserisci il numero di interazioni"<<std::endl;
std::cin>>M;
for (int i=0; i<M+1; i++) {
mondo1=evolve(mondo1);
}
mondo1.print();
return 0;
}  */ 