// Brace initialisation rejects narrowing conversions at compile time
int main() {
    int a = 3.7;        // allowed: silently truncates to 3 (no error, maybe a warning)
    int b{3.7};         // ERROR: narrowing double -> int
    bool c{5};          // ERROR: narrowing int -> bool
    char d{300};        // ERROR: constant 300 does not fit in char
    return a + b + c + d;
}
