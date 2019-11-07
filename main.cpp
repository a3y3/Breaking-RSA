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
    //Assume you are only encrypting with public key for now.

    static unsigned long long int
    decrypt(unsigned long long cipher, PrivateKey privateKey);

    //void as crack() can find multiple cube roots for a cipher.
    static void crack(unsigned long long cipher, PublicKey publicKey);
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

void RSABreaker::crack(unsigned long long cipher, PublicKey publicKey) {
    unsigned int n = publicKey.getN();
    unsigned int e = publicKey.getE();
    bool cracked = false;
    for (unsigned int m = 0; m <= n - 1; ++m) {
        unsigned long long possibleCipher = 1;

        //Brute force for a possible cipher.
        // Instead of doing pow(cipher, e), the loop guards against overflows
        // by repeatedly taking the modulus with every multiplication.
        for (unsigned int i = 0; i < e; ++i) {
            possibleCipher *= m;
            possibleCipher = possibleCipher % n;
        }
        if (possibleCipher == cipher) {
            std::cout << m << "^" << e << " = " << cipher << "(mod " << n
                      << ")" << std::endl;
            cracked = true;
        }
    }
    if (!cracked){
        std::cout<<"No cube roots of "<< cipher<<" (mod " <<n<<")";
    }
}


int phi(int p, int q);

PrivateKey getPrivateKey(int p, int q, unsigned int e);

int main(int argc, char *argv[]) {
    unsigned long long int cipher = std::stoi(argv[1]);
    unsigned int n = std::stoi(argv[2]);
    unsigned int e = 3;
//    PrivateKey privateKey = getPrivateKey(p, q, e);
    PublicKey publicKey(n, e);

    RSABreaker rsaBreaker;
    rsaBreaker.crack(cipher, publicKey);
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
