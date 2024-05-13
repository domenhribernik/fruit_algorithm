import matplotlib.pyplot as plt

# Podatki za čase izvajanja algoritmov
bruteforce_times = {
    6: 0.0008039,
    8: 5.36581,
    11: 0.000732,
    12: 0.000622,
    95: 0.0012775,
    98: 0.0005865,
    99: 0.0011497
}

# Dodelitev velike vrednosti tam, kjer ni rešitve
no_solution_value = 10  # Simbolizira 10 sekund kot placeholder za neuspeh
bruteforce_failed = {1, 2, 3, 4, 5, 10, 13}
for test in bruteforce_failed:
    bruteforce_times[test] = no_solution_value

dp_times = {
    1: 0.0283726,
    2: 0.0218431,
    3: 0.03439,
    4: 0.0215,
    5: 0.0032541,
    6: 0.002785,
    8: 0.0007218,
    10: 0.0389499,
    11: 0.0098542,
    12: 0.0097159,
    13: 0.0303193,
    95: 0.0053925,
    98: 0.0058409,
    99: 0.0049506
}

# Vsi testni primeri, ki so obravnavani v obeh metodah
all_tests = set(bruteforce_times.keys()).union(set(dp_times.keys()))
test_numbers = sorted(all_tests)

# Izločitev časov za oba algoritma
bruteforce_values = [bruteforce_times.get(test, no_solution_value) for test in test_numbers]
dp_values = [dp_times.get(test, no_solution_value) for test in test_numbers]

# Izris grafa
plt.figure(figsize=(10, 5))
plt.plot(test_numbers, bruteforce_values, marker='o', linestyle='-', color='red', label='Bruteforce')
plt.plot(test_numbers, dp_values, marker='s', linestyle='-', color='blue', label='Dinamično programiranje (DP)')

plt.title('Primerjava časov izvajanja algoritmov Bruteforce in DP')
plt.xlabel('Številka testa')
plt.ylabel('Čas izvajanja (s)')
plt.legend()
plt.grid(True)
plt.yscale('log')  # Logaritemska lestvica za boljšo vizualizacijo razlik
plt.xticks(test_numbers)
plt.tight_layout()
plt.show()
