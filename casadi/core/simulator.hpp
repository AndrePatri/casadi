/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef CASADI_SIMULATOR_HPP
#define CASADI_SIMULATOR_HPP

#include "function.hpp"
#include "linsol.hpp"
#include "rootfinder.hpp"

namespace casadi {

  /** \defgroup main_simulator Title
      \par

      Create an ODE/DAE simulator
      Solves an initial value problem (IVP) with the differential equation given as an
      implicit ODE coupled to an algebraic equation and a set of output equations:

      \verbatim
      Time grid: [t0, t1, ..., tN]

      Initial conditions for forward integration
      x(t0)  = x0

      Sequential forward integration from t=tk to t=t{k+1}
      der(x) = fx(t, x, z, p, uk)         ODE
      0 = fz(t, x, z, p, uk)              Algebraic equations
      yk = fy(t, x, z, p, uk)             Output equations

      where we assume that the problem is index-1 (i.e. dfz/dz, is invertible) and furthermore that

      \endverbatim

      \generalsection{Simulator}
      \pluginssection{Simulator}

      \author Joel Andersson
      \date 2011-2021

      \identifier{21m} */
  /** \defgroup simulator Title
  * @copydoc main_simulator
  *  @{
  */

  /** \if EXPANDED
  * @copydoc main_simulator
  * \endif
  */
  ///@{
  CASADI_EXPORT Function simulator(const std::string& name, const std::string& solver,
    const SXDict& dae, const std::vector<double>& grid, const Dict& opts=Dict());
  CASADI_EXPORT Function simulator(const std::string& name, const std::string& solver,
    const MXDict& dae, const std::vector<double>& grid, const Dict& opts=Dict());
  CASADI_EXPORT Function simulator(const std::string& name, const std::string& solver,
    const Function& dae, const std::vector<double>& grid, const Dict& opts=Dict());
  ///@}

  /// Check if a particular plugin is available
  CASADI_EXPORT bool has_simulator(const std::string& name);

  /// Explicitly load a plugin dynamically
  CASADI_EXPORT void load_simulator(const std::string& name);

  /// Get the documentation string for a plugin
  CASADI_EXPORT std::string doc_simulator(const std::string& name);

  #ifndef SWIG
  /// Input arguments of an simulator
  enum SimulatorInput {
    /// Differential state at the initial time
    SIMULATOR_X0,
    /// Controls
    SIMULATOR_U,
    /// Initial guess for the algebraic variable at the initial time
    SIMULATOR_Z0,
    /// Parameters
    SIMULATOR_P,
    /// Number of input arguments of an simulator
    SIMULATOR_NUM_IN
  };

  /// Output arguments of an simulator
  enum SimulatorOutput {
    /// Differential state
    SIMULATOR_X,
    /// Algebraic variable
    SIMULATOR_Z,
    /// Number of output arguments of an simulator
    SIMULATOR_NUM_OUT
  };
  #endif // SWIG

  /** \brief Get input scheme of simulators

      \identifier{wx} */
  CASADI_EXPORT std::vector<std::string> simulator_in();

  /** \brief Get simulator output scheme of simulators

      \identifier{wy} */
  CASADI_EXPORT std::vector<std::string> simulator_out();

  /** \brief Get simulator input scheme name by index

      \identifier{x5} */
  CASADI_EXPORT std::string simulator_in(casadi_int ind);

  /** \brief Get output scheme name by index

      \identifier{x6} */
  CASADI_EXPORT std::string simulator_out(casadi_int ind);

  /** \brief Get the number of simulator inputs

      \identifier{x7} */
  inline casadi_int simulator_n_in() { return SIMULATOR_NUM_IN;}

  /** \brief Get the number of simulator outputs

      \identifier{x8} */
  inline casadi_int simulator_n_out() { return SIMULATOR_NUM_OUT;}
  /** @} */

} // namespace casadi

#endif // CASADI_SIMULATOR_HPP
