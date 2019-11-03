#include <iostream>
#include <cmath>

class Key {
public:
    static const int e = 3;
};

class PublicKey : Key {

};

class PrivateKey : Key {

};

class RSABreaker {

    int getN(int p, int q) {
        return p * q;
    }

private:
    int encrypt(int message, PrivateKey privateKey); //Assume you are only
    // encrypting with private key for now.

    int decrypt(int cipher, PublicKey publicKey);

    int crack();
};

int RSABreaker::decrypt(int cipher, PublicKey publicKey) {
    return 0;
}

int RSABreaker::encrypt(int m, PrivateKey privateKey) {
    return 0;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}