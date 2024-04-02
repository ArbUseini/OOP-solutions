#include <iostream>
#include <cstring>
using namespace std;

class List{
    int *arr;
    int n;
public:
    List(){
        this-> n = 0;
        this->arr = nullptr;
    }
    List(int *arr, int n){
        this-> n = n;
        this->arr = new int[n];
        for (int i = 0; i < n; i++){
            this->arr[i] = arr[i];
        }
    }
    List(const List& list){
        this-> n = list.getN();
        this->arr = new int[this->n];
        for (int i = 0; i < n; i++){
            this->arr[i] = list.getArr()[i];
        }
    }
    ~List(){
        delete[] arr;
    }
    List& operator=(const List& list){
        if (this != &list){
            delete[] arr;
            arr = new int[list.getN()];
            for (int i = 0; i < list.getN(); i++){
                arr[i] = list.getArr()[i];
            }
            this->n = list.getN();
        }
        return *this;
    }
    int *getArr() const {
        return arr;
    }

    int getN() const {
        return n;
    }

    int sum(){
        int mlidh(0);
        for (int i = 0; i < n; i++){
            mlidh+=arr[i];
        }
        return mlidh;
    }
    double average(){
        double avg = sum();
        return avg/n;
    }
    void print(){
        cout <<  n << ": ";
        for (int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << endl;
    }

};

class ListContainer{
    List *array;
    int n;
    int attempt;
public:
    ListContainer(): n(0), attempt(0){
        array = nullptr;
    }
    ListContainer(const ListContainer& list){
        this->array = new List[list.getN()];
        this->n = list.getN();
        this->attempt = list.getAttempt();
        for (int i = 0; i < this->n; i++){
            array[i] = list.getArray()[i];
        }
    }
    ~ListContainer(){
        delete []array;
    }

    ListContainer& operator=(const ListContainer& list){
        if (this != &list){
            delete[] array;
            this->array = new List[list.getN()];
            this->n = list.getN();
            this->attempt = list.getAttempt();
            for (int i = 0; i < this->n; i++){
                array[i] = list.getArray()[i];
            }
        }
        return *this;
    }

    List *getArray() const {
        return array;
    }

    int getN() const {
        return n;
    }

    int getAttempt() const {
        return attempt;
    }
    void print(){
        for (int i = 0; i < n; i++){
            cout << "List number: " << i+1 << " List info: "; array[i].print();

        }
        if (n == 0){
            cout << "The list is empty" << endl;
        }
        else{
            cout << "Sum: "<< sum() << " Average: " << average() <<
                 "\nSuccessful attempts: " << n << " Failed attempts: " << attempt << endl;
        }

    }
    void addNewList(List l){
        for (int i = 0; i < n; i++){
            if (array[i].sum() == l.sum()){
                attempt++;
                return;
            }
        }
        List *temp = this->array;
        this->array = new List[n+1];
        for (int i = 0; i < n; i++){
            this->array[i] = temp[i];
        }
        array[n++] = l;
    }
    int sum(){
        int mlidh(0);
        for (int i = 0; i < n; i++){
            mlidh+=array[i].sum();
        }
        return mlidh;
    }
    double average(){
        double avg = 0;
        int ele(0);
        for (int i = 0; i < n; i++){
            avg += array[i].sum();
            ele += array[i].getN();
        }
        avg/=ele;

        return avg;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}

