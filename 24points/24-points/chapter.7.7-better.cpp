#include"24 points.h"

// Token definitions
const char number = '8';    // Token kind for numbers

// Token class
class Token {
public:
    char kind;        // Token type
    double value;     // For numbers: a value
    Token(char ch)    // Make a Token from a char
        : kind(ch), value(0) { }
    Token(char ch, double val)     // Make a Token from a char and a double
        : kind(ch), value(val) { }
};

// Token_stream class
class Token_stream {
public:
    Token_stream(istream& s);   // Constructor that takes an input stream
    Token get();                // Get a Token
    void putback(Token t);      // Put a Token back
    void ignore(char c);        // Discard tokens up to and including a c
private:
    bool full;        // Is there a Token in the buffer?
    Token buffer;     // Buffer to hold a Token put back using putback()
    istream& ip;      // Input stream reference
};

// Token_stream constructor
Token_stream::Token_stream(istream& s)
    : full(false), buffer(0), ip(s)
{
}

// Putback function
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;
    full = true;
}

// Get function
Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    if (!(ip >> ch)) {
        return Token('\0'); // No more input
    }

    switch (ch) {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
        return Token(ch);   // Let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':    // Numeric literal
    {
        ip.putback(ch);      // Put digit back into the input stream
        double val;
        ip >> val;           // Read a floating-point number
        return Token(number, val);
    }
    default:
        error("Bad token");
    }
}

// Ignore function
void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while (ip >> ch)
        if (ch == c) return;
}

// Forward declarations
double expression(Token_stream& ts);
double term(Token_stream& ts);
double primary(Token_stream& ts);

// Primary function
double primary(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':   // Handle '(' expression ')'
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case number:
        return t.value;    // Return the number's value
    case '-':
        return -primary(ts);
    case '+':
        return primary(ts);
    default:
        error("Primary expected");
    }
}

// Term function
double term(Token_stream& ts)
{
    double left = primary(ts);
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary(ts);
            t = ts.get();
            break;
        case '/':
        {
            double d = primary(ts);
            if (d == 0) error("Divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

// Expression function
double expression(Token_stream& ts)
{
    double left = term(ts);
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
        case '+':
            left += term(ts);
            t = ts.get();
            break;
        case '-':
            left -= term(ts);
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

// Calculate function
double calculate(string expr)
{
    istringstream iss(expr);
    Token_stream ts(iss);
    try {
        double val = expression(ts);
        Token t = ts.get();
        if (t.kind != '\0') {
            error("Unexpected input after expression");
        }
        return val;
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        throw; // Rethrow exception to be handled by the caller if necessary
    }
}

