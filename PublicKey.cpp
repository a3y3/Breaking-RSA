/**
 * Holds a public key (consisting of n and e).
 */
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