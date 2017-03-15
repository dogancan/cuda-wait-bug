# cuda-wait-bug

If a process tries to create a CUDA context on a device in exclusive process mode and fails because another process currently owns a context on that device, it will continue to fail even after the device is no longer occupied.

## Steps to Replicate

    # Set compute mode for GPU 0 to "Exclusive Process"
    nvidia-smi -c 3 -i 0
    # Compile
    g++ -I/usr/local/cuda/include -L/usr/local/cuda/lib64 -o wait-for-gpu wait-for-gpu.cc -lcudart
    # Second process does not terminate. See log.1 and log.2
    ./run.sh &
