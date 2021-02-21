#pragma once

#include <panoc-alm/problem.hpp>

/// Load an objective function generated by CasADi.
std::function<pa::Problem::f_sig>
load_CasADi_objective(const char *so_name, const char *fun_name = "f");
/// Load the gradient of an objective function generated by CasADi.
std::function<pa::Problem::grad_f_sig>
load_CasADi_gradient_objective(const char *so_name,
                               const char *fun_name = "grad_f");
/// Load a constraint function generated by CasADi.
std::function<pa::Problem::g_sig>
load_CasADi_constraints(const char *so_name, const char *fun_name = "g");
/// Load the gradient of a constraint function generated by CasADi.
std::function<pa::Problem::grad_g_sig>
load_CasADi_gradient_constraints(const char *so_name,
                                 const char *fun_name = "grad_g");
