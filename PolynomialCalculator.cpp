

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
pair<int, int> readRationalNumber();
int gcdNums(int a, int b);
int minNumber(int a, int b);
int lcmNums(int a, int b);

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

pair<int, int> readRationalNumber() {
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
        currentNum = readRationalNumber();
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
      

        

        if ( numerator!= 0)
        {

            if (i != 0 && numerator > 0 && (numerator != 1 || denominator != 1)) {
                cout << "+";
            }

            if (numerator != 1 || denominator != 1)
            {
                cout << numerator;
            }

            if (denominator != 1) {
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
        }
    
   
        degree--;
    }

    cout << endl;
}

int minNumber(int a, int b)
{
    if (a > b)
    {
        return b;
    }
    return a;
}

int abs(int a)
{
    if (a > 0)
    {
        return a;
    }
    return -a;
}

int gcdNums(int a, int b)
{
    if (a == 0 || b == 0)
    {
        return 1;
    }

    a = abs(a);
    b = abs(b);

    // Find Minimum of a and b
    int res = minNumber(a, b);

    // Testing divisiblity with all numbers starting from
  // min(a, b) to 1

    while (res > 1) {

        // If any number divide both a and b, so we
        // got the answer
        if (a % res == 0 && b % res == 0)
            break;
        res--;
    }
    return res;
}

int lcmNums(int a, int b)
{

    return a * b / gcdNums(a, b);
}

vector<pair<int, int>> addDegree(vector<pair<int, int>> P, int degree)
{
    //since we have increased the degree,the new P will be of type old P * x^degree + 0x^0 + ... 0x^1 + ... + 0x^degree-1  
    pair<int, int> zeroCoefficient = { 0,1 };
    for (int i = 0;i < degree;i++)
    {
        P.push_back(zeroCoefficient);
    }

    return P;
}

pair<int, int> ReturnSumOfElements(pair<int, int> elP, pair<int, int> elQ)
{
    pair<int, int> elR;
    int numeratorP, denominatorP, numeratorQ, denominatorQ;
    
    numeratorP = elP.first;
    denominatorP = elP.second;
    numeratorQ = elQ.first;
    denominatorQ = elQ.second;

    //each number is presented in this format : {numerator} / { denominator }
    // in order to find the sum of the elements they need to have matching denominators
    
    if (denominatorP != denominatorQ)
    {
        // we find the lcm of the denominators and then multiply the numerators with the ( lcm / denominator ) 
        int lcmDenominators = lcmNums(denominatorP, denominatorQ);

        numeratorP *= lcmDenominators / denominatorP;
        numeratorQ *= lcmDenominators / denominatorQ;
        denominatorP = lcmDenominators;
        denominatorQ = lcmDenominators;
    }

    //when the denominators are equal, we can find the sum of their numerators
    elR.first = numeratorP + numeratorQ;
    elR.second = denominatorP;

    return elR;
}

vector<pair<int, int>> returnSumOfPolynomials(vector<pair<int, int>> P, vector<pair<int, int>> Q)
{
    //resulting vector
    vector<pair<int, int>> R;

    int sizeP = P.size();
    int sizeQ = Q.size();

    // if either one contains elements from higher degree, then we just pass them to the resulting polynomial R

    int indexP = 0;
    int indexQ = 0;

    if (sizeP > sizeQ)
    {
        int difference = sizeP - sizeQ;
        while (indexP != difference)
        {
            R.push_back(P[indexP++]);
        }
    }
    else if (sizeQ > sizeP)
    {
        int difference = sizeQ - sizeP;
        while (indexQ != difference)
        {
            R.push_back(Q[indexQ++]);
        }
    }

    pair<int, int> elementR;
    while (indexP != sizeP && indexQ != sizeQ)
    {
        elementR = ReturnSumOfElements(P[indexP], Q[indexQ]);
        R.push_back(elementR);

        indexP++;
        indexQ++;
    }

    return R;
}

vector<pair<int, int>> returnMultipliedPolynomialByScalar(vector<pair<int, int>> P, pair<int, int> scalar)
{
    int size = P.size();
    int gcd = 0; 
    int numeratorScalar = scalar.first;
    int denominatorScalar = scalar.second;
    int numeratorP = 0;
    int denominatorP = 0;
    for (int i = 0;i < size;i++)
    {
        numeratorP = P[i].first; 
        denominatorP = P[i].second;
        //we multiply each numerator of P by the numerator of the Scalar and multiply each denominator of P by the denominator of the scalar
        numeratorP *= numeratorScalar;
        denominatorP *= denominatorScalar;
        // we find the gcd of the new numeratorP and new denominatorP 
        gcd = gcdNums(numeratorP, denominatorP);

        //Now we abbreviate the fractions

        numeratorP /= gcd;
        denominatorP /= gcd;

        //Finally, we save the values to the Polynomial
        P[i].first = numeratorP;
        P[i].second = denominatorP;
    }

    return P;
}

vector<pair<int, int>> returnMultiplicationOfPolynomials(vector<pair<int, int>> P, vector<pair<int, int>> Q)
{
    //Multiplication of two polynomials P(x) and Q(x).
    //Let's assume P(x) is 5x^3 + 3x^2 + 1 and Q(x) is x^2 + 3
    // Then P(x) * Q(x) = P(x) * x^2 + P(x) * 3 which is sum of polynomials multiplied by scalar and and x of some degree.

    //Resulting polynomial
    vector<pair<int, int>> R;
    
    int sizeQ = Q.size();
    vector<pair<int, int>> multipliedPolynomial;
    int degree = sizeQ - 1;

    for (int i = 0;i < sizeQ;i++)
    {
        //First we calculate the new coefficients
        multipliedPolynomial = returnMultipliedPolynomialByScalar(P, Q[i]);

        //Now we adjust the degree
        multipliedPolynomial = addDegree(multipliedPolynomial, degree);

        if (i == 0)
        {
            R = multipliedPolynomial;
        }
        else {
            R = returnSumOfPolynomials(R, multipliedPolynomial);
        }
        degree--;
    }


 
    return R;
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


    vector<pair<int, int>> R = returnSumOfPolynomials(P, Q);

    
    cout << "P(X) + Q(X) = ";
    printPolynomial(R);
}

void subtractPolynomials() {
    cout << "Enter polynomial P(x)" << endl;
    vector<pair<int, int>> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter polynomial Q(x)" << endl;
    vector<pair<int, int>> Q = readPolynomial();
    cout << "Q(X) = ";
    printPolynomial(Q);


    //We will use the following rule : a + b = a + (-b) and since we already have the function for sum of two polynomials we just need to multiply the second polynomial by -1
    //So we will first write the function for multiplying polynomial by scalar
    pair<int, int> coefficient = { -1,1 }; // this is exactly the number -1 
    Q = returnMultipliedPolynomialByScalar(Q, coefficient);

    //R will be the result of the subtraction
    vector<pair<int, int>> R = returnSumOfPolynomials(P, Q);
    cout << "P(x) - Q(x) = ";
    printPolynomial(R);
   
   
}

void multiplyPolynomials() {
 
   
    cout << "Enter polynomial P(x)" << endl;
    vector<pair<int, int>> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter polynomial Q(x)" << endl;
    vector<pair<int, int>> Q = readPolynomial();
    cout << "Q(X) = ";
    printPolynomial(Q);


    vector<pair<int, int>> R = returnMultiplicationOfPolynomials(P, Q);


    cout << "P(X) * Q(X) = ";
    printPolynomial(R);
}

void dividePolynomials() {
    cout << "dividePolynomials() is not implemented yet.\n";
}

void multiplyPolynomialByScalar() {

    cout << "Enter polynomial P(x)" << endl;
    vector<pair<int, int>> P = readPolynomial();
    cout << "P(X) = ";
    printPolynomial(P);

    cout << "Enter rational number>> ";
    pair<int, int> scalar = readRationalNumber();

    P = returnMultipliedPolynomialByScalar(P, scalar);
    cout << "Result: ";
    printPolynomial(P);

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

