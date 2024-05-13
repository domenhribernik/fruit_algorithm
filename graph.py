import matplotlib.pyplot as plt

# Input sizes
input_sizes = [10, 30, 50, 100, 250, 500, 1000, 2500, 5000, 10000]

# Computation times for brute force algorithm
bruteforce_times = [0.0129413, 0.0798356, 0.54662, 5.4935]  # Only available up to input 100

# Computation times for dynamic programming algorithm
dp_times = [0.0031673, 0.0012766, 0.0015329, 0.0019994, 0.003136, 0.0038502, 0.0127375, 0.021998, 0.0210917, 0.0295908]

plt.plot(input_sizes[:len(bruteforce_times)], bruteforce_times, label='Brute Force')
plt.plot(input_sizes, dp_times, label='Dynamic Programming')

plt.xlabel('Size of input')
plt.ylabel('Computation time')
plt.title('Comparison of Computation Times')
plt.legend()
plt.yscale('log')  # Set y-axis scale to logarithmic
plt.show()
