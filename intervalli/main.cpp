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
        //caso speciale se non parte da 1
        if(prima){
            if(lista[i].inizio > 1){
                supp.inizio = 1;
                supp.fine = lista[i].inizio;
                gg = supp.fine - supp.inizio;
            }
            e = lista[i].fine;
            prima = false;
        } else {
            //sovrapposizione aggiorno
            if(e >= lista[i].inizio && lista[i].fine > e){
                //ERRORE: AGGIORNO SOLO QUANDO LISTA[I].FINE > E
                //altrimenti sono nel caso in cui la coppia è già compresa
                e = lista[i].fine;
            } else {
                //aggiorno l'item da restituire solo se maggiore
                //in questo modo sono safe se la lunghezza è uguale
                if(lista[i].inizio - e > gg){
                    supp.inizio = e;
                    supp.fine = lista[i].inizio;
                    gg = supp.fine - supp.inizio;
                    e = lista[i].fine;
                } else if (lista[i].inizio - e == gg)
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
