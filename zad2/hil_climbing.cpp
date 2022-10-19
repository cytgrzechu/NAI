#include <functional>
    #include <iomanip>
    #include <iostream>
    #include <list>
    #include <random>
    #include <vector>

    using namespace std;

    random_device rd;
    mt19937 gen(rd()); 

    ostream& operator<<(ostream& o, vector<double> v)
    {
        for (auto e : v) {
            o << std::fixed << std::setprecision(5) << "\t" << e;
        }
        return o;
    }

    vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
    {
        auto p = p0;
        uniform_int_distribution<> distrib(0, p.size() - 1);
        uniform_real_distribution<> distrib_r(-0.1, 0.1);

        if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");
        for (int i = 0; i < iterations; i++) {
            auto p2 = p;

            p2[distrib(gen)] += distrib_r(gen);
            if(!f_domain(p2)){
            double y2 = f(p2);
            if (y2 < f(p)) {
                p = p2;
            }
            }
        }
        return p;
    }

    int main()
    {
       
//Ackley function
        auto ackley = [](vector<double> v) {
            double x = v.at(0), y = v.at(1);
            return -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
        };

        auto ackley_domain = [](vector<double> v) {
            return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
        };

        uniform_real_distribution<> distrib_r(-5, 5);
        vector<double> ackley_p0 = {
            distrib_r(gen),
            distrib_r(gen),
        };

    auto result = hill_climbing(ackley, ackley_domain, ackley_p0, 100000);
    cout << " Ackley function" << result << " -> " << ackley(result)  <<endl;
//Himmelblau's function
    auto himmelblau = [](vector <double> v){
            double x = v.at(0),y= v.at(1);
            return (x*x+y-11)*(x*x+y-11)+(x+y*y-7)*(x+y*y-7);
        };
        auto himmelblau_domain = [](vector <double> v){
        return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
        };
        
        uniform_real_distribution<> distrib_h(-5, 5);
        vector<double> himmelblau_p0 = {
            distrib_h(gen),
            distrib_h(gen),
        };


    auto result2 =  hill_climbing(himmelblau, himmelblau_domain, himmelblau_p0, 10000);
    cout<< " Himmelblau's function" << result2 << " -> " << himmelblau(result) << endl;
    
//Matyas function 
auto matyas = [](vector<double> v) {
            double x = v.at(0), y = v.at(1);
            return 0.26*(pow(x,2) + pow(y,2) - 0.48*x*y);
        };

        auto matyas_domain = [](vector<double> v) {
            return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
        };

        uniform_real_distribution<> distrib_a(-10, 10);
        vector<double> matyas_p0 = {
            distrib_a(gen),
            distrib_a(gen),
        };

    auto result3 = hill_climbing(matyas, matyas_domain, matyas_p0, 100000);
    cout<< " Matyas function " << result << " -> " << matyas(result3) << endl;

        


   
        return 0;
    }