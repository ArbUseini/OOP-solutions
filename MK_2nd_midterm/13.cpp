#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image{
protected:
    char* name;
    char user[51];
    int width;
    int height;
public:
    Image(const char* name="untitled", const char* user="unknown", int width=800, int height=800){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->user, user);
        this->width = width;
        this->height = height;
    }
    virtual ~Image(){
        delete []name;
    }

    virtual int fileSize()const{
        return width*height*3;
    }

    bool operator>(const Image& i)const{
        return this->fileSize() > i.fileSize();
    }

    friend ostream& operator<<(ostream& out, const Image& i){
        return out << i.name << " " << i.user << " " << i.fileSize() << endl;
    }
};

class TransparentImage: public Image{
    bool supports;
public:
    TransparentImage(const char* name="untitled", const char* user="unknown", int width=800, int height=800, bool supports= true):
            Image(name, user, width, height), supports(supports){}
    ~TransparentImage(){}
    int fileSize()const{
        return (supports)? width*height*4 : width*height*1.125;
    }
};

class Folder{
    char name[256];
    char owner[51];
    Image* is[100];
    int n;
public:
    Folder(const char* name="", const char* owner="unknown"):n(0){
        strcpy(this->name, name);
        strcpy(this->owner, owner);
    }
    int folderSize()const{
        int sum(0);
        for (int i = 0; i < n; i++){
            sum += is[i]->fileSize();
        }
        return sum;
    }
    Image* getMaxFile(){
        Image* ii = is[0];
        for (int i = 0; i < n; i++){
            if (*is[i] > *ii){
                ii = is[i];
            }
        }
        return ii;
    }
    Folder& operator+=(Image& ii){
        is[n++] = &ii;
        return *this;
    }

    Image* operator[](int i){
        if (i >= n){
            return nullptr;
        }
        return is[i];
    }

    friend ostream& operator<<(ostream& out, const Folder& f){
        out << f.name << " " << f.owner << endl << "--" << endl;
        for (int i = 0; i < f.n; i++){
            out << *f.is[i];
        }
        out << "--" << endl << "Folder size: " << f.folderSize() << endl;
        return out;
    }
};

Folder& max_folder_size(Folder* fs, int n){
    double max(-1);
    int idx(0);
    for (int i = 0; i < n; i++){
        if (fs[i].folderSize() > max){
            max = fs[i].folderSize();
            idx = i;
        }
    }
    return fs[idx];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
