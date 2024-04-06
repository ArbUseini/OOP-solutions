#include <iostream>
using namespace std;

struct Player {
  char name[15];
  int currentLevel;
  int points;
};

struct ComputerGame {
  char game[20];
  Player players[30];
  int numberOfPlayers;
};

void bestPlayer(ComputerGame *array, int n) {
  int maxPlayers = 0;
  int bestPlayerIndex = -1;
  int maxPoints = -1;
  int maxLevel = 1;
  int bestGameIndex;

  for (int i = 0; i < n; i++) {
    if (array[i].numberOfPlayers > maxPlayers) {
      maxPlayers = array[i].numberOfPlayers;
      bestGameIndex = i;
      bestPlayerIndex = -1; // reset
    }
    if (array[i].numberOfPlayers == maxPlayers) {
      for (int j = 0; j < array[i].numberOfPlayers; j++) {
        if (array[i].players[j].points > maxPoints ||
            (array[i].players[j].points == maxPlayers &&
             array[i].players[j].currentLevel > maxLevel)) {
          maxPoints = array[i].players[j].points;
          maxLevel = array[i].players[j].currentLevel;
          bestPlayerIndex = j;
          bestGameIndex = i;
        }
      }
    }
  }

  if (bestPlayerIndex != -1) {
    cout << "Najdobar igrac e igracot so korisnicko ime "
         << array->players[bestPlayerIndex].name << " koj ja igra igrata "
         << array[bestGameIndex].game << endl;
  }
}

int main() {
  int n, m;
  char ime[20];
  cin >> n;
  // create an array of max 100 computer games;
  ComputerGame poleigri[100];
  for (int i = 0; i < n; i++) {
    ComputerGame nova;
    cin >> nova.game >> nova.numberOfPlayers;
    Player pole[30];
    for (int j = 0; j < nova.numberOfPlayers; j++) {
      Player nov;
      cin >> nov.name >> nov.currentLevel >> nov.points;
      nova.players[j] = nov;
    }
    poleigri[i] = nova;
  }

  bestPlayer(poleigri, n);
  return 0;
}
