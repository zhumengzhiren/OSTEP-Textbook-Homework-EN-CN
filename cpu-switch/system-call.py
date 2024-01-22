import time
import os
import ctypes

# Function to measure the cost of system calls using gettimeofday()
def measure_syscall_cost(iterations):
    start_time = time.time()
    for _ in range(iterations):
        os.system("true")  # Replace with your system call
    end_time = time.time()
    elapsed_time = end_time - start_time
    syscall_cost = elapsed_time / iterations
    return syscall_cost

# Function to measure the accuracy of gettimeofday()
def measure_gettimeofday_accuracy(iterations):
    start_time = time.time()
    for _ in range(iterations):
        current_time = time.time()
    end_time = time.time()
    elapsed_time = end_time - start_time
    gettimeofday_accuracy = elapsed_time / iterations
    return gettimeofday_accuracy

# Function to measure the cost of system calls using rdtsc instruction
def measure_syscall_cost_rdtsc(iterations):
    start_time = ctypes.c_uint64(int(time.time() * 1e9)).value
    for _ in range(iterations):
        os.system("true")  # Replace with your system call
    end_time = ctypes.c_uint64(int(time.time() * 1e9)).value
    elapsed_time = end_time - start_time
    syscall_cost = elapsed_time / iterations / 1e9
    return syscall_cost

# Example usage
syscall_iterations = 1000


# gettimeofday_iterations = 10000

syscall_cost = measure_syscall_cost(syscall_iterations)
print(f"Estimated syscall cost using gettimeofday(): {syscall_cost} seconds per syscall")

# gettimeofday_accuracy = measure_gettimeofday_accuracy(gettimeofday_iterations)
# print(f"Accuracy of gettimeofday(): {gettimeofday_accuracy} seconds per call")

# Uncomment the following lines if rdtsc instruction is supported on your machine
syscall_cost_rdtsc = measure_syscall_cost_rdtsc(syscall_iterations)
print(f"Estimated syscall cost using rdtsc: {syscall_cost_rdtsc} seconds per syscall")
