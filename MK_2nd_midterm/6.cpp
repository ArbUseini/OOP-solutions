#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class ExistingGame{
private:
    char msg[256];
public:
    ExistingGame(char msg_txt[]){
        strncpy(this->msg, msg_txt, 255);
        this->msg[255] = '\0';
    }

    void message(){
        cout<<this->msg<<std::endl;
    }
};

class Game{
protected:
    char name[101];
    double g_price;
    bool sale;
public:
    Game(const char* name="", double g_price=0, bool sale=false):g_price(g_price), sale(sale){
        strcpy(this->name, name);
    }
    Game(const Game& g):g_price(g.g_price), sale(g.sale){
        strcpy(this->name, g.name);
    }
    Game& operator=(const Game& g){
        if (this != &g){
            strcpy(this->name, g.name);
            g_price = g.g_price;
            sale = g.sale;
        }
        return *this;
    }
    virtual double get_price()const{
        if (sale){
            return g_price * 0.3F;
        }
        return g_price;
    }

    bool operator==(const Game&g)const{
        return strcmp(this->name, g.name)==0;
    }

    friend istream& operator>>(istream& in, Game& g){
        in.get();
        in.getline(g.name, 100);
        in >> g.g_price >> g.sale;
        return in;
    }
    friend ostream& operator<<(ostream& out, Game& g){
        return out << "Game: " << g.name << ", regular price: $" << g.g_price << ((g.sale)? ", bought on sale":"");
    }
};

class SubscriptionGame: public Game{
    double fee;
    int month, year;
public:
    SubscriptionGame(const char* name="", double g_price=0, bool sale=false, double fee=0, int month=0,
                     int year=0):Game(name, g_price, sale), fee(fee), month(month), year(year){}
    SubscriptionGame(const SubscriptionGame& sg):Game(sg.name, sg.g_price, sg.sale), fee(sg.fee), month(sg.month), year(sg.year){}
    SubscriptionGame& operator=(const SubscriptionGame& sg){
        if (this != &sg){
            Game::operator=(sg);
            fee = sg.fee;
            month = sg.month;
            year = sg.year;
        }
        return *this;
    }
    double get_price()const{
        double price = Game::get_price();
        int months(0);
        if (year<2018){
            months = (12 - this->month) + (2017 - year)*12 + 5;
        }
        else {
            months = 5 - this->month;
        }
        price += months * fee;
        return price;
    }
    friend istream& operator>>(istream& in, SubscriptionGame& sg){
        in.get();
        in.getline(sg.name, 100);
        in >> sg.g_price >> sg.sale >> sg.fee >> sg.month >> sg.year;
        return in;
    }
    friend ostream& operator<<(ostream& out, SubscriptionGame& sg){
        Game * tmp = dynamic_cast<Game*>(&sg);
        out << *tmp;
        out <<", monthly fee: $"<< sg.fee << ", purchased: " << sg.month << "-" << sg.year << endl;
        return out;
    }
};

class User{
    char name[101];
    Game** gs;
    int n;
public:
    User(const char* name=""):gs(nullptr), n(0){
        strcpy(this->name, name);
    }
    User(const User& u):gs(nullptr), n(0){
        strcpy(this->name, u.name);
    }
    User& operator+=(Game& g){
        for (int i = 0; i < n; i++){
            if (g == *gs[i]){
                throw ExistingGame("The game is already in the collection");
            }
        }
        Game** temp = new Game*[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = gs[i];
        }
        temp[n++] = &g;
        delete[] gs;
        gs = temp;
        return *this;
    }
    double total_spent()const{
        double sum(0);
        for (int i = 0; i < n; i++){
            sum += gs[i]->get_price();
        }
        return sum;
    }
    friend ostream& operator<<(ostream& out, const User& u){
        out << endl << "User: " << u.name << endl;
        for (int i = 0; i < u.n; i++){
            SubscriptionGame* sg = dynamic_cast<SubscriptionGame*>(u.gs[i]);
            if (sg){
                out << "- " << *sg;
            }else{
                out << "- " << *u.gs[i] << endl;
            }
        }
        out << endl;
        return out;
    }
};

int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          u+=(*g);
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}
