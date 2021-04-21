import numpy as np
import matplotlib.pyplot as plt
from matplotlib import patheffects 
import yaml
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "serif",
    "font.size": 15,
})

show_ψ = False

# xlim, ylim = [2.95, 3.15], [1.85, 2.10]
# xlim, ylim = [2.6, 3.4], [1.9, 3.1]
xlim, ylim = [2.5, 3.5], [1.9, 3.1]
levels = np.arange(0, 56, 1)

def meshplot(f, xlim, ylim, delta):
    x = np.arange(xlim[0], xlim[1], delta)
    y = np.arange(ylim[0], ylim[1], delta)
    X, Y = np.meshgrid(x, y)
    Z = f(X, Y)
    return X, Y, Z


def f(x, y):
    return (x**2 + y - 11)**2 + (x + y**2 - 7)**2


X, Y, Z = meshplot(f, xlim, ylim, 0.001)

def load_results(name, long = False):
    if long: name = "long-" + name
    with open("/tmp/" + name + ".yaml", "r") as file:
        return yaml.safe_load(file)

data = [ load_results(nm)
           for nm in ["pga", "panoc", "panoc-2lbfgs", "panoc-2newton"] ]
alm_its = max(map(len, data))
it = 0
colors = ["r", "g", "b", "purple"]
labels = [  r"Projected gradient", 
            r"Standard PANOC", 
            r"2\textsuperscript{nd} order PANOC with L-BFGS",
            r"2\textsuperscript{nd} order PANOC with exact Newton"]

x_star = np.array([2.97248423531758647429, 2.1])

fig, ax = plt.subplots(1, 1, sharex='all', sharey='all', figsize=(6.6, 7.6))
for id, d in enumerate(data):
        x = np.array([e["x"] for e in d[it]["PANOC"]])
        λ = np.array(d[it]["y"])
        Σ = np.array(d[it]["Σ"])
        print(len(x))
        ax.contour(X, Y, Z, levels)
        cg1 = ax.contour(X, Y, -Y, [-2.1], colors='black', linewidths=0.8, linestyles='-')
        plt.setp(cg1.collections,
                path_effects=[patheffects.withTickedStroke(spacing=7, linewidth=0.8)])
        ax.set_xlim(xlim)
        ax.set_ylim(ylim)
        lbl = f'{labels[id]} ({len(x) - 1} it.)'
        ax.plot(x[:, 0], x[:, 1], '.-', color=colors[id], label=lbl, markersize=8)
ax.set_aspect('equal')
ax.set_xticks(np.linspace(*xlim, 5, endpoint=True))
ax.plot(3, 2, 'kx')
ax.legend(loc='upper center')
ax.set_title('Himmelblau with box constraint')
plt.tight_layout()
plt.savefig("pga-vs-panoc-vs-newton.pdf")

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "serif",
    "font.size": 12,
})
data = [ load_results(nm, long=True)
           for nm in ["pga", "panoc", "panoc-2lbfgs", "panoc-2newton"] ]

fig, ax = plt.subplots(1, 1, sharex='all', sharey='all', figsize=(4, 4))
for id, d in enumerate(data):
    x = np.array([e["x"] for e in d[it]["PANOC"]])
    err = np.linalg.norm(x - x_star, axis=-1)
    lbl = f'{labels[id]} ({len(x) - 1} it.)'
    ax.semilogy(err, '.-', color=colors[id], label=lbl, markersize=8)
ax.set_xlim([0, 15])
ax.set_ylim([1e-12, 1])
ax.set_title('Himmelblau convergence')
ax.set_xlabel('Iteration')
ax.set_ylabel(r'$\left\|x - x^\star \right\|_2$')
plt.tight_layout()
plt.savefig("pga-vs-panoc-vs-newton-conv.pdf")

plt.show()