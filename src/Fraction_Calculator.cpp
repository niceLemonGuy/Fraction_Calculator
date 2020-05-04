#include <iostream>
#include <exception>
using namespace std;

class Rational {
public:
    Rational() {
        numer = 0;
        denom = 1;
    }

    Rational(int numerator, int denominator) {
    	if(denominator == 0) {
    		throw invalid_argument("Invalid argument");
    	}

    	int n = abs(numerator), d = abs(denominator);
    	while(n > 0 && d > 0) {
    		if(n > d) {
    			n %= d;
    		} else {
    			d %= n;
    		}
    	}
    	n += d;
    	numer = numerator / n;
    	denom = denominator / n;
    	if(numer < 0 && denom < 0) {
    		numer = abs(numer);
    		denom = abs(denom);
    	} else if(numer < 0 || denom < 0) {
    		numer = abs(numer);
			denom = abs(denom);
    		numer = -numer;
    	} else if(numer == 0) {
    		denom = 1;
    	}
    }

    int Numerator() const {
    	return numer;
    }

    int Denominator() const {
        return denom;
    }

private:
    int numer, denom;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
	return Rational((lhs.Numerator() * rhs.Denominator() +
					rhs.Numerator() * lhs.Denominator()),
					lhs.Denominator() * rhs.Denominator());
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
	return Rational((lhs.Numerator() * rhs.Denominator() -
					rhs.Numerator() * lhs.Denominator()),
					lhs.Denominator() * rhs.Denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if(rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(),
					lhs.Denominator() * rhs.Numerator());
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(),
					lhs.Denominator() * rhs.Denominator());
}

ostream& operator << (ostream& stream,
					  const Rational& rational) {
	stream << rational.Numerator() << "/"
		   << rational.Denominator();
	return stream;
}

istream& operator >> (istream& stream,
					  Rational& rational) {
	int numer = 0, denom = 0;
	if(!(stream >> numer)) {
		return stream;
	}
	stream.ignore(1);
	if(!(stream >> denom)){
		return stream;
	}
	rational = {numer, denom};
	return stream;
}

bool operator < (const Rational& lhs,
				 const Rational& rhs) {
	return ((lhs.Numerator() * rhs.Denominator()) <
			(rhs.Numerator() * lhs.Denominator()));
}

bool operator > (const Rational& lhs,
				 const Rational& rhs) {
	return ((lhs.Numerator() * rhs.Denominator()) >
			(rhs.Numerator() * lhs.Denominator()));
}

void Calculate(void) {
	try {
		Rational lhs, rhs;
		char operation;
		cin >> lhs;
		cin >> operation;
		cin >> rhs;
		if('+' == operation) {
			cout << lhs + rhs;
		} else if('-' == operation) {
			cout << lhs - rhs;
		} else if('*' == operation) {
			cout << lhs * rhs;
		} else if('/' == operation) {
			cout << lhs / rhs;
		}
	} catch (invalid_argument& ex) {
    	cout << ex.what() << endl;
    } catch (domain_error& ex) {
    	cout << ex.what() << endl;
    }
}

int main() {
	Calculate();
	return 0;
}
