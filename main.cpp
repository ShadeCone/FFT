#include <format>
#include <iostream>
#include <complex>
#include <vector>
#include <fstream>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

void DFT_init(vector<cd> & x);
void DFT(vector<cd> & x, bool inverse);

void DFT_init(vector<cd> & x) {
    int N;
    double real, imag;
    bool inverse;

    cout << "enter N: ";
    cin >> N;
    cout << "0: Forward, 1: Inverse. Choose one: ";
    cin >> inverse;
    for (int i = 0; i < N; i++) {
        cout << "Real part: ";
        cin >> real;
        cout << "Imaginary part: ";
        cin >> imag;
        cd temp(real, imag);
        x.push_back(temp);
    }
    cout << "N: " << N << endl;
    if (N < 10) {
        for (int i = 0; i < N; i++) {
            cout << format("{}: ({:.2f} + {:.2f}i)", i, x[i].real(), x[i].imag()) << endl;
        }
    }
    if (inverse == 0) {
        cout << "------Performing DFT------" << endl;
    }
    if (inverse == 1) {
        cout << "------Performing IDFT------" << endl;
    }
    DFT(x, inverse);
    if (N < 10) {
        for (int i = 0; i < N; i++) {
            cout << format("{}: ({:.2f} + {:.2f}i)", i, x[i].real(), x[i].imag()) << endl;
        }
    }
    
}

void DFT(vector<cd> & x, bool inverse) {
    int N = x.size();
    vector<cd> x_k(N, cd(0, 0));
    for (int k = 0; k < N; k++) {
        double arg = -2*(1-2*inverse)*PI*k/N;
        for (int n = 0; n < N; n++) { // 0 to n-1 of x_n * e^(-i * 2 * pi * k * n / N)
            double a = x[n].real();
            double b = x[n].imag();
            x_k[k] += cd(a * cos(arg*n) - b * sin(arg*n), a * sin(arg * n) + b * cos(arg * n));
        }
        if (inverse) {x_k[k] /= N;}
    }
    x = x_k;
}

int main() {
    int max_options = 1;
    int option = -1;

    cout << "0: Manual DFT\n";
    cout << "1: DFT, read from file\n";
    cout << "Choose option: ";
    cin >> option;

    int N;
    vector<cd> x;
    if (option == 0) {
        DFT_init(x);
    }
    
    N = x.size();

    ofstream myfile;
    myfile.open("data.csv");
    myfile << "real,imag\n";
    for (int i = 0; i < N; i++) {
        myfile << format("{},{}\n", x[i].real(), x[i].imag());
    }
}