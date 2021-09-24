#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Electromagnetic interaction
// You have to create world and be able to add and delete particles from it
// When you add or delete particle you must recalculate all interactions

// Требуется описать мир с некоторыми частицами
// Координата/скорость задается через структуру vector3

struct vector3 {
    double x;
    double y;
    double z;
};

// Для описания событий происходящих в мире напишите свой небольшой логгер, который умеет
// Запоминать создание, изменение и уничтожение частиц

/*class Logger {
public:
    Logger() = default;
    void log(const std::string& s){
        l.push_back(s);
    }
    ~Logger();
private:
    std::vector<std::string> l;
};*/

// Существует базовый класс частиц, который внутри себя хранит информацию о частице
// Допишите этот родительский класс так, чтобы он мог считать количество объектов, созданных от него

class Particle {
protected:
    // Поля, описывающие частицу
    // Можно дописать свои
    double mass = 0;
    double charge = 0;
    vector3 coordinate = {0, 0, 0};
    vector3 velocity = {0, 0,0};
    vector3 force = {0, 0, 0};
    std::string name;
    // Логгер для записи событий
    //Logger logger;

public:
    Particle() = default;
    //explicit Particle(double energy);
    // метод, который вам необходимо переопределить в дочерних классах
    // см. или вспомнить лекцию
    // внутри него напишите логику взаимодействия двух частиц (например, кулоновское)
    virtual void interaction(Particle& p){
    };
    void setForceDefault(){
        force = {0, 0, 0};
    }
    void Step(double time){
        coordinate.x = coordinate.x + velocity.x * time + force.x / mass * time * time / 2;
        coordinate.y = coordinate.y + velocity.y * time + force.y / mass * time * time / 2;
        coordinate.z = coordinate.z + velocity.z * time + force.z / mass * time * time / 2;
        velocity.x = velocity.x + force.x / mass * time;
        velocity.y = velocity.y + force.y / mass * time;
        velocity.z = velocity.z + force.z / mass * time;
    }

    std::string getName() const{
        return name;
    }
    void setName(std::string new_name){
        name = new_name;
    }

    double getEnergy() const{
        double Velocity = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2) + pow(velocity.z, 2));
        return mass * Velocity * Velocity / 2;
    }
    vector3 getCoords(){
        return coordinate;
    }
    double getCharge(){
        return charge;
    }
    vector3 getForce(){
        return force;
    }
};

// описать несколько классов разных частиц
// например такой
class Electron : public Particle {
public:
    // в этом конструкторе предлагается задавать координаты и через энергию остальные параметры частицы
    explicit Electron(vector3 veloc, vector3 coords){
        name = "electron";
        charge = -1;
        mass = 1;
        velocity = veloc;
        coordinate = coords;
    }
    void interaction(Particle& p) override{
        vector3 ParticleCoords = p.getCoords();
        double Distance = pow(ParticleCoords.x - coordinate.x, 2) + pow(ParticleCoords.y - coordinate.y, 2) + pow(ParticleCoords.z - coordinate.z, 2);
        double ForceV = charge * p.getCharge() / Distance;
        double fx = -(ParticleCoords.x - coordinate.x) * ForceV / sqrt(Distance);
        double fy = -(ParticleCoords.y - coordinate.y) * ForceV / sqrt(Distance);
        double fz = -(ParticleCoords.z - coordinate.z) * ForceV / sqrt(Distance);
        force.x = force.x + fx;
        force.y = force.y + fy;
        force.z = force.z + fz;
    }
    ~Electron(){};
};

class Proton : public Particle{
public:
        explicit Proton(vector3 veloc, vector3 coords){
        name = "proton";
        charge = 1;
        mass = 100;
        velocity = veloc;
        coordinate = coords;
    }
    void interaction(Particle& p) override{
        vector3 ParticleCoords = p.getCoords();
        double Distance = pow(ParticleCoords.x - coordinate.x, 2) + pow(ParticleCoords.y - coordinate.y, 2) + pow(ParticleCoords.z - coordinate.z, 2);
        double ForceV = charge * p.getCharge() / Distance;
        double fx = -(ParticleCoords.x - coordinate.x) * ForceV / sqrt(Distance);
        double fy = -(ParticleCoords.y - coordinate.y) * ForceV / sqrt(Distance);
        double fz = -(ParticleCoords.z - coordinate.z) * ForceV / sqrt(Distance);
        force.x = force.x + fx;
        force.y = force.y + fy;
        force.z = force.z + fz;
    }
    ~Proton(){};
};

// в этом классе опишите мир, состоящий из некоторого числа частиц
class World {
private:
    std::vector<Particle*> v;
    int electrons = 0;
    int protons = 0;
public:
    // добавить частицу в мир (она должна провзаимодействовать со всеми остальными)
    void addParticle(Particle& p){
        std :: string prev = p.getName();
        if (prev == "electron"){
            electrons++;
            prev = prev + std::to_string(electrons);
        }
        if (prev == "proton"){
            protons++;
            prev = prev + std::to_string(protons);
        }
        p.setName(prev);
        v.push_back(&p);
    }
    // удалить частицу из мира
    void deleteParticle(const Particle& p){
        for (int i = 0; i < v.size(); i++){
            if(v[i]->getName() == p.getName()){
                v.erase(v.begin() + i);
            }
        }
    }
    void Step(double time){
        for (int i = 0; i < v.size(); i++)
        {
            v[i]->setForceDefault();
        }
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v.size(); j++)
            {
                if (i != j)
                {
                    v[i]->interaction(*v[j]);
                }
            }
        }
        for (int i = 0; i < v.size(); i++)
        {
            v[i]->Step(time);
        }
    };
    std::vector<Particle*>* getArray(){
        return &v;
    };
};

// перегрузите оператор вывода, чтобы можно было вывести состав мира
// (может потребоваться перегрузка оператора вывода для частиц)
std::ostream& operator<<(std::ostream& os,  World& w){
    for (int i = 0; i < w.getArray()->size(); i++)
    {
        os << "Particle " << i + 1 << ": " << w.getArray()->at(i)->getName() << std::endl <<
            "x = " << w.getArray()->at(i)->getCoords().x << ", y = " << w.getArray()->at(i)->getCoords().y <<
            ", z = " << w.getArray()->at(i)->getCoords().z << std::endl <<
            "fx = " << w.getArray()->at(i)->getForce().x << ", fy = " << w.getArray()->at(i)->getForce().y <<
            ", fz = " << w.getArray()->at(i)->getForce().z << std::endl;

    }
    return os;
}

// здесь создайте мир/миры, куда добавьте некоторое число частиц, взаимодействующих друг с другом
int main() {
    setlocale(LC_ALL, "Russian");
    vector3 acoords = { 0,10,7 };
    vector3 aveloc = { 0,0,0 };
    Electron a(aveloc,acoords);
    vector3 ocoords = { 0,5,12 };
    vector3 oveloc = { 0,0,0 };
    Proton o(oveloc, ocoords);
    World world;
    world.addParticle(a);

    world.addParticle(o);
    for (int i = 0; i < 100000; i++)
    {
        world.Step(0.0001);

        if (i % 1000 == 0)
        {

            std::cout << world;
        }
    }

}
