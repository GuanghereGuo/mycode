import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel('data.xlsx', sheet_name='Sheet1', index_col=0)
diss = df.values

neg_df = pd.read_excel('data.xlsx', sheet_name='Sheet2', index_col=0)
neg = neg_df.values

n_emp = 280
n_task = 100

def init_assign():
    best_obj = float('inf')
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
        total_diss = sum(task_diss(t, t2e[t], diss) for t in range(n_task))
        total_neg = sum(task_neg_impact(t2e[t], neg) for t in range(n_task))
        obj = total_diss + total_neg
        if obj < best_obj:
            best_obj = obj
            best_assign = assign
            best_e2t = e2t
            best_t2e = t2e
    return best_assign, best_e2t, best_t2e

def task_diss(t, es, diss):
    return np.mean([diss[e, t] for e in es]) if es else 0

def task_neg_impact(es, neg):
    return sum(neg[e1, e2] for e1 in es for e2 in es if e1 < e2)

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

def delta(t2e, t_diss, neg_impact, diss, neg, changes):
    e = changes['emp']
    f = changes['from']
    t = changes['to']
    new_f_diss = task_diss(f, t2e[f], diss)
    new_t_diss = task_diss(t, t2e[t], diss)
    new_neg_impact_f = task_neg_impact(t2e[f], neg)
    new_neg_impact_t = task_neg_impact(t2e[t], neg)
    d_diss = (new_f_diss - t_diss[f]) + (new_t_diss - t_diss[t])
    d_neg = (new_neg_impact_f - neg_impact[f]) + (new_neg_impact_t - neg_impact[t])
    d = d_diss + d_neg
    return d, new_f_diss, new_t_diss, new_neg_impact_f, new_neg_impact_t

def sa():
    assign, e2t, t2e = init_assign()
    t_diss = [task_diss(t, t2e[t], diss) for t in range(n_task)]
    neg_impact = [task_neg_impact(t2e[t], neg) for t in range(n_task)]
    curr_diss = sum(t_diss)
    curr_neg_impact = sum(neg_impact)
    curr_obj = curr_diss + curr_neg_impact
    best_obj = curr_obj
    best_assign = [list(es) for es in t2e.values()]
    T = 1e4
    alpha = 0.9995
    min_T = 1e-7
    iters = n_emp
    obj_history = []
    while T > min_T:
        for _ in range(iters):
            changes = move(e2t, t2e)
            d, new_f_diss, new_t_diss, new_neg_impact_f, new_neg_impact_t = delta(
                t2e, t_diss, neg_impact, diss, neg, changes
            )
            if d < 0 or np.random.rand() < np.exp(-d / T):
                t_diss[changes['from']] = new_f_diss
                t_diss[changes['to']] = new_t_diss
                neg_impact[changes['from']] = new_neg_impact_f
                neg_impact[changes['to']] = new_neg_impact_t
                curr_obj += d
                if curr_obj < best_obj:
                    best_obj = curr_obj
                    best_assign = [list(es) for es in t2e.values()]
            else:
                revert(changes, t2e, e2t)
            obj_history.append(curr_obj)
        T *= alpha
    return best_assign, best_obj, obj_history

best_assign, best_obj, obj_history = sa()

print(f"Best Total Objective (Dissatisfaction + Negative Impact): {best_obj:.4f}")
final_t2e = {t: set(es) for t, es in enumerate(best_assign)}
final_diss = sum(task_diss(t, final_t2e[t], diss) for t in range(n_task))
final_neg_impact = sum(task_neg_impact(final_t2e[t], neg) for t in range(n_task))
print("Task Assignments:")
for t, es in enumerate(best_assign):
    print(f"Task {t}: Employees {es}")

plt.plot(obj_history)
plt.xlabel('Iteration')
plt.ylabel('Total Objective (Dissatisfaction + Negative Impact)')
plt.title('Simulated Annealing Convergence')
plt.show()