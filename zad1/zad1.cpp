#include <iostream>
#include <cmath>
#include<functional>
#include<map>
#include<vector>



using mojafunkcja_t = std::function<double(std::vector<double>)>;
using mojamapa_t = std::map<std::string, std::vector<double>>;

void wypisz(const mojamapa_t mapa, const mojafunkcja_t fun) {
    using namespace std;
    for (auto kv : mapa) {
        auto [k, v] = kv;
        cout << "Wynik " <<fun(v) << endl;

    }
}
int main(int argc, char** argv) {
    using namespace std;
        vector <double> wartosci;
        //= { stod (argv[2]), stod (argv[3]) };
        for(int i=2; i<argc; i++)
        {
            wartosci.push_back(stod(argv[i]));
        }

        vector<string> argumenty (argv, argv + argc);
        map<string, mojafunkcja_t> formatery;
        formatery["add"] = [](vector<double> x) { return  x[0] + x[1]; };
        formatery["sin"] = [](vector<double> x) { return  sin(x[0]);  };
        formatery["mod"] = [](vector<double> x) { return  int(x[0])%int(x[1]); };


 map<string, vector <double>> mapa = {{argv[1], wartosci }};

try {
    auto selected_f = argumenty.at(1);
    wypisz(mapa, formatery.at(selected_f));
  } catch (std::out_of_range aor) {
    cout << "Dostepne funkcje to: ";
    for (auto [k, v] : formatery) cout <<" "<<  k;
  }
  return 0;
}