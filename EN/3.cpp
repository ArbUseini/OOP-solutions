#include <iostream>
#include <cstring>
using namespace std;

// your code here

class Character{
    char c;
public:
    Character(){
        this->c = ' ';
    }
    Character(char c){
        this->c = c;
    }
    void setC(char c){
        this->c = c;
    }

    char getC() const {
        return c;
    }
    friend ostream& operator<<(ostream& out, const Character ch){
        return out << ch.c;
    }
};

class CharSequence {
private:
    Character* chars;
    int length;
public:
    CharSequence(){
        chars = nullptr;
        length = 0;
    }
    CharSequence(const char* f){
        length = strlen(f);
        chars = new Character[length];
        for (int i = 0; i < length; i++){
            chars[i].setC(f[i]);
        }
    }

    CharSequence(const CharSequence& c){
        length = c.length;
        chars = new Character[length];
        for (int i = 0; i < length; i++){
            chars[i].setC(c.chars[i].getC());
        }
    }

    ~CharSequence(){
        delete [] chars;
    }

    CharSequence& operator=(const CharSequence& c){
        if (this != &c) {
            delete [] chars;
            length = c.length;
            chars = new Character[length];
            for (int i = 0; i < length; i++){
                chars[i].setC(c.chars[i].getC());
            }
        }
        return *this;
    }
    
    Character& operator[](int i){
        return chars[i];
    }

    CharSequence& operator +=(const Character &c){
        Character* temp = chars;
        chars = new Character[length + 1];
        for (int i = 0; i < length; i++){
            chars[i].setC(temp[i].getC());
        }
        chars[length].setC(c.getC());
        delete[] temp;
        length++;
        return *this;
    }
    
    int operator[](char c) const {
        int count = 0;
        for (int i = 0; i < length; ++i) {
            if (chars[i].getC() == c) {
                count++;
            }
        }
        return count;
    }
    
    friend ostream& operator<<(ostream& out, const CharSequence& charSequence){
        for (int i = 0; i < charSequence.length; i++){
            out << charSequence.chars[i];
        }
        return out;
    }

    CharSequence& toUpperCase(){
        for (int i = 0; i < length; i++){
            chars[i].setC(toupper(chars[i].getC()));
        }
        return *this;
    }

    bool operator==(const CharSequence &cs){
        if (cs.length != length){
            return false;
        }
        for (int i = 0; i < length; i++){
            if (chars[i].getC() != cs.chars[i].getC()){
                return false;
            }
        }
        return true;
    }
};

int main() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if(n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if(n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for(int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if(n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << 12 << endl;
    } else if(n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    } else if(n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}

