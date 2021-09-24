# include <iostream>
# include <set>
# include <random>
#include <iostream>
#include <fstream>
#include <vector>

class State {
public:
    virtual bool contains(int s) const{
            return false;
    }
};

class DiscreteState : public State{
private:
    int const state ;

public:
    DiscreteState(int state) : state(state) { }

    virtual  bool contains(int s) const {
        return s == state ;
    }

};

class SegmentState : public State {
private:
    int const beg , end ;

public :
    SegmentState () : beg(0) , end(-1) { }
    SegmentState (int beg , int end) : beg (beg) , end(end) { }

    virtual bool contains(int s) const {
        return s >= beg && s <= end ;
    }
};

class SegmentModState : public State {
private:
    int const beg, end;

    std::set<int> const incl;
    std::set<int> const excl;


public:
    SegmentModState() : beg(0), end(-1){}
    SegmentModState(int beg, int end, std::set<int> const &inc, std::set<int> const &exc ): beg(beg), end(end), incl(inc), excl(exc)  { }
    virtual bool contains(int s) const {
        return ((s >= beg && s <= end) || (incl.count(s) > 0)) && (excl.count(s) == 0);
    }
};
class SetState : public State {
private :
    std::set<int> const states ;

public :
    SetState(): states() { }
    SetState(std::set <int> const &src): states(src) { }

    virtual bool contains(int s) const {
        return states.count(s) > 0;
    }

};

class ProbabilityTest {
private:
    unsigned seed ;
    int test_min , test_max ;
    unsigned test_count ;

public :
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count ) : seed ( seed ) , test_min ( test_min ) , test_max (test_max ) , test_count ( test_count ) { }
    float operator () (State const &s ) const {
        std :: default_random_engine rng (seed ) ;
        std :: uniform_int_distribution<int> dstr (test_min, test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count ; ++cnt)
            if (s.contains(dstr(rng))) ++good ;

        return static_cast <float>(good) / static_cast <float>(test_count);
    }
};

int main (int argc , const char * argv []) {
    DiscreteState d(1) ;
    SegmentState s(0, 10) ;
    SetState ss ({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});

    std::ofstream out;
    out.open("Discrete2.txt");
    for (int i = 1; i < 101; i++){
        ProbabilityTest pt(9, 0, i, 10000);

        out << i << " " << pt(d) << std::endl;
    }
    out.close();

    std::cout << "1 test completeted" << std::endl;

    out.open("Segment2.txt");
    for (int i = 1; i < 101; i++){
        ProbabilityTest pt(9, 0, i, 10000);

        out << i << " " << pt(s) << std::endl;
    }
    out.close();
    std::cout << "2 test completeted" << std::endl;

    out.open("Set2.txt");
    for (int i = 1; i < 101; i++){
        ProbabilityTest pt(9, 0, i, 10000);

        out << i << " " << pt(ss) << std::endl;
    }
    out.close();
    std::cout << "3 test completeted" << std::endl;


    return 0;
}
