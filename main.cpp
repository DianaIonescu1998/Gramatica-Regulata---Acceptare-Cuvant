#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


void gr (char **M, int im, char *w, int y, char *&poz, int &j, int n){ //fiecare variabila reprezinta acelasi lucru ca in main
    //functia gr va actualiza vectorul poz pentru litera de pe pozitia y din cuvantul w
    // M e matricea si im, numarul de linii
    int i, naux=0;
    char *aux;
    aux= new char [n]; //n= numarul de neterminale
        for(i=0; i<j ;i++){ //poz[i]
            for(int u=0; u<im; u++)
                if(M[u][2]==poz[i] && M[u][1]==w[y]){
                    bool ok=true;
                    for(int r=0; r<naux; r++ )
                        if(M[u][0]== aux[r]) ok= false;
                    if(ok){aux[naux]=M[u][0];
                             naux++;}
                }
        }
    delete [] poz; //sterg vectorul testat
    poz=aux; // actualizez vectorul poz pentru urmatoarea verificare
    j=naux;
//    cout<<endl;
//    for(int u=0; u<j;u++)
//        cout<<poz[u]<<" ";


}

int main ()
{
    // n= numarul de neterminale
    // N= nectorul de neterminale
    // t= numarul de terminale
    // T= vectorul de terminale
    ifstream fin ("C:\\Users\\Dell\\Desktop\\GR\\test.txt");
    int n=0, t=0;
    char x, *N, *T;
    N= new char [100];
    //citirea neterminalelor
    while((fin>>x)&&(x>='A')&&(x<='Z')){
        N[n]=x;
        n++;
    }
    if(n<100){
        char *aux;
        aux= new char [n];
        for(int i =0; i< n; i ++)
            aux[i]= N[i];
        delete [] N;
        N=aux;
            }
//    cout<<"Neterminale: ";
//    for (int i=0; i< n; i++)
//        cout<<N[i]<<" ";

    T= new char [100];
    //citirea terminalelor
    while(x>='a' && x<='z'){
        T[t]=x;
        t++;
        fin>>x;
    }
    if(t<100){
        char *aux;
        aux= new char [t];
        for(int i =0; i< t; i ++)
            aux[i]= T[i];
        delete [] T;
        T=aux;
    }
//    cout<<"\nTerminale: ";
//    for (int i=0; i< t; i++)
//        cout<<T[i]<<" ";
//
//    cout<<endl;
    char c[2];
    //cout<<x;


//citirea matricei ce contine regulile de productie
    //voi folosi o variabila x de tip char pentru a citi primul neterminal si o variabila c[2] care citeste regulile de forma kK
    // lamda va fi retinut sub forma "-"
    char **M;                                                                                                      /////alocarea dinamica a unei matrici
     M= new char* [100];
    for(int i=0; i< 100; i++)
        M[i]= new char [3];
    int im=0;//numarul de linii ale matricei
    M[0][0]=x;
    while(fin>>c){

        if(c[0]>='a' && c[0] <= 'z') M[im][1]=c[0];
        else M[im][1]='-';
        if(c[1]>='A' && c[1]<='Z') M[im][2]=c[1];
        else M[im][2]='-';
        fin>>x;
        im++;
        M[im][0]=x;
        //cout<<x;
    }


    char **aux;
       aux= new char* [im];
    for(int i=0; i< im; i++)
        aux[i]= new char [3];
    for(int i=0;i <im; i++)
        for(int j=0; j< 3; j++)
            aux[i][j]=M[i][j];
    for(int i=0; i<im ;i++)
        delete [] M[i];
    delete [] M;
    M=aux;
//    for(int i=0; i<im; i++){
//        for(int j=0; j<3; j++)
//            cout<<M[i][j]<<" ";
//        cout<<endl;
//    }

    //citirea cuvantului de verificat
    char w[100];
//    cout<<"Cuvantul: ";
//    cin>>w;
    ifstream fcuvinte("C:\\Users\\Dell\\Desktop\\GR\\cuvinte.txt");// trebuie modificat fisierul de intrare                  //******citire din fisier
    while(fcuvinte>>w){
    int y;
    y= strlen(w)-1;
    //cout<<w[y];
    bool ok= false;

    //
    int e=0;

    //in vectorii poz si pozLamda voi retine neterminalele din care vine ultima litera a cuvantului
    //vectorul pozLamda este necesar pentru a gasi neterminalele pe care se afla lamda -> obtinem alte neterminale si verificam pentru ultima litera a cuvantului si neterminalul obtinut
    // j va fi numarul de elemente ale lui poz si jLamda, numarul de elemente ale lui pozLamda
    int j=0, jLamda=0;
    char *poz, *pozLamda; //indicii liniilor pe care se  afla ultima litera a cuvantului
    poz =new char [n]; //aloc memorie pentru toete cele n neterminale
    pozLamda= new char [n];
    while(e<im ){
    if( (M[e][1]==w[y]) && (M[e][2]=='-')) {
        bool test=true;
        for(int i=0; i<j; i++)
            if(poz[i]==M[e][0]) test= false;
        if(test) {poz[j]=M[e][0];
                 j++;}
    }
        e++;
    }
    for(int i=0; i<im; i++)
       if(M[i][1]=='-')
        {
            pozLamda[jLamda]=M[i][0];
            jLamda++;
        }
//    cout<<"poz: ";
//    for(int i=0; i< j ;i++)
//        cout<<poz[i]<<" ";
//    cout<<endl<<"pozLamda: ";
//    for(int i=0; i< jLamda ;i++)
//        cout<<pozLamda[i]<<" ";

    // verific daca neterminalele gasite si ultima litera a cuvantului fac parte dintr-o regula de productie
    for(int i=0; i<jLamda; i++){
        e=0;
    while(e<im){
        if(M[e][2]==pozLamda[i] && M[e][1]==w[y]){
                bool test=true;
            for(int u=0; u<j; u++)
                if(poz[u]==M[e][0]) test= false;
            if(test) {poz[j]=M[e][0];
                j++;}
            }
        e++;
    }
    }
//    cout<<endl;
//    cout<<"poz: ";
//    for(int i=0; i< j ;i++)
//        cout<<poz[i]<<" ";
//    cout<<"liera: "<<w[y]<<" ";
    y--; //actualizez pozitia in w
    //cout<<endl;

    //testez pentru fiecare litera din cuvant
    while((y>=0)){
        //cout<<"liera: "<<w[y]<<" ";
        gr( M, im, w, y, poz, j, n);
       // cout<<"poz: ";
//        for(int i=0; i< j ;i++)
//            cout<<poz[i]<<" ";
        y--;
    }
    //if (j==0) cout<<"Cuvantul "<<w<<" nu este acceptat";
    // verific daca dupa ce am terminat de testat cuvantul ajung la starea initiala
    bool tr=false;
    for(int i=0; i<j; i++)
        if(poz[i]==N[0]) tr=true;
    if(tr) cout<<"Cuvantul "<<w<<" este acceptat\n";
    else cout<<"Cuvantul "<<w<<" nu este acceptat\n";
    }// aici se incheie citirea din fisier a cuvintelor

    //cout<<"\nSfarsit.\n";
}