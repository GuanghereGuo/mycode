import matplotlib.pyplot as plt

with open('obj_history.txt', 'r') as f:
    obj_history = [float(line.strip()) for line in f]

plt.plot(obj_history)
plt.xlabel('Iteration')
plt.ylabel('Total Objective')
plt.title('Simulated Annealing Convergence')
plt.show()