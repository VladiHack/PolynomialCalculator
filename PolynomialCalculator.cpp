

#include <iostream>
#include <vector>

using namespace std;

constexpr int CHOICE_QUIT = 11;
constexpr int MAX_DEGREE = 1000;


void addPolynomials();
void subtractPolynomials();
void multiplyPolynomials();
void dividePolynomials();
void multiplyPolynomialByScalar();
void findValueAtNumber();
void findGCDOfTwoPolynomials();
void displayVieta();
void representInPowers();
void factorAndFindRoots();
vector<pair<int,int>> readPolynomial();
void printPolynomial(vector<pair<int,int>> polynomial);
pair<int, int> readNumberAsPair();

int main()
{
    cout << "Welcome to Polynomial Calculator - a mini project intended to work with polynomials with rational coefficients \nChoose one of the following functionalities:\n";
    cout << "1) Add polynomials \n2) Subtract polynomials \n3) Multiply polynomials \n4) Divide polynomials \n5) Multiply polynomial by scalar) \n6) Find value of polynomial at a given number \n7) Find GCD of two polynomials \n8) Display Vieta's formulas for a given polynomial \n9) Represent a polynomial in powers of (x+a) \n10) Factor polynomial and find its rational roots \n11) Quit program \n";
    cout << "Enter your option here>> ";
    int choice=0;
    while (choice != CHOICE_QUIT)
    {
        cin >> choice;
        switch (choice)
        {
        case 1: addPolynomials();break;
        case 2: subtractPolynomials();break;
        case 3: multiplyPolynomials();break;
        case 4: dividePolynomials(); break;
        case 5: multiplyPolynomialByScalar();break;
        case 6: findValueAtNumber();break;
        case 7: findGCDOfTwoPolynomials();break;
        case 8: displayVieta();break;
        case 9: representInPowers();break;
        case 10: factorAndFindRoots();break;
        case CHOICE_QUIT: break;
        default: cout << "The number you need to choose is between 1 and 11!" << endl;
            break;
        }
    }
   
}

pair<int, int> readNumberAsPair() {
    int numerator, denominator = 1; // Default denominator is 1
    char slash; // To check for the '/' character

    cin >> numerator; // First, read the numerator or plain integer

    if (cin.peek() == '/') { // Check the next character in the input stream
        cin >> slash >> denominator; // If '/' is found, read the denominator
        if (denominator == 0) {
            cout << "Error: Division by zero is not allowed!" << endl;
            denominator = 1; // Default safe value
        }
    }

    return { numerator, denominator };
}

vector<pair<int,int>> readPolynomial()
{
    int degree;
    cout << "Enter degree of your polynomial>> ";
    cin >> degree;

    vector<pair<int,int>> polynomial;
    pair<int, int> currentNum;

    for (int i = degree;i >= 0;i--)
    {
        cout << "Enter coefficient before x^" << i << ">> ";
        currentNum = readNumberAsPair();
        polynomial.push_back(currentNum);
    }

  
    return polynomial;
}

void printPolynomial(vector<pair<int, int>> polynomial)
{
    int size = polynomial.size();
    if (size == 0)
    {
        // HANDLE EXCEPTION
        cout << "Polynomial is empty";
        return;
    }

    pair<int, int> currentNum = polynomial[0];
    int degree = size -1 ;
    int numerator, denominator = 1;

    for (int i = 0;i < size;i++)
    {
        currentNum = polynomial[i];

        numerator = currentNum.first;
        denominator = currentNum.second;
      

        if(i!=0 && numerator >0){
            cout << "+";
        }

        if (numerator != 1)
        {
            cout << numerator;
        }
        if(denominator !=  1) {
            cout << "/" << denominator;
        }

        if (degree >= 2)
        {
            cout << "x^" << degree;
        }
        else if (degree == 1)
        {
            cout << "x";
        }
   
        degree--;
    }
}



void addPolynomials() {
    cout << "Enter polynomial P(x)" << endl;
    vector<pair<int,int>> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter polynomial Q(x)" << endl;
    vector<pair<int,int>> Q = readPolynomial();
    cout << "Q(X) = ";
    printPolynomial(Q);


   

    
}

void subtractPolynomials() {
    cout << "subtractPolynomials() is not implemented yet.\n";
}

void multiplyPolynomials() {
    cout << "multiplyPolynomials() is not implemented yet.\n";
}

void dividePolynomials() {
    cout << "dividePolynomials() is not implemented yet.\n";
}

void multiplyPolynomialByScalar() {
    cout << "multiplyPolynomialByScalar() is not implemented yet.\n";
}

void findValueAtNumber() {
    cout << "findValueAtNumber() is not implemented yet.\n";
}

void findGCDOfTwoPolynomials() {
    cout << "findGCDOfTwoPolynomials() is not implemented yet.\n";
}

void displayVieta() {
    cout << "displayVieta() is not implemented yet.\n";
}

void representInPowers() {
    cout << "representInPowers() is not implemented yet.\n";
}

void factorAndFindRoots() {
    cout << "factorAndFindRoots() is not implemented yet.\n";
} 

