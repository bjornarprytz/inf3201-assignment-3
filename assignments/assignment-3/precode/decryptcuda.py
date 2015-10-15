import pycuda.autoinit
import pycuda.driver as drv
import pycuda.gpuarray as gpuarray
import pycuda.compiler
import numpy as np

# Generate the source module
f = open("cuda_kernel.cu", 'r')
# lineinfo used to enable assembly profiling in nvvp
sm = pycuda.compiler.SourceModule(f.read(), options=['-lineinfo'])

width = 16
height = 16

def decrypt(bytes_in, output, key, length):
    # Get a function pointer from the source module
    func = sm.get_function("decrypt")
    # Reshaping for simplicity here, not really needed usually
    output = np.reshape(output, width*height)
    # Copy data to and from the GPU, and call the function on it
    # Grid and block size simplified here, probably easier to understand the code if it was 2D
    func(drv.In(bytes_in), drv.InOut(output), drv.In(key), np.int32(length), block=(64,1,1), grid=(width*height/64,1,1))
    # Reshaping the results
    output = np.reshape(output,(width,height))
