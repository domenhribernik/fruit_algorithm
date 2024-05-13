import matplotlib.pyplot as plt
import numpy as np


# Read input from file
def read_input(filename):
    with open(filename, 'r') as file:
        n, k, m = map(int, file.readline().split())
        fruit = file.readline().strip()
    return n, k, m, fruit

# Sample input filename
filename = 'sadje/sadje.02.in'

# Read input from file
n, k, m, fruit = read_input(filename)

n = 200
fruit = fruit[:n]

# Generate insertion points (for demonstration purposes)
insertions = [i + 1 for i in range(k)]  # Assuming insertion points are at every position

# Initialize DP table
dp = np.full((n+1, k+1), float('inf'))
dp[0][0] = 0

# Populate DP table
for i in range(n):
    for j in range(min(k, i+1)+1):
        # No insertion
        if i < n and dp[i][j] != float('inf'):
            next_pick = 1 if (i + j) % m == (m - 1) and fruit[i] == '1' else 0
            dp[i+1][j] = min(dp[i+1][j], dp[i][j] + next_pick)
        # Insert apple
        if j < k and dp[i][j] != float('inf'):
            next_pick = 1 if (i + j) % m == (m - 1) else 0
            dp[i][j+1] = min(dp[i][j+1], dp[i][j] + next_pick)

# Visualize DP table
plt.imshow(dp, cmap='hot', interpolation='nearest')
plt.colorbar()
plt.title('Toplotna karta DP tabele (Minimalno pobranih jabolk)')
plt.xlabel('Število vstavljenih jabolk')
plt.ylabel('Pozicija v zaporedju')
plt.show()
