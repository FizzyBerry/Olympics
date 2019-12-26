//Maria Widera
#include <iostream>
#include <fstream>

using namespace std;

class Caesar;

class Squad;


int numberOfJugedGladiators = 0;
int numberOfStrikes = 0;

class Gladiator{
protected:
    virtual void die(){
        MAX_HEALTH = 0;
    }

public:
    friend Caesar;
    friend Squad;

    int MAX_HEALTH;
    int BASE_DAMAGE;
    int BASE_RAPIDITY;
    int BASE_DEFENCE;

    Gladiator* next;

    Gladiator(){}

    virtual unsigned int getRemainingHealth() = 0;

    virtual unsigned int getDamage() = 0;

    virtual void takeDamage(unsigned int damage) = 0;

    virtual unsigned int getRapidity() = 0;

    virtual void applyWinnerReward() = 0;

    virtual void cure() = 0;

    virtual void printParams() = 0;

};


class Caesar{
public:
    Caesar(){}

    void judgeDeathOrLife(Gladiator* G){
        numberOfJugedGladiators++;
        if(numberOfJugedGladiators%3 == 0){
            G->die();
        }else{
            G->cure();
            G->applyWinnerReward();
        }
    }
};


class Amphitheatre{
protected:
    Caesar* C;

public:
    Amphitheatre(){}

    Amphitheatre(Caesar* _C){
        C = _C;
    }

    void fight(Gladiator* G1, Gladiator* G2){
        numberOfStrikes = 0;
        Gladiator* tmp;
        if(G1->getRemainingHealth() != 0 && G2->getRemainingHealth() != 0){
            if(G1->getRapidity() < G2->getRapidity()){
                tmp = G2;
                G2 = G1;
                G1 = tmp;
            }
            int damage;
            if(G1->getRemainingHealth() == 0 || G2->getRemainingHealth() == 0)
                return;
            while((G1->getRemainingHealth() >= 10 && G2->getRemainingHealth() >= 10) && numberOfStrikes != 40){
                G2->takeDamage(G1->getDamage());
                numberOfStrikes++;

                if(G2->getRemainingHealth() >= 10){
                    G1->takeDamage(G2->getDamage());
                    numberOfStrikes++;
                }

                if(G1->getRemainingHealth() >= 10 && G2->getRemainingHealth() >= 10){
                    G1->printParams();
                    G2->printParams();
                }

            }
            if(G1->getRemainingHealth() < 10 && G1->getRemainingHealth() > 0 && numberOfStrikes < 40){
                C->judgeDeathOrLife(G1);
            } else {
                if(G1->getRemainingHealth() >= 10 && numberOfStrikes < 40){
                    G1->cure();
                    G1->applyWinnerReward();
                }
            }

            if(G2->getRemainingHealth() < 10 && G2->getRemainingHealth() > 0 && numberOfStrikes < 40){
                C->judgeDeathOrLife(G2);
            } else {
                if(G2->getRemainingHealth() >= 10 && numberOfStrikes < 40){
                    G2->cure();
                    G2->applyWinnerReward();
                }
            }
            G1->printParams();
            G2->printParams();
        }
    }

};

class Human : virtual public Gladiator{
public:
    string name;

    Human(string _name){
        name = _name;
        MAX_HEALTH = 200;
        BASE_DAMAGE = 30;
        BASE_RAPIDITY = 10;
        BASE_DEFENCE = 10;
    }

    Human(){}

    unsigned int getRemainingHealth(){
        return (MAX_HEALTH/2);
    }

    unsigned int getDamage(){
        return BASE_DAMAGE;
    }

    void takeDamage(unsigned int damage){
        damage =  damage - BASE_DEFENCE - BASE_RAPIDITY;

        if(damage < 100000)
            MAX_HEALTH -= damage;


        if(MAX_HEALTH < 0)
            MAX_HEALTH = 0;
    }

    unsigned int getRapidity(){
        return BASE_RAPIDITY;
    }

    void applyWinnerReward(){
        BASE_DAMAGE += 2;
        BASE_RAPIDITY += 2;
    }

    void cure(){
        MAX_HEALTH = 200;
    }

    void printParams(){
        cout << name << ":" << MAX_HEALTH/2 << ":" << BASE_DAMAGE << ":" << BASE_RAPIDITY << endl;
    }

};

class Beast : virtual public Gladiator{
public:
    string type;
    bool dmg;

    Beast(string _type){
        type = _type;
        MAX_HEALTH = 150;
        BASE_DAMAGE = 40;
        BASE_RAPIDITY = 20;
        dmg = false;
    }

    Beast(){}

    unsigned int getRemainingHealth(){
        return ((MAX_HEALTH*10)/15);
    }

    unsigned int getDamage(){
        return BASE_DAMAGE;
    }

    void takeDamage(unsigned int damage){
        damage =  damage - (BASE_RAPIDITY/2);
        if(damage < 100000)
            MAX_HEALTH -= damage;

        if(MAX_HEALTH < 0)
            MAX_HEALTH = 0;

        if(getRemainingHealth() < 25 && !dmg){
            BASE_DAMAGE = BASE_DAMAGE*2;
            dmg = true;
        }

    }

    unsigned int getRapidity(){
        return BASE_RAPIDITY;
    }

    void applyWinnerReward(){
        BASE_DAMAGE += 2;
        BASE_RAPIDITY += 2;
    }

    void cure(){
        MAX_HEALTH = 150;
        if(dmg)
            BASE_DAMAGE = BASE_DAMAGE/2;
        dmg = false;
    }

    void printParams(){
        cout << type << ":" << (MAX_HEALTH*10)/15 << ":" << BASE_DAMAGE << ":" << BASE_RAPIDITY << endl;
    }


};

class Berserker : public Human, public Beast{
public:
    string ID;
    bool dmg;

    Berserker(){}

    Berserker(string _name){
        MAX_HEALTH = 200;
        BASE_DAMAGE = 35;
        BASE_RAPIDITY = 5;
        BASE_DEFENCE = 15;
        ID = _name;
        dmg = false;
    }

    unsigned int getRemainingHealth(){
        return (MAX_HEALTH/2);
    }

    unsigned int getDamage(){
        return BASE_DAMAGE;
    }

    void takeDamage(unsigned int damage){
        damage = damage - BASE_RAPIDITY - BASE_DEFENCE;
        if(damage < 100000){
            MAX_HEALTH -= damage;
        }

        if(MAX_HEALTH < 0){
            MAX_HEALTH = 0;
        }

        if(getRemainingHealth() < 25 && !dmg){
            BASE_DEFENCE = 0;
            BASE_DAMAGE = BASE_DAMAGE*2;
            dmg = true;
        }
    }

    unsigned int getRapidity(){
        return BASE_RAPIDITY;
    }

    void applyWinnerReward(){
        BASE_DAMAGE += 2;
        BASE_RAPIDITY += 2;
    }

    void cure(){
        MAX_HEALTH = 200;
        if(dmg){
            BASE_DAMAGE = BASE_DAMAGE/2;
            BASE_DEFENCE = 15;
        }
        dmg = false;
    }

    void printParams(){
        cout << ID << ":" << MAX_HEALTH/2 << ":" << BASE_DAMAGE << ":" << BASE_RAPIDITY << endl;
    }
};


class Squad : public Gladiator{
    Gladiator* first;
private:

    void die(){
        MAX_HEALTH = 0;
        BASE_DAMAGE = 0;
        BASE_RAPIDITY = 0;
        Gladiator* tmp = first;
        while(tmp){
            tmp->die();
            tmp = tmp ->next;
        }
        numberOfMembers = 0;
        first = NULL;
        allDead = false;
        ded = false;
        alreadyInSquad = false;
    }

public:
    bool alreadyInSquad, allDead;
    int numberOfMembers;

    Squad(){
        MAX_HEALTH = 0;
        BASE_DAMAGE = 0;
        BASE_RAPIDITY = 100000;
        alreadyInSquad = false;
        numberOfMembers = 0;
        ded = false;
        allDead = false;
        first = NULL;
    }

    void addGladiator(Gladiator* G){
        if(G->getRemainingHealth() > 0){
            Gladiator* tmp = first;
            while(tmp){ // sprawdzanie czy gladiator juz nie nalezy do squadu
                if(tmp == G){
                    alreadyInSquad = true;
                    break;
                }
                tmp = tmp->next;
            }
            if(!alreadyInSquad){
                BASE_DAMAGE += G->getDamage();
                numberOfMembers++;
                if(G->getRapidity() < BASE_RAPIDITY){
                    BASE_RAPIDITY = G->getRapidity();
                }

                if(G->getRemainingHealth() > MAX_HEALTH)
                    MAX_HEALTH = G->getRemainingHealth();

                G->next = first;
                first = G;
                alreadyInSquad = false;
            }
        }
    }

    unsigned int getRemainingHealth(){
        Gladiator* tmp = first;
        MAX_HEALTH = 0;
        while(tmp){
            if(tmp->getRemainingHealth() > MAX_HEALTH)
                MAX_HEALTH = tmp->getRemainingHealth();
            tmp = tmp->next;
        }
        return MAX_HEALTH;
    }

    unsigned int getDamage(){
        BASE_DAMAGE = 0;
        Gladiator* tmp = first;
        while(tmp){
            BASE_DAMAGE += tmp->getDamage();
            tmp = tmp->next;
        }

        return BASE_DAMAGE;
    }

    bool ded;

    void takeDamage(unsigned int damage){

        Gladiator* tmp = first;
        Gladiator* tmpPrev = NULL;
        damage = damage/numberOfMembers;
        int newHealth = 0;
        while(tmp){
            tmp->takeDamage(damage);
            /**Aktualizacja parametrow squadu**/
            if(tmp->getRemainingHealth() > newHealth)   // szukanie gladiatora z najwiekszym % zycia po ataku
                newHealth = tmp->getRemainingHealth();
            if(tmp->getRemainingHealth() <= 0){ // przypadek kiedy zadane obrazenia zabijaja gladiatora
                if(numberOfMembers == 1){
                    this->die();
                    return;
                }

                if(tmpPrev != NULL)
                    tmpPrev->next = tmp->next;
                else{
                    first = tmp->next;
                }

                tmp->die();
                numberOfMembers --;
                BASE_DAMAGE -= tmp->getDamage();
                ded = true;
            }

            if(!ded){
                tmpPrev = tmp;
                tmp = tmp->next;
            } else {
                if(tmpPrev != NULL)
                    tmp = tmpPrev->next;
                else{
                    tmp = first;
                }
            }
            ded = false;
        }

        if(first == NULL)
            allDead = true;

        MAX_HEALTH = newHealth;

        tmp = first;        // szukanie najwolniejszego czlonka
        int newRapidity = 100000;
        BASE_DAMAGE = 0;
        while(tmp){
            if(tmp->getRapidity() < newRapidity)
                newRapidity = tmp->getRapidity();

            BASE_DAMAGE += tmp->getDamage();
            tmp = tmp->next;
        }
        if(newRapidity != 100000)
            BASE_RAPIDITY = newRapidity;
        else
            BASE_RAPIDITY = 0;
    }

    unsigned int getRapidity(){
        BASE_RAPIDITY = 1000000;
        Gladiator* tmp = first;
        while (tmp){
            if(tmp->BASE_RAPIDITY < BASE_RAPIDITY)
                BASE_RAPIDITY = tmp->getRapidity();
            tmp = tmp->next;
        }
        return BASE_RAPIDITY;
    }

    void applyWinnerReward(){
        BASE_DAMAGE = 0;
        BASE_RAPIDITY = 100000;
        Gladiator* tmp = first;
        while(tmp){
            tmp->applyWinnerReward();
            if(tmp->getRapidity() < BASE_RAPIDITY)
                BASE_RAPIDITY = tmp->getRapidity();

            BASE_DAMAGE += tmp->getDamage();
            tmp = tmp->next;
        }
        MAX_HEALTH = 100;
    }

    void cure(){
        Gladiator* tmp = first;
        while(tmp){
            tmp->cure();
            tmp = tmp->next;
        }
        MAX_HEALTH = 100;
    }

    void printParams(){
        Gladiator* tmp = first;
        MAX_HEALTH = 0;
        BASE_DAMAGE = 0;
        BASE_RAPIDITY = 100000;
        while(tmp){
            if(MAX_HEALTH < tmp->getRemainingHealth())
                MAX_HEALTH = tmp->getRemainingHealth();

            if(BASE_RAPIDITY > tmp->getRapidity())
                BASE_RAPIDITY = tmp->getRapidity();

            BASE_DAMAGE += tmp->getDamage();

            tmp = tmp->next;
        }

        if(BASE_RAPIDITY == 100000){
            BASE_RAPIDITY = 0;
        }

        if(allDead){
            MAX_HEALTH = 0;
            BASE_DAMAGE = 0;
            BASE_RAPIDITY = 0;
        }

        cout << "Squad:" << MAX_HEALTH << ":" << BASE_DAMAGE << ":" << BASE_RAPIDITY << endl;
    }

};



int main(){
    Amphitheatre a(new Caesar());

    Berserker glad("Glad Valakas");

    Squad squad;
    squad.addGladiator(&glad);
    Berserker b("B");
    b.printParams();
    a.fight(&b, &squad);

    glad.printParams();

    Caesar* c = new Caesar();
    //Amphitheatre a(c);
    Berserker B("Berserker");
    Beast B1("B1");
    Human H1("H1");



    a.fight(&B,&B1);
    cout << endl;
    a.fight(&B,&H1);
    cout << endl;
    a.fight(&B,&H1);
    cout << endl;
    a.fight(&B,&H1);

    Berserker BR1("BR1");
    Beast B3("B3");
    Human H3("H3");

    cout << endl;
    a.fight(&B,&BR1);
    cout << endl;
    a.fight(&B,&B3);
    cout << endl;
    a.fight(&B,&B3);
    cout << endl;
    a.fight(&B,&B3);
    cout << endl;
    a.fight(&B,&H3);
    cout << endl;
    a.fight(&B,&H3);
    cout << endl;
    a.fight(&B,&H3);


    Beast B2("B2");
    Human H2("H2");

    Squad S;
    S.addGladiator(&B2);
    S.addGladiator(&H2);

    cout << "\nH&Bt vs BERSERKER\n" << endl;

    a.fight(&S,&B);

    cout << "\nBr&Br vs BERSERKER\n\n" ;

    Berserker BR2("BR2");
    Berserker BR3("BR3");

    Squad S1;
    S1.addGladiator(&BR2);
    S1.addGladiator(&BR3);

    a.fight(&B,&S1);

    cout << "\nH&H vs BERSERKER\n\n" ;

    Human H4("H4");
    Human H5("H5");

    Squad S2;
    S2.addGladiator(&H4);
    S2.addGladiator(&H5);

    a.fight(&B,&S2);

    cout << "\nBt&Bt vs BERSERKER\n\n" ;

    Beast B4("B4");
    Beast B5("B5");

    Squad S3;
    S3.addGladiator(&B4);
    S3.addGladiator(&B5);

    a.fight(&B,&S3);

    cout << "\nH&Bt vs BERSERKER\n\n" ;

    Human H7("B6");
    Beast B7("B7");

    Squad S5;
    S5.addGladiator(&B7);
    S5.addGladiator(&H7);

    a.fight(&B,&S5);

    cout <<"\nBEASTS\n\n" ;

    Beast B8("B8");
    Beast B9 ("B9");
    Beast B10 ("B10");
    Beast B11 ("B11");
    Beast B12 ("B12");
    Beast B13 ("B13");
    Beast B14 ("B14");
    Beast B15 ("B15");
    Beast B16 ("B16");
    Beast B17 ("B17");
    Beast B18 ("B18");
    Beast B19 ("B19");
    Beast B20 ("B20");


    a.fight(&B,&B8);
    cout << endl;
    a.fight(&B,&B9);
    cout << endl;
    a.fight(&B,&B10);
    cout << endl;
    a.fight(&B,&B11);
    cout << endl;
    a.fight(&B,&B12);
    cout << endl;
    a.fight(&B,&B13);
    cout << endl;
    a.fight(&B,&B14);
    cout << endl;
    a.fight(&B,&B15);
    cout << endl;
    a.fight(&B,&B16);
    cout << endl;
    a.fight(&B,&B17);
    cout << endl;
    a.fight(&B,&B18);
    cout << endl;
    a.fight(&B,&B19);
    cout << endl;
    a.fight(&B,&B20);
    cout << endl;

    cout << "\nH&Br vs BERSERKER\n\n";

    Human H6("H6");
    Berserker BR4("BR4");

    Squad S4;
    S4.addGladiator(&H6);
    S4.addGladiator(&BR4);

    a.fight(&B,&S4);



    cout << "\nH&H&H vs BERSERKER\n\n";

    Human H10 ("H7");
    Human H8 ("H8");
    Human H9 ("H9");

    Squad S6;

    S6.addGladiator(&H10);
    S6.addGladiator(&H8);
    S6.addGladiator(&H9);

    a.fight(&B,&S6);


return 0;

}














