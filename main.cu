#include <iostream>
#include "PublicKey.cpp"
#include <chrono>

void printResults(const int *results, unsigned long long cipher, unsigned int e,
                  unsigned int n);

/**
 * This function is run on a GPU.
 *
 * It gets the threadID (using
 * {@code unsigned long long m = blockDim.x * blockIdx.x + threadIdx.x) and
 * assumes that {@code threadID} is a possible message.
 *
 * It then calculates message ^ e modulus n iteratively and marks it as a
 * possible message by setting the value at that index to 1.
 *
 * @param cipher the cipher that is to be cracked.
 * @param e {@see PublicKey.cpp)
 * @param n {@see PublicKey.cpp)
 * @param gpu_results pointer to results. Note that this exists only in the
 * GPU memory so it must be copied back into the host.
 */
__global__
void gpu_crack(unsigned long long cipher, unsigned int e, unsigned int n,
               int *gpu_results) {
    unsigned long long possibleCipher = 1;
    unsigned long long m = blockDim.x * blockIdx.x + threadIdx.x;
    if (m < n) {
        // Instead of doing pow(cipher, e), the loop guards against overflows
        // by repeatedly taking the modulus with every multiplication.
        for (unsigned int i = 0; i < e; ++i) {
            possibleCipher *= m;
            possibleCipher = possibleCipher % n;
        }
        if (possibleCipher == cipher) {
            gpu_results[m] = 1;
            return;
        }
    }
    gpu_results[m] = 0;
}

/**
 * Parallel brute force all messages 0<=m<=n for finding a message that
 * equals to the cube root of the cipher text.
 *
 * @param cipher the cipher that is to be cracked.
 * @param publicKey the public key that is assumed to be available to the
 * hacker.
 */
void crack(unsigned long long cipher, PublicKey publicKey) {
    unsigned int e = publicKey.getE();
    unsigned int n = publicKey.getN();

    size_t size = n * sizeof(int);
    auto *results = (int *) malloc(size);
    int *gpu_results;
    cudaMalloc(&gpu_results, size);


    unsigned int threadsPerBlock = 256;
    unsigned int blocksPerGrid =
            (n + threadsPerBlock - 1) / threadsPerBlock;
    gpu_crack << < blocksPerGrid, threadsPerBlock >> >
                                  (cipher, e, n, gpu_results);

    cudaMemcpy(results, gpu_results, size, cudaMemcpyDeviceToHost);
    printResults(results, cipher, e, n);
    cudaFree(gpu_results);
    delete results;
}

void printResults(const int *results, unsigned long long cipher,
                  unsigned int e, unsigned int n) {
    bool atleast_one_result = false;
    for (unsigned int i = 0; i < n; i++) {
        if (results[i] == 1) {
            atleast_one_result = true;
            std::cout << i << "^" << e << " = " << cipher << " (mod " << n
                      << ")" << std::endl;
        }
    }
    if (!atleast_one_result) {
        std::cout << "No cube roots of " << cipher << " (mod " << n << ")";
    }
}

int main(int argc, char *argv[]) {
    unsigned long long int cipher = std::stoi(argv[1]);
    unsigned int n = std::stoi(argv[2]);
    unsigned int e = 3;
    PublicKey publicKey(n, e);
    auto start = std::chrono::high_resolution_clock::now();
    crack(cipher, publicKey);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            stop - start);
    std::cout << "Execution finished in " << duration.count() <<
              "ms" << std::endl;
    return 0;
}