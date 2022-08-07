import casadi as cs
from sys import argv, path
from os.path import join, dirname

path.insert(0, join(dirname(__file__), '..', '..', '..', 'python', 'alpaqa'))
import casadi_generator

if len(argv) < 2:
    print(f"Usage:    {argv[0]} <name>")
    exit(0)

x = cs.SX.sym("x")
y = cs.SX.sym("y")
z = cs.SX.sym("z")
unknowns = cs.vertcat(x, y, z)

p = cs.SX.sym("p")

# Formulate the NLP
f = x**2 + p * z**2
g = z + (1 - x)**2 - y

cg, _, _, _ = casadi_generator.generate_casadi_problem(
    cs.Function("f", [unknowns, p], [f]),
    cs.Function("g", [unknowns, p], [g]),
    name=argv[1])
cg.generate()