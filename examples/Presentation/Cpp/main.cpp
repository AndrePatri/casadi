#include <alpaqa/config/config.hpp>
#include <alpaqa/inner/directions/panoc/lbfgs.hpp>
#include <alpaqa/inner/panoc.hpp>
#include <alpaqa/outer/alm.hpp>

#include <iostream>

int main() {
    USING_ALPAQA_CONFIG(alpaqa::DefaultConfig);

    // Problem specification
    alpaqa::FunctionalProblem<config_t> problem{2, 1}; // # variables, # constraints

    // minimize  ½ xᵀHx
    //  s.t.     Ax ≤ b
    mat H(2, 2);
    H << 3, -1, -1, 3;
    mat A(1, 2);
    A << 2, 1;
    vec b(1);
    b << -1;

    problem.f           = [&](crvec x) { return 0.5 * x.dot(H * x); };
    problem.grad_f      = [&](crvec x, rvec gr) { gr = H * x; };
    problem.g           = [&](crvec x, rvec g) { g = A * x; };
    problem.grad_g_prod = [&](crvec x, crvec y, rvec gr) {
        (void)x;
        gr = A.transpose() * y;
    };

    // Specify the bounds
    problem.C.lowerbound = vec::Constant(problem.n, -alpaqa::inf<config_t>);
    problem.C.upperbound = vec::Constant(problem.n, alpaqa::inf<config_t>);
    problem.D.lowerbound = vec::Constant(problem.m, -alpaqa::inf<config_t>);
    problem.D.upperbound = b;

    // Define the solvers to use
    using Accelerator = alpaqa::LBFGS<config_t>;
    using InnerSolver = alpaqa::PANOCSolver<Accelerator>;
    using OuterSolver = alpaqa::ALMSolver<InnerSolver>;

    // Settings for the outer augmented Lagrangian method
    OuterSolver::Params almparam;
    almparam.ε              = 1e-8; // tolerance
    almparam.δ              = 1e-8;
    almparam.Δ              = 10; // penalty update factor
    almparam.max_iter       = 20;
    almparam.print_interval = 1;

    // Settings for the inner PANOC solver
    InnerSolver::Params panocparam;
    panocparam.max_iter       = 500;
    panocparam.print_interval = 10;
    // Settings for the L-BFGS algorithm used by PANOC
    Accelerator::Params lbfgsparam;
    lbfgsparam.memory = 2;

    // Create an ALM solver using PANOC as inner solver
    OuterSolver solver{
        almparam,                 // params for outer solver
        {panocparam, lbfgsparam}, // inner solver
    };

    // Initial guess
    vec x(2);
    x << 2, 2; // decision variables
    vec y(1);
    y << 1; // Lagrange multipliers

    // Solve the problem
    auto stats = solver(problem, y, x);
    // y and x have been overwritten by the solution

    // Print the results
    std::cout << "status: " << stats.status << std::endl;
    std::cout << "inner iterations: " << stats.inner.iterations << std::endl;
    std::cout << "outer iterations: " << stats.outer_iterations << std::endl;
    std::cout << "elapsed time:     " << stats.elapsed_time.count() * 1e-6
              << 's' << std::endl;
    std::cout << "x = " << x.transpose() << std::endl;
    std::cout << "y = " << y.transpose() << std::endl;
    std::cout << "f = " << problem.f(x) << std::endl;
}