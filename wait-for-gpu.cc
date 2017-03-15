#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime_api.h>

inline void __cudaSafeCall(cudaError_t err, const char *file, const int line) {
  if (cudaSuccess != err) {
    fprintf(stderr, "Cuda call failed at %s:%i : %s\n",
            file, line, cudaGetErrorString(err));
    exit(EXIT_FAILURE);
  }
  return;
}

inline void __cudaPrintError(cudaError_t err, const char *file, const int line) {
  if (cudaSuccess != err) {
    fprintf(stderr, "Cuda error at %s:%i : %s\n",
            file, line, cudaGetErrorString(err));
  }
  return;
}

#define CudaSafeCall(err) __cudaSafeCall ( err, __FILE__, __LINE__ )
#define CudaPrintError(err) __cudaPrintError ( err, __FILE__, __LINE__ )

int main(int argc, char *argv[]) {
  CudaSafeCall(cudaSetDevice(0));
  CudaPrintError(cudaDeviceSynchronize());
  while (cudaGetLastError() != cudaSuccess) {
    sleep(3);
    CudaPrintError(cudaDeviceSynchronize());
  }
  sleep(5);
  CudaSafeCall(cudaDeviceReset());
  fprintf(stderr, "Done.\n");
  return 0;
}
