#include <iostream>
#include <string.h>
#include <exception>
#include <stdexcept>
#include <list>
#include <iterator>
#include <ios>
#include <limits>

using namespace std;
using std::runtime_error;

int numarProduse;
int numarClienti;
int numarComenzi;

class IOInterface {
public:
    virtual istream& read(istream& in) = 0;
    virtual ostream& write(ostream& out) = 0;
};

class Produs: public IOInterface{
protected:
    string nume;
    float pret;
    string culoare;

public:
    Produs(){
        this->nume = "Anonim";
        this->pret = 0;
        this->culoare = "-";
    }

    Produs(string nume, float pret,  string culoare){
        this->nume = nume;
        this->pret = pret;
        this->culoare = "-";
    }

    Produs(const Produs& prod){
        this->nume = prod.nume;
        this->pret = prod.pret;
        this->culoare = prod.culoare;
    }

    ~Produs(){}

    Produs& operator=(const Produs& prod){
        if(this != &prod){

            this->nume = prod.nume;
            this->pret = prod.pret;
            this->culoare = prod.culoare;
        }
        return *this;
    }

    istream& read(istream&in){
       cout<<"Numele produsului este: ";
        in>>this->nume;
        int rasp = 0;
        do{
            try{
                cout<<"Pretul produsului este: ";
                in>>this->pret;
                if(in.fail())
                    throw 1;
                rasp = 1;
                }
            catch(int e){
                cout<<"Pret introdus gresit!\n";
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }while(rasp==0);
        cout<<"Culoarea produsului este: ";
        in>>this->culoare;
        cout<<endl;
        return in;
    }

    friend istream& operator>>(istream& in, Produs& prod){
        return prod.read(in);
    }

    ostream& write(ostream& out){
        out<<"Numele produsului este "<<this->nume<<endl;
        out<<"Pretul produsului este "<<this->pret<<endl;
        out<<"Culoarea produsului este "<<this->culoare<<endl<<endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, Produs& prod){
        return prod.write(out);
    }

    virtual void specProdus(){
        cout<<"Produsul nu este complet";
    };

    virtual void setBat(int cap){
        cout<<"Produsul nu este un mouse wireless;";
    }

    float getPret(){
        return this->pret;
    }

    void setPret(float pret){
        this->pret = pret;
    }

};

class Tastatura : public virtual Produs{
private:
    int nrTaste;
    bool display;
public:
    Tastatura():Produs(){
        this->nrTaste = 0;
        this->display = false;
    }

    Tastatura(int nrTaste, bool display, string nume, float pret, string culoare):Produs(nume, pret, culoare){
        this->nrTaste = nrTaste;
        this->display = display;
    }

    ~Tastatura(){}

    Tastatura(const Tastatura& tastatura) : Produs(tastatura){
        this->nrTaste = tastatura.nrTaste;
        this->display = tastatura.display;
    }

    Tastatura& operator=(const Tastatura& tastatura){
        if (this!=&tastatura){
            Produs::operator=(tastatura);
            this->nrTaste = tastatura.nrTaste;
            this->display = display;
        }
        return *this;
    }

    istream& read(istream& in){
        Produs::read(in);
        int rasp = 0;
        do{
            try{
                cout << "Cate taste are: ";
                in >> this->nrTaste;
                if(in.fail())
                    throw 1;
                rasp = 1;
            }
            catch(int e){
                cout<<"Nr taste introdus gresit!\n";
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');}
        }while(rasp == 0);
        rasp = 0;
        do{
            try{
                cout << "Are display (1/0): ";
                in >> this->display;
                if(in.fail())
                    throw 1;
                rasp = 1;
            }
            catch(int e){
                cout<<"Display introdus gresit!\n";
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');}
        }while(rasp == 0);
        cout<<endl<<endl;
        return in;
    }

    friend istream& operator>>(istream& in, Tastatura& tastatura){
        return tastatura.read(in);
    }

    ostream& write(ostream& out){
        Produs::write(out);
        out << "Numar de taste: ";
        out << this->nrTaste<<endl;
        out << "Are display: ";
        out << this->display<<endl<<endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, Tastatura& tastatura){
        return tastatura.write(out);
    }

    void set(int nr){
        this->nrTaste=nr;
    }

    void set(bool bol){
        this->display = bol;
    }

    void specProdus()const{
        cout << "Are " << this->nrTaste << " taste"<<endl;
        if (this->display == false)
            cout<<"Nu are display"<<endl;
        else cout<<"Are display"<<endl;
    }
};

class Mouse : public virtual Produs{
private:
    int dpi;
public:
    Mouse():Produs(){
        this->dpi = 0;
    }

    Mouse(int dpi, string nume, float pret, string culoare):Produs(nume, pret, culoare){
        this->dpi = this->dpi;
    }

    ~Mouse(){}

    Mouse(const Mouse& mouse) : Produs(mouse){
        this->dpi = mouse.dpi;
    }

    Mouse& operator=(const Mouse& mouse){
        if (this!=&mouse){
            Produs::operator=(mouse);
            this->dpi = mouse.dpi;
        }
        return *this;
    }

    istream& read(istream& in){
        Produs::read(in);
        cout << "Cati DPI are: ";
        in >> this->dpi;
        cout<<endl;
        return in;
    }

    friend istream& operator>>(istream& in, Mouse& mouse){
        return mouse.read(in);
    }

    ostream& write(ostream& out){
        Produs::write(out);
        out << "Numar DPI: ";
        out << this->dpi<<endl<<endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, Mouse& mouse){
        return mouse.write(out);
    }

    void specProdus(){
        cout << "Are " << this->dpi << " DPI"<<endl;
    }
};

class MouseWireless: public Mouse{
private:
    int capacitateBaterie;

public:
    MouseWireless():Mouse(){
        this->capacitateBaterie = 0;
    }

    MouseWireless(int capacitateBaterie, int dpi, string nume, float pret, string culoare):Mouse(dpi, nume, pret, culoare){
        this->capacitateBaterie = capacitateBaterie;
    }

    ~MouseWireless(){}

    MouseWireless(const MouseWireless& mousew): Mouse(mousew){
        this->capacitateBaterie = mousew.capacitateBaterie;
    }



    MouseWireless& operator=(const Mouse mouse){
        Mouse::operator=(mouse);
        this->capacitateBaterie = 0;

        return *this;
    }

    MouseWireless(Mouse mouse):Mouse(mouse){
        this->capacitateBaterie = 0;
    }

    MouseWireless& operator=(const MouseWireless& mousew){
        if(this!=&mousew){
            Mouse::operator=(mousew);
            this->capacitateBaterie = mousew.capacitateBaterie;
        }
        return *this;
    }

    istream& read(istream&in){
        Mouse::read(in);
        cout << "Capacitatea bateriei: ";
        in >> this->capacitateBaterie;
        cout<<endl;
        return in;
    }

    friend istream& operator>>(istream& in, MouseWireless& mousew){
        return mousew.read(in);
    }

    ostream& write(ostream& out){
        Mouse::write(out);
        out << "Capacitate baterie: "<<this->capacitateBaterie<<endl<<endl;
        return out;
    }

    friend ostream& operator<<(ostream& out, MouseWireless& mousew){
        return mousew.write(out);
    }

    void setBat(int cap){
        this->capacitateBaterie = cap;
    }
};

class Client{
private:
    char* nume;
    string adresa;
    string mail;
    float puncteLoialitate;

public:
    Client(){
        this->nume = new char[strlen("Anonim")+1];
        strcpy(this->nume,"Anonim");
        this->adresa = "-";
        this->mail = "-";
        this->puncteLoialitate = 0;
    }

    Client(char* nume , string adresa , string mail , float puncteLoialitate){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->adresa = adresa;
        this->mail = mail;
        this->puncteLoialitate = puncteLoialitate;
    }

    Client(const Client& client){
        if(client.nume!=NULL){
            this->nume = new char[strlen(client.nume)+1];
            strcpy(this->nume, client.nume);}
        this->adresa = client.adresa;
        this->mail = client.mail;
        this->puncteLoialitate = client.puncteLoialitate;
    }

    ~Client(){
        if(this->nume != NULL)
            delete[] this->nume;
    }

    Client& operator=(const Client& client){
        if (this != &client){
            if(this->nume != NULL)
                delete[] this->nume;
            if(client.nume != NULL)
                this->nume = new char[strlen(client.nume)+1];
            strcpy(this->nume,client.nume);
            this->adresa = client.adresa;
            this->mail = client.mail;
            this->puncteLoialitate = client.puncteLoialitate;
        }
    }

    friend istream& operator>>(istream&in, Client& client){
        cout<<"Numele clientului este: ";
        char auxnume[25];
        in>>auxnume;
        delete[] client.nume;
        client.nume = new char[strlen(auxnume)+1];
        strcpy(client.nume, auxnume);
        cout<<"Adresa clientului este: ";
        in>>client.adresa;
        cout<<"Mailul clientului este: ";
        in>>client.mail;
        cout<<"Cate puncte de loialitate are clientul: ";
        in>>client.puncteLoialitate;
        cout<<endl;
        return in;
    }

    friend ostream& operator<<(ostream&out, const Client& client){
        if(client.nume)
            out<<"Numele clientului este "<<client.nume<<endl;
        out<<"Adresa clientului este "<<client.adresa<<endl;
        out<<"Mailul clientului este "<<client.mail<<endl;
        out<<"Clientul are "<<client.puncteLoialitate<<" puncte de loialitate"<<endl;
        cout<<endl;
        return out;
    }

    float getPct(){
        return this->puncteLoialitate;
    }

    void setPct(int p){
        this->puncteLoialitate = p;
    }
};

template <class T>
T* addTen(T* a){
    float pret = a->getPret();
    pret += 10;
    a->setPret(pret);
}

template<>
Client* addTen(Client* a){
    int pct;
    pct = a->getPct();
    pct += 10;
    a->setPct(pct);
    }

class Comanda{
private:
    Client client;
    int nrProduse;
    Produs *produse;
    const int idComanda;
    static int contorComenzi;

public:
    Comanda():idComanda(contorComenzi++){
        Client client;
        this->client = client;
        this->nrProduse = 0;
        this->produse = NULL;
    }

    Comanda(Client client, int nrProduse, Produs* produse):idComanda(contorComenzi++){
        this->client = client;
        this->nrProduse = nrProduse;
        if(this->produse != NULL)
            delete[] this->produse;
        this->produse = new Produs[this->nrProduse];
        for(int i = 0; i < this->nrProduse; i++)
            this->produse[i]=produse[i];
    }

    Comanda(const Comanda& cmd):idComanda(cmd.idComanda){
        this->client = cmd.client;
        this->nrProduse = cmd.nrProduse;
        this->produse = new Produs[this->nrProduse];
        if(this->produse != NULL)
            delete[] this->produse;
        for(int i = 0; i < this->nrProduse; i++)
            this->produse[i] = cmd.produse[i];
    }

    ~Comanda(){
        if(this->produse != NULL)
            delete[] this->produse;
    }

    Comanda& operator=(const Comanda& cmd){
        this->client = cmd.client;
        this->nrProduse = cmd.nrProduse;
        this->produse = new Produs[this->nrProduse];
        if(this->produse != NULL)
            delete[] this->produse;
        for(int i = 0; i< this->nrProduse; i++)
            this->produse[i] = cmd.produse[i];
    }

    friend istream& operator>>(istream&in, Comanda& cmd){
        cin>>cmd.client;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Comanda& cmd){
        out<<"Comanda este data de:"<<endl<<cmd.client;
        out<<"Comanda are "<<cmd.nrProduse<<" produse"<<endl;
        out<<"Acestea sunt: "<<endl;
        for(int i = 0; i< cmd.nrProduse; i++){
            out<<cmd.produse[i];
           // cout<<endl;
        }
        //out<<endl;
        out<<"Comanda are id-ul "<<cmd.idComanda<<endl<<endl;
    }
};
int Comanda::contorComenzi=1000;

class Meniu{
private:
    static Meniu *menu;
    Produs *produse[100];
    Client clienti[100];
    Comanda comenzi[100];
    int nrProduse;

    Meniu(){};
public:
    static Meniu* getInstance(){
        if(!menu)
            menu = new Meniu();
        return menu;
    }

    void startMeniu(){
        cout<<"Welcome to PeriPC\n";
        int alegere, continua = 1;
        while(continua){
            cout<<"Menu"<<endl;
            cout<<"1.Create"<<endl;
            cout<<"2.Read"<<endl;
            cout<<"3.Add 10 function"<<endl;
            //cout<<"4.Delete"<<endl;
            cout<<"0.Stop"<<endl;
            cout<<endl;
            cin>>alegere;
            cout<<endl;
            switch(alegere){
                case 1:{

                    int alegereDoi;

                    cout<<"1.Create product"<<endl;
                    cout<<"2.Create order"<<endl;
                    cout<<"3.Create customer"<<endl;
                    cout<<"0.Cancel"<<endl;
                    cout<<endl;
                    cin>>alegereDoi;
                    cout<<endl;

                    switch(alegereDoi){
                        case 1:{
                            int ans;
                            cout<<"Keyboard (0) sau Mouse(1)? ";
                            cin>>ans;
                            if (ans == 0){
                                Tastatura aux;
                                cin>>aux;
                                produse[nrProduse] = new Tastatura(aux);
                                this->nrProduse++;
                            }
                            if (ans == 1){
                                Mouse aux;
                                cin>>aux;
                                produse[nrProduse] = new Mouse(aux);
                                this->nrProduse++;
                                cout<<"Does it have a wirless version? ";
                                bool answ;
                                cin>>answ;
                                if(answ){
                                    MouseWireless aux2(aux);
                                    produse[nrProduse] = new MouseWireless(aux2);
                                    cout<<"The battery capacity: ";
                                    int cap;
                                    cin>>cap;
                                    produse[nrProduse]->setBat(cap);
                                    this->nrProduse++;
                                }
                            }
                            break;
                        }
                        case 2:{
                            cout<<"Add customer number ";
                            int custnrr, nrProd, idProd;
                            cin>>custnrr;
                            cout<<endl;
                          //  Comanda c(this->clienti[custnrr]);
                            //cout<<c;
                            cout<<"Add number of products ";
                            cin>>nrProd;
                            cout<<endl;
                            Produs *produse[nrProd];
                            for(int i = 0; i < nrProd; i++){
                                cout<<"Enter product ID ";
                                cin>>idProd;
                                cout<<endl;
                                produse[i] = this->produse[idProd];
                            }
                            Comanda c(this->clienti[custnrr], nrProd, *produse);
                            comenzi[numarComenzi++] = c;
                            //cin>>this->comenzi[numarComenzi++];
                            break;
                        }
                        case 3:{
                            cin>>this->clienti[numarClienti++];
                            break;
                        }
                        case 0:{
                            cout<<"Creation cancelled"<<endl<<endl;
                            break;
                        }
                        default:{
                            cout<<"Wrong command"<<endl<<endl;
                            break;
                        }
                    }
                    break;}
                case 2:{
                    int alegereTrei;
                    cout<<"1.Read product"<<endl;
                    cout<<"2.Read order"<<endl;
                    cout<<"3.Read customer"<<endl;
                    cout<<"0.Cancel"<<endl;
                    cout<<endl;
                    cin>>alegereTrei;
                    cout<<endl;
                    switch(alegereTrei){
                        case 1:{
                            int prodnr;
                            cout<<"Product number? ";
                            cin>>prodnr;
                            cout<<endl;
                            cout<<*produse[prodnr];
                            break;
                        }
                        case 2:{
                            int ordnr;
                            cout<<"Order number? ";
                            cin>>ordnr;
                            cout<<endl;
                            cout<<this->comenzi[ordnr];
                            break;
                        }
                        case 3:{
                            int custnr;
                            cout<<"Customer number? ";
                            cin>>custnr;
                            cout<<endl;
                            cout<<this->clienti[custnr];
                            break;
                        }
                        case 0:{
                            cout<<"Read cancelled"<<endl<<endl;
                            break;
                        }
                        default:{
                            cout<<"Wrong command"<<endl<<endl;
                            break;
                        }
                    }
                    break;}
                case 3:{
                    cout<<"AddTen product(0) or client(1)? ";
                    int nrAddTen;
                    cin>>nrAddTen;
                    switch(nrAddTen){
                        case 0:{
                            cout<<"Product number: ";
                            int prodnr;
                            cin>>prodnr;
                            addTen<Produs>(produse[prodnr]);
                            cout<<endl;
                            break;}
                        case 1:{
                            cout<<"Customer number: ";
                            int clientnr;
                            cin>>clientnr;
                            Client* auxclient = new Client(clienti[clientnr]);
                            addTen<Client>(auxclient);
                            clienti[clientnr] = *auxclient;
                            cout<<endl;
                            break;}
                        default:{
                            cout<<"Wrong command"<<endl<<endl;
                            break;
                        }
                    }
                    break;}
                case 4:{

                    break;}
                case 0:{
                    continua = 0;
                    cout<<"Menu has been closed"<<endl;
                    break;}
                default:{
                    cout<<"Wrong command"<<endl;
                    break;}
            }
        }
    }
};
Meniu* Meniu::menu = 0;


int main(){
    Meniu *m = m->getInstance();
    m->startMeniu();

    return 0;
}
