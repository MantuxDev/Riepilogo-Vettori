/*
    Riepilogo vettori

    I vettori STUD,MATE e INFO delle 25 componenti contengono i nomi degli
    studenti di una classe e i loro voti di fine anno in matematicaa e informatica
    (I vettori sono già caricati)

    Facendo uso di sottoprogrammi:

    - a) visualizza la media della classe per le due materie
    - b) visualizza il nome e il voto degli studenti che hanno il voto di 
    informatica maggiore della media
    - c) visualizza il nome e il voto degli studenti che hanno il voto di matematica
    inferiore alla media
    - d) visualizza il nome dello studente che ha il voto più alto in informatica
    e dello studente col voto più alto in matematica
    - e) dato il nome in input il nome di uno studente stampare i suoi voti in 
    matematica e informatica, segnala se lo studente non esiste
    - f) visualizza quanti studenti hanno voto <6, quanti tra 6 e 7, e quanti > 8,
    ripeti il procedimento per i voti di informatica
*/


#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <cstdlib>

using namespace std;

//Colori    
#define BLUE    "\033[1m\033[34m"  /*Messaggi*/      
#define RED     "\033[1m\033[31m"  /*Errore o voti<50% di votoMax*/ 
#define YELLOW  "\033[1m\033[33m"  /*Attenzione o voti>50% && voti <60% di votoMax*/
#define GREEN   "\033[1m\033[32m"  /*Successo o voto>=60% di votoMax*/            
#define RESET   "\033[0m"

//Dichiarazione costanti 
const int votoMax=10;
const int votoMin=2;
const int dim=25;
const int lenght=20;

//Prototipi
int menu();
void caricaVoti(double materia[]);
double media(double materia[]);
void stampaVoti1(double materia[], double mediaClasse, string studenti[]);
void stampaVoti2(double materia[], double mediaClasse, string studenti[]);
int ricerca(string studenti[], double materia[]);
void cercaStudente(string studenti[], double informatica[], double matematica[]);
void voti(string studenti[], double materia[], int MinVoto, int MaxVoto,string color);
double calcolaVoto(int perc);
void stampaVoti(string studenti[],double materia[]);
void avanti();

int main(){
    //Dichiarazione variabili
    int s;
    double x,y;

    //Dichiarazione array
    string studenti[dim]={
        "Marco Rossi", "Chiara Bianchi", "Luca Romano", "Alessia Russo", "Giovanni Ferrari",
        "Elena Martini", "Matteo Conti", "Sofia Esposito", "Andrea De Luca", "Francesca Russo",
        "Davide Moretti", "Giulia Ferrari", "Antonio Rizzo", "Martina Colombo", "Stefano Greco",
        "Valentina Serra", "Roberto Caruso", "Federica Leone", "Luca De Santis", "Anna Galli",
        "Nicola Costa", "Laura Bruno", "Simone D'Angelo", "Sara Barone", "Alessando Monti"
    };

    double informatica[dim];
    double matematica[dim];

    //Inizializzazione seme 
    srand(time(nullptr)+votoMin);

    //Riempiamo i vettori dei voti
    caricaVoti(informatica);
    caricaVoti(matematica);

    do{
        system("cls");
        s=menu();

        switch(s){

            //Visualizza la media della classe per le due materie
            case 1:{
                x=media(informatica);
                y=media(matematica);

                cout<<BLUE<<"\nMedia informatica: "<<RESET<<x<<endl;
                cout<<BLUE<<"\nMedia matematica: "<<RESET<<y<<endl;

                avanti();
                break;
            }

            //Visualizza il nome e il voto degli studenti che hanno il voto di informatica maggiore della media
            case 2:{
                cout<<BLUE<<"\nStudenti con voto informatica maggiore della media: "<<RESET<<endl;
                stampaVoti1(informatica,x,studenti);
                avanti();
                break;
            }

            //Visualizza il nome e il voto degli studenti che hanno il voto di matematica inferiore alla media
            case 3:{
                cout<<BLUE<<"\nStudenti con voto matematica inferiore alla media: "<<RESET<<endl;
                stampaVoti2(matematica,y,studenti);
                avanti();
                break;
            }

            //Visualizza il nome dello studente che ha il voto più alto in informatica e dello studente col voto più alto in matematica
            case 4:{
                cout<<BLUE<<"\nStudente con voto informatica maggiore: "<<RESET<<studenti[ricerca(studenti,informatica)];
                cout<<BLUE<<"\nStudente con voto matematica maggiore: "<<RESET<<studenti[ricerca(studenti,matematica)];

                avanti();
                break;
            }

            //Dato il nome in input il nome di uno studente stampare i suoi voti in matematica e informatica, segnala se lo studente non esiste
            case 5:{
                cercaStudente(studenti,informatica,matematica);
                avanti();
                break;
            }

            //Stampa voti matematica
            case 6:{

                cout<<BLUE<<"Studenti con voto minore di "<<RESET<<calcolaVoto(60)<<BLUE<<" in matematica: "<<RESET<<endl;
                voti(studenti,matematica,votoMin,calcolaVoto(60),RED);

                cout<<endl;

                cout<<BLUE<<"Studenti con voto tra "<<RESET<<calcolaVoto(60)<<BLUE<<" e "<<RESET<<calcolaVoto(70)<<BLUE<<" in matematica: "<<RESET<<endl;
                voti(studenti,matematica,calcolaVoto(60),calcolaVoto(70),GREEN);

                cout<<endl;

                cout<<BLUE<<"Studenti con voto maggiore o uguale di "<<RESET<<calcolaVoto(80)<<BLUE<<" in matematica: "<<RESET<<endl;
                voti(studenti,matematica,calcolaVoto(80),votoMax,GREEN);
                break;
            }

            //Stampa voti informatica
            case 7:{

                cout<<BLUE<<"Studenti con voto minore di "<<RESET<<calcolaVoto(60)<<BLUE<<" in informatica: "<<RESET<<endl;
                voti(studenti,informatica,votoMin,calcolaVoto(60),RED);

                cout<<endl;

                cout<<BLUE<<"Studenti con voto tra "<<RESET<<calcolaVoto(60)<<BLUE<<" e "<<RESET<<calcolaVoto(70)<<BLUE<<" in informatica: "<<RESET<<endl;
                voti(studenti,informatica,calcolaVoto(60),calcolaVoto(70),GREEN);

                cout<<endl;

                cout<<BLUE<<"Studenti con voto maggiore o uguale di "<<RESET<<calcolaVoto(80)<<BLUE<<" in informatica: "<<RESET<<endl;
                voti(studenti,informatica,calcolaVoto(80),votoMax,GREEN);
                break;
            }

            //Stampa tutti i voti
            case 8:{
                cout<<BLUE<<"Voti informatica:"<<RESET<<endl;
                stampaVoti(studenti,informatica);

                cout<<endl;

                cout<<BLUE<<"Voti matematica:"<<RESET<<endl;
                stampaVoti(studenti,matematica);

                avanti();
                break;
            }

            case 0:{
                cout<<BLUE<<"\nArrivederci!"<<RESET<<endl;
                break;
            }

            default :{
                cout<<RED<<"\nScelta non valida!"<<RESET<<endl;
            }
        }
    }while(s!=0);

    return 0;
}

int menu(){

    int scelta;

    cout<<BLUE<<"\t -----Menu'-----\n"<<RESET;
    cout<<BLUE<<"1."<<RESET<<" Visualizza la media della classe per le due materie"<<endl;
    cout<<BLUE<<"2."<<RESET<<" Visualizza il nome e il voto degli studenti che hanno il voto di informatica maggiore della media"<<endl;
    cout<<BLUE<<"3."<<RESET<<" Visualizza il nome e il voto degli studenti che hanno il voto di matematica inferiore alla media"<<endl;
    cout<<BLUE<<"4."<<RESET<<" Visualizza il nome dello studente che ha il voto più alto in informatica e dello studente col voto più alto in matematica"<<endl;
    cout<<BLUE<<"5."<<RESET<<" Dato il nome in input il nome di uno studente stampare i suoi voti in matematica e informatica, segnala se lo studente non esiste"<<endl;
    cout<<BLUE<<"6."<<RESET<<" Visualizza quanti studenti hanno voto <6, quanti tra 6 e 7, e quanti > 8, in matematica"<<endl;
    cout<<BLUE<<"7."<<RESET<<" Visualizza quanti studenti hanno voto <6, quanti tra 6 e 7, e quanti > 8, in informatica"<<endl;
    cout<<BLUE<<"8."<<RESET<<" Stampa tutti i voti di matematica e infomatica"<<endl;
    cout<<BLUE<<"0."<<RESET<<" Esci"<<endl;

    cout<<endl;

    cout<<BLUE<<"Fai una scelta: "<<RESET;
    cin>>scelta;

    return scelta;
}

void caricaVoti(double materia[]){
    for(int i=0;i<dim;i++){
        materia[i]=rand()%votoMax+1;
    }
}

double media(double materia[]){
    double somma=0;

    for(int i=0;i<dim;i++){
        somma+=materia[i];
    }

    return somma/dim;
}

void stampaVoti1(double materia[], double mediaClasse, string studenti[]){

    for(int i=0;i<dim;i++){

        if(materia[i]>mediaClasse){
            cout<<studenti[i]<<setw( ( lenght-studenti[i].size() ) + 10 )<<materia[i]<<endl;
        }
    }
}

void stampaVoti2(double materia[], double mediaClasse, string studenti[]){

    for(int i=0;i<dim;i++){

        if(materia[i]<mediaClasse){
            cout<<studenti[i]<<setw( ( lenght-studenti[i].size() ) + 10 )<<materia[i]<<endl;
        }
    }
}

int ricerca(string studenti[], double materia[]){

    int pos=0;
    double max=materia[pos];

    for(int i=1;i<dim;i++){

        if(materia[i]>max){
            max=materia[i];
            pos=i;
        }
    }

    return pos;
}

void cercaStudente(string studenti[], double informatica[], double matematica[]){
    string nome,nome1,nome2;
    int pos;
    bool esiste=false;

    cout<<BLUE<<"Inserisci il nome del studente: "<<RESET;
    cin.ignore();
    getline(cin,nome);

    cout<<endl;
    nome1=nome;
    for(int i=0;i<nome.size();i++){
        nome1[i]=toupper(nome[i]);
    }

    for(int i=0;i<dim;i++){

        nome2=studenti[i];
        for(int j=0;j<studenti[i].size();j++){
            nome2[j]=toupper(studenti[i][j]);
        }

        if(nome1==nome2){
            esiste=true;
            pos=i;
            break;
        }
    }

    if(esiste==true){
        cout<<BLUE<<"Nome studente: "<<RESET<<studenti[pos]<<endl;
        cout<<BLUE<<"Voti informatica: "<<RESET<<informatica[pos]<<endl;
        cout<<BLUE<<"Voti matematica: "<<RESET<<matematica[pos]<<endl;
    }
    else{
        cout<<YELLOW<<"Lo studente "<<nome<<" non esiste"<<RESET<<endl;
    }
}

double calcolaVoto(int perc){
    return (perc/100.0)*votoMax;
}

void voti(string studenti[], double materia[], int MinVoto, int MaxVoto, string color){

    int cont=0;

    for(int i=0;i<dim;i++){
        if(materia[i]>MinVoto && materia[i]<MaxVoto){
            cout<<studenti[i]<<setw( ( lenght-studenti[i].size() ) + 10 )<<color<<materia[i]<<RESET<<endl;
            cont++;
        }
    }

    cout<<BLUE<<"Gli studenti con voti tra "<<RESET<<MinVoto<<BLUE<<" e "<<RESET<<MaxVoto<<BLUE<<" sono: "<<RESET<<cont<<endl;

    avanti();

}

void stampaVoti(string studenti[], double materia[]){

    for(int i=0;i<dim;i++){
        cout<<studenti[i]<<setw( ( lenght-studenti[i].size() ) + 10 );
        if(materia[i]<calcolaVoto(50)){
            cout<<RED<<materia[i]<<RESET<<endl;
        }
        else if(materia[i]>=calcolaVoto(50) && materia[i]<calcolaVoto(60)){
            cout<<YELLOW<<materia[i]<<RESET<<endl;
        }
        else{
            cout<<GREEN<<materia[i]<<RESET<<endl;
        }
    }
}

void avanti(){
    cout<<GREEN<<"\nPremi invio per continuare..."<<RESET<<endl;
    cin.get();
    cin.ignore();
}