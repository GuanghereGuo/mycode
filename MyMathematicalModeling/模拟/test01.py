import numpy as np
import pandas as pd

df = pd.read_excel('data.xlsx', sheet_name='Sheet1', index_col=0)
diss = df.values

n_emp = 280
n_task = 100

def init_assign():
    best_diss = float('inf')
    best_assign = None
    best_e2t = None
    best_t2e = None
    for _ in range(1000):
        emps = np.random.permutation(n_emp)
        sizes = np.full(n_task, 2)
        sizes[:n_emp - 2 * n_task] += 1
        assign = []
        start = 0
        for s in sizes:
            assign.append(emps[start:start + s].tolist())
            start += s
        e2t = {e: t for t, es in enumerate(assign) for e in es}
        t2e = {t: set(es) for t, es in enumerate(assign)}
        curr_diss = total_diss(t2e, diss)
        if curr_diss < best_diss:
            best_diss = curr_diss
            best_assign = assign
            best_e2t = e2t
            best_t2e = t2e
    return best_assign, best_e2t, best_t2e

def task_diss(t, es, diss):
    return np.mean([diss[e, t] for e in es]) if es else 0

def total_diss(t2e, diss):
    return sum(task_diss(t, t2e[t], diss) for t in range(n_task))

def move(e2t, t2e):
    e = np.random.randint(n_emp)
    curr_t = e2t[e]
    while len(t2e[curr_t]) <= 2:
        e = np.random.randint(n_emp)
        curr_t = e2t[e]
    new_t = curr_t
    while new_t == curr_t:
        new_t = np.random.randint(n_task)
    changes = {'emp': e, 'from': curr_t, 'to': new_t}
    t2e[curr_t].remove(e)
    t2e[new_t].add(e)
    e2t[e] = new_t
    return changes

def revert(changes, t2e, e2t):
    e = changes['emp']
    t2e[changes['to']].remove(e)
    t2e[changes['from']].add(e)
    e2t[e] = changes['from']

def delta(t2e, t_diss, diss, changes):
    e = changes['emp']
    f = changes['from']
    t = changes['to']
    new_f_diss = task_diss(f, t2e[f], diss)
    new_t_diss = task_diss(t, t2e[t], diss)
    d = (new_f_diss - t_diss[f]) + (new_t_diss - t_diss[t])
    return d, new_f_diss, new_t_diss

def sa():
    assign, e2t, t2e = init_assign()
    t_diss = [task_diss(t, t2e[t], diss) for t in range(n_task)]
    curr_diss = sum(t_diss)
    best_diss = curr_diss
    best_assign = [list(es) for es in t2e.values()]
    T = 1e3
    alpha = 0.9995
    min_T = 1e-7
    iters = n_emp
    diss_history = []
    while T > min_T:
        for _ in range(iters):
            changes = move(e2t, t2e)
            d, new_f_diss, new_t_diss = delta(t2e, t_diss, diss, changes)
            if d < 0 or np.random.rand() < np.exp(-d / T):
                t_diss[changes['from']] = new_f_diss
                t_diss[changes['to']] = new_t_diss
                curr_diss += d
                if curr_diss < best_diss:
                    best_diss = curr_diss
                    best_assign = [list(es) for es in t2e.values()]
            else:
                revert(changes, t2e, e2t)
            diss_history.append(curr_diss)
        T *= alpha
    return best_assign, best_diss, diss_history

import matplotlib.pyplot as plt

best_assign, best_diss, diss_history = sa()

print(f"Best Total Dissatisfaction: {best_diss:.2f}")
print("Task Assignments:")
for t, es in enumerate(best_assign):
    print(f"Task {t}: Employees {es}")

plt.plot(diss_history)
plt.xlabel('Iteration')
plt.ylabel('Total Dissatisfaction')
plt.title('Simulated Annealing Convergence')
plt.show()

max_cols = max(len(lst) for lst in best_assign)
output_df = pd.DataFrame(best_assign, columns=[f"Emp_{i}" for i in range(max_cols)])
output_df.to_excel('assignment_result.xlsx', index_label='Task')