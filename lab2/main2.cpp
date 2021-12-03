#include <iostream>
#include <vector>
#include <string>
#include <cmath>

template<typename T>
class Grid {
private:
    T *memory;
    size_t x_size, y_size;

public:
    Grid(size_t x_size = 1, size_t y_size = 1): x_size(x_size), y_size(y_size)
    {
        memory = new T[x_size * y_size];
    };
    ~Grid()
    {
        delete [] memory;
    }

    T operator()(size_t x_idx, size_t y_idx) const//возвращает значение в ячейке с инлесами x y просто возвращает нельзя менять
    {
        return memory[x_idx * y_size + y_idx];
    };
    T& operator()(size_t x_idx, size_t y_idx)// получаем по адресу в ячейке x y число и можем его поменять
    {
        return memory[x_idx * y_size + y_idx];
    };

    size_t get_xsize() const
    {
        return x_size;
    };
    size_t get_ysize() const
    {
        return y_size;
    };

    T* get_memory() const {
        return memory;
    }

    Grid& operator=(T x){// оператор равно
        for (int i = 0; i < x_size; i++){
            for (int j = 0; j < y_size; j++){
                memory[i * y_size + j] = x;
            }
        }
        return *this;
    };

    Grid& operator = (Grid& x){
        delete[] memory;
        memory = new T[x.get_xsize() * x.get_ysize()];
        x_size = x.get_xsize();
        y_size = x.get_ysize();
        for (int i = 0; i < x_size; i++){
            for (int j = 0; j < y_size; j++){
                memory[i * y_size + j] = x(i, j);
            }
        }
        return *this;
    };

    template<typename P>// дружественный оператор , извне имеет доступ к приватным полям класса его нужно будет перееопределить
    friend std::ostream& operator<<(std::ostream&, Grid<P> const& g);
    template<typename P>
    friend std::istream& operator>>(std::istream&, Grid<P> &);

    T average() {
        T summ = 0;
        for (int i = 0; i < x_size; i++){
            for (int j = 0; j < y_size; j++){
                summ += memory[i * y_size + j];
            }
        }
        return summ/(x_size * y_size);
    }
};

// далее объявляю два оператор на ввод и еа вывод
template <typename V>
std::istream& operator>>(std::istream& is, Grid<V>& g) {
    V x;
    for (int i = 0; i < g.x_size; i++) {
            for (int j = 0; j < g.y_size; j++) {
                is >> x;
                g.memory[i * g.y_size + j] = x;
            }
        }
    return is;
 };

template <typename U>
std::ostream& operator<<(std::ostream& os, Grid<U> const& g) {
    for (int i = 0; i < g.get_xsize(); i++) {
            for (int j = 0; j < g.get_ysize(); j++) {
                os << g(i, j) << " ";
            }
            os << "\n";
        }
    if ((g.get_xsize() == 0) && (g.get_ysize() == 0)) os << "Empty";
    return os;
 };

 template <typename U>
 class Grid_sub {
private:
    Grid<U> *memory;
    size_t x_size, y_size;

    public:
    Grid_sub(size_t x_size, size_t y_size): x_size(x_size), y_size(y_size){
        memory = new Grid<U>[x_size * y_size];
    };

    U operator()(size_t x_idx, size_t y_idx) const {
        return memory[x_idx * y_size + y_idx](0, 0);
    };

    U& operator()(size_t x_idx, size_t y_idx){
        return memory[x_idx * y_size + y_idx](0, 0);
    };

    size_t get_xsize() const {
        return x_size;
    };

    size_t get_ysize() const {
        return y_size;
    };

    Grid_sub& make_subgrid(size_t x_idx, size_t y_idx, size_t x_sub_size, size_t y_sub_size){
        Grid<U> g(x_sub_size, y_sub_size);
        U x = memory[x_idx * y_size + y_idx](0, 0);
        g = x;
        memory[x_idx * y_size + y_idx] = g;
        return *this;
    };

    Grid<U>& collapse_subgrid(size_t x_idx, size_t y_idx){
        Grid<U> g(1, 1);
        g = memory[x_idx * y_size + y_idx].average();
        memory[x_idx * y_size + y_idx] = g;
    };

    Grid<U>& get_subgrid(size_t x_idx, size_t y_idx){
        return memory[x_idx * y_size + y_idx];
    }

    bool is_subgrid(size_t x_idx, size_t y_idx) const {
        bool a = false;
        if ((memory[x_idx * y_size + y_idx].get_xsize() > 1) || (memory[x_idx * y_size + y_idx].get_xsize() > 1)) a = true;
        return a;
    };

    template<typename P>
    friend std::ostream& operator<<(std::ostream& os, Grid_sub<P> const& g);
    template<typename P>
    friend std::istream& operator>>(std::istream& is, Grid_sub<P> & g);

    ~Grid_sub() {
        delete[] memory;
    };

 };

 template <typename V>
 std::istream& operator>>(std :: istream& is, Grid_sub<V>& g){
    V x;
    for (int i = 0; i < g.x_size; i++){
        for (int j = 0; j < g.y_size; j++){
            is >> x;
            g(i, j) = x;
        }
    }
    return is;
 };

 template <typename U>
 std::ostream& operator<<(std::ostream& os, Grid_sub<U> const& g){
    for (int i = 0; i < g.get_ysize(); i++){
        for (int j = 0; j < g.get_ysize(); j++){
            os << g(i,j) << " ";
        }
        os << "\n";
    }
    return os;
 };

 int main(){
    Grid_sub<int> g(2, 2);
    std::cin >> g;

    std::cout << g(0, 0) << '\n';
    g.make_subgrid(0, 0, 2, 2);
    std::cout << g.get_subgrid(0, 0);
return 0;
 }




















