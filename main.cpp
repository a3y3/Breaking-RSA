#include <iostream>
#include <cmath>

class PublicKey {
    unsigned int n;
    unsigned int e;
public:
    PublicKey(unsigned int n1, unsigned int e1) {
        n = n1;
        e = e1;
    }

    unsigned int getN() const {
        return n;
    }

    unsigned int getE() const {
        return e;
    }
};

class PrivateKey {
    unsigned int d;
    unsigned int n;
public:
    PrivateKey(unsigned int d1, unsigned int n1) {
        d = d1;
        n = n1;
    }

    unsigned int getD() const {
        return d;
    }

    unsigned int getN() const {
        return n;
    }
};

class RSABreaker {
public:
    static unsigned long long int encrypt(unsigned long long message, PublicKey
    publicKey);
    //Assume
    // you are only encrypting with public key for now.

    static unsigned long long int
    decrypt(unsigned long long cipher, PrivateKey privateKey);

    static int crack();
};

unsigned long long int
RSABreaker::decrypt(unsigned long long cipher, PrivateKey privateKey) {
    unsigned int d = privateKey.getD();
    unsigned int n = privateKey.getN();
    unsigned long long int message = 1;

    for (unsigned int i = 0; i < d; ++i) {
        message *= cipher;
        message = message % n;
    }
    return message;
}

unsigned long long int RSABreaker::encrypt(unsigned long long m, PublicKey
publicKey) {
    unsigned int e = publicKey.getE();
    unsigned int n = publicKey.getN();
    unsigned long long int cipher = 1;

    for (unsigned int i = 0; i < e; ++i) {
        cipher *= m;
        cipher = cipher % n;
    }
    return cipher;
}

int RSABreaker::crack() {
    return 0;
}

int phi(int p, int q);

PrivateKey getPrivateKey(int p, int q, unsigned int e);

void test(PublicKey, PrivateKey);

int main() {
    int p = 53;
    int q = 59;
    unsigned int n = p * q;
    unsigned int e = 3;
    PrivateKey privateKey = getPrivateKey(p, q, e);
    PublicKey publicKey(n, e);

    test(publicKey, privateKey);
    return 0;
}

int phi(int p, int q) {
    return (p - 1) * (q - 1);
}

PrivateKey getPrivateKey(int p, int q, unsigned int e) {
    int phi_n = phi(p, q);
    int k = 2;
    unsigned int d = ((k * phi_n) + 1) / e;
    unsigned int n = p * q;

    return {d, n};
}

void test(PublicKey publicKey, PrivateKey privateKey) {
    unsigned int message = 89;
    std::cout << "Encrypting \"" << message << "\"...\n";
    RSABreaker rsaBreaker;
    unsigned long long int cipher = rsaBreaker.encrypt(message, publicKey);
    std::cout << "Encrypted!: " << cipher << "\n";

    std::cout << "Decrypting \"" << cipher << "\"...\n";
    unsigned long long int decrypted = rsaBreaker.decrypt(cipher, privateKey);
    std::cout << "Decrypted!: " << decrypted << "\n";

    if (message != decrypted) {
        std::cout << "Test failed, please check encryption and decryption";
    }
}