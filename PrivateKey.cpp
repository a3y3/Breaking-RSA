/**
 * Holds a private key. Is unused for this implementation, but feel free to
 * play around with this for encrypting custom messages instead of accepting
 * a cipher directly from STDIN.
 */
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