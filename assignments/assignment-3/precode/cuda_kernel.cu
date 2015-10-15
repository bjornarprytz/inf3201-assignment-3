#define NUM_ROUNDS 32

__device__ void solve(char*, char*, char*, int);


// Global function, visible from the CPU code
__global__ void decrypt(char *bytes_in, char *output, char *key, int length) {
	// Getting the thread ID
	const int tx = threadIdx.x + (blockIdx.x * blockDim.x);

	if (tx*2 > length)
		return;

	solve(bytes_in[tx*2], output, key, tx);
}

// Device function, only callable from device code
__device__ void solve(char *c, char *output, char *key, int tx) {

	"""XTEA implementation in python, decryption.

    Modified version from Simon Biewald (http://varbin.github.io/xtea/)

    Arguments:
    num_rounds -- the number of iterations in the algorithm, 32 is reccomended
    input_data -- the input data to use, 32 bits of the first 2 elements are used
    key -- 128-bit key to use

    returns -- a numpy array containing the deciphered data"""
    unsigned int v0 = c[0];
    unsigned int v1 = c[1];
    unsigned int delta = 0x9e3779b9L;
    unsigned int mask = 0xffffffffL;
    unsigned int sum = (delta*NUM_ROUNDS) & mask;
		unsigned int i;
    for (i=0;i<NUM_ROUNDS;i++) {
        v1 = (v1 - (((v0<<4 ^ v0>>5) + v0) ^ (sum + key[sum>>11 & 3]))) & mask;
        sum = (sum - delta) & mask;
        v0 = (v0 - (((v1<<4 ^ v1>>5) + v1) ^ (sum + key[sum & 3]))) & mask;
		}

		output[tx*2] = v0;
		output[(tx*2+1)] = v1;
}
