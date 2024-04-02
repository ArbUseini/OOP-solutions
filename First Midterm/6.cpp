#include<iostream>
#include<cstring>
using namespace std;

class Camera{
protected:
    char manufacturer[21];
    char model[21];
    int year;
    double resolution;
public:
    const char* getName() const {
        return model;
    };
    virtual double price() const = 0;
    virtual double rentalPrice(int) const = 0;
    bool operator<(const Camera& other) const {
        return this->price() < other.price();
    }
};

class PhotoCamera: public Camera{
    bool raw;

public:
    PhotoCamera(const char* manufacturer, const char* model, int year, float resolution, bool raw){
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
        this->raw = raw;
    }

    double price() const{
        return 100+resolution*20+((raw)?50:0);
    }
    double rentalPrice(int days) const{
        double cost = price()*0.01;
        return cost*days*((days>7)? 0.8:1);
    }
};

class VideoCamera: public Camera{
    int lent;

public:
    VideoCamera(const char* manufacturer, const char* model, int year, float resolution, int lent){
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
        this->lent = lent;
    }
    double price() const{
        return resolution*80*((lent > 3600)?1.4:1);
    }
    double rentalPrice(int days) const{
        double cost = price()*0.01;
        return cost*days*((days>7)? 0.8:1);
    }
};

class FilmCamera: public Camera{
    int frame;

public:
    FilmCamera(const char* manufacturer, const char* model, int year, float resolution, int frame){
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
        this->frame = frame;
    }
    double price() const{
        return 100+resolution*20+((frame > 30)?5000+(frame-30)*30:0);
    }
    double rentalPrice(int days) const{
        return days*500*((frame>60)? 2: 1);
    }
};

double production(Camera** cameras, int n, int days){
    double sum(0);
    for (int i = 0; i < n; i++){
        sum += cameras[i]->rentalPrice(days);
    }
    return sum;
}

const char* mostExpensiveCamera(Camera** cameras, int n){
    double max(-1);
    int idx(0);
    for (int i = 0; i < n; i++){
        if (cameras[i]->price() > max){
            max = cameras[i]->price();
            idx = i;
        }
    }
    return cameras[idx]->getName();
}

int main(int argc, char *argv[])
{
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c [10];

    // Read number of cameras
    cin>>n;

    for(int i = 0; i < n; ++i){

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout << "Price of production is: " << production(c, n, days);
    cout<<"\n" << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}
