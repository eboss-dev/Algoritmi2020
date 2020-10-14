#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
//DICHIARAZIONE VARIABILI
int N;

struct Days {
    long long int inizio;
    long long int fine;
};

bool compareDays (Days a, Days b) {
    return a.inizio < b.inizio;
}

int main(){

    ifstream in ("input.txt");
    in>>N;
    Days lista [N];
    //cout<<N<<endl;
    for(int i = 0; i < N; i++){
        in>>lista[i].inizio;
        in>>lista[i].fine;
    }


    sort(lista, lista+N, compareDays);
    for(int i = 0; i < N; i++){
        cout<<lista[i].inizio<<" ";
        cout<<lista[i].fine;
        cout<<endl;
    }
    Days supp;
    supp.inizio = -1;
    long long int e;
    long long int gg = 0;
    bool prima = true;
    for(int i = 0; i < N; i++){
        //primo caso e verifica se non parte da 1
        if(prima){
            if(lista[i].inizio > 1){
                supp.inizio = 1;
                supp.fine = lista[i].inizio;
                gg = supp.fine - supp.inizio;
            }
            e = lista[i].fine;
            prima = false;
        } else {
            //OVERLAP
            if(lista[i].inizio <= e){
                //ERRORE: AGGIORNO SOLO QUANDO LISTA[I].FINE > E
                //altrimenti sono nel caso in cui la coppia è già compresa
                //CASO 1: la fine della coppia è più grande dell'end -> sostituisco
                if (lista[i].fine > e)
                    e = lista[i].fine;
                //CASO 2: la fine della coppia è più piccolo quindi è compreso
                //-----> non serve aggiornamento
            } else { //NO OVERLAP -> ho quindi spazi vuoti
                //aggiorno l'item da restituire solo se strettamente maggiore
                //in questo modo sono safe se la lunghezza è uguale
                if(lista[i].inizio - e > gg){
                    supp.inizio = e;
                    supp.fine = lista[i].inizio;
                    gg = supp.fine - supp.inizio;
                }
                e = lista[i].fine;

            }
        }
    }

    ofstream out("output.txt");
    if(supp.inizio == -1){
        out<<"0";
    } else {
        out<<supp.inizio<<" "<<supp.fine;
    }




    return 0;
}
