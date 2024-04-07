#include <iostream>
#include <cstring>
using namespace std;

class Goal{
    char* name;
    int min;
    char team[51];
public:
    Goal(const char* name="", int min=0, const char* team=""){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->team, team);
        this->min = min;
    }
    Goal(const Goal& g){
        this->name = new char[strlen(g.name)+1];
        strcpy(this->name, g.name);
        strcpy(this->team, g.team);
        this->min = g.min;
    }
    ~Goal(){
        delete[] name;
    }
    //if hsve dynamic allocation we should create the following:
    //1.destructor , 2.copy constructor , 3. equal operator
    Goal& operator=(const Goal& g){
        if(this != &g){
            delete[] this->name;
            this->name = new char[strlen(g.name)+1];
            strcpy(this->name, g.name);
            strcpy(this->team, g.team);
            this->min = g.min;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Goal& g){
        return out << g.min << " " << g.name;
    }

    Goal& operator++(int){
        Goal temp = *this;
        this->min++;
        return temp;
    }
    Goal& operator--(){
        this->min--;
        return *this;
    }

    char *getName() const {
        return name;
    }

    const char *getTeam() const {
        return team;
    }
};

class Game{
    Goal* goal;
    char team1[51];
    char team2[51];
    int n;
public:
    Game (const char* team1="", const char* team2=""){
        strcpy(this->team1,team1);
        strcpy(this->team2, team2);
        this->n = 0;
        goal = nullptr;
    }
    Game& operator+=(Goal& g){
        for (int i = 0; i < this->n; i++){
            if (g.getName() == this->goal[i].getName()){
                return *this;
            }
        }
        if (strcmp(g.getTeam(), team1)!=0 && strcmp(g.getTeam(), team2)!=0){
            cout << "Invalid team name: " << g.getTeam() << endl;
            return *this;
        }
        Goal* temp = new Goal[this->n+1];
        for (int i = 0; i < this->n; i++){
            temp[i] = this->goal[i];
        }
        temp[this->n++] = g;
        delete[] goal;
        goal = temp;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Game& g){
        out << g.team1 << " - " << g.team2 << endl;
        for (int i = 0; i < g.n; i++){
            out << g.goal[i] << endl;
        }
        return out;
    }
};

int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        n += g;
    }
    cout << n << endl;
    return 0;
}