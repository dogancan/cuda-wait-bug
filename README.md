# cuda-wait-bug

If a process tries to create a CUDA context on a device in exclusive process mode and fails because another process currently owns a context on that device, it will continue to fail even after the device is no longer occupied.

## Steps to Replicate

    nvidia-smi -c 3 -i 0  # Set compute mode for GPU 0 to "Exclusive Process"
    g++ -I/usr/local/cuda/include -L/usr/local/cuda/lib64 -o wait-for-gpu wait-for-gpu.cc -lcudart
    ./run.sh &  # Second process will never terminate. See log.2
