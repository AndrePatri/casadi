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


#ifndef CASADI_BSPLINE_INTERPOLANT_HPP
#define CASADI_BSPLINE_INTERPOLANT_HPP

#include "casadi/core/interpolant_impl.hpp"
#include <casadi/solvers/casadi_interpolant_bspline_export.h>

/** \defgroup plugin_Interpolant_bspline
*/

/** \pluginsection{Interpolant,bspline} */

/// \cond INTERNAL

namespace casadi {
  class BSplineCommon;
  /** \brief \pluginbrief{Interpolant,bspline}

    N-dimensional BSpline interpolator

    Uses not-a-knot conditions.
    For 1D and 2D cases, this code is equivalent to fitpack

    @copydoc Interpolant_doc
    @copydoc plugin_Interpolant_bspline
    \author Joris Gillis
    \date 2017
  */
  class CASADI_INTERPOLANT_BSPLINE_EXPORT BSplineInterpolant : public Interpolant {
  public:
    // Constructor
    BSplineInterpolant(const std::string& name,
                      const MX& grid,
                      const std::vector<casadi_int>& offset,
                      const MX& values,
                      casadi_int m);

    // Destructor
    ~BSplineInterpolant() override;

    // Get name of the plugin
    const char* plugin_name() const override { return "bspline";}

    // Get name of the class
    std::string class_name() const override { return "BSplineInterpolant";}

    /** \brief  Create a new Interpolant */
    static Interpolant* creator(const std::string& name,
                                const MX& grid,
                                const std::vector<casadi_int>& offset,
                                const MX& values,
                                casadi_int m) {
      return new BSplineInterpolant(name, grid, offset, values, m);
    }

    // Initialize
    void init(const Dict& opts) override;

    /// Evaluate numerically
    int eval(const double** arg, double** res, casadi_int* iw, double* w, void* mem) const override;

    ///@{
    /** \brief Full Jacobian */
    bool has_jacobian() const override { return true;}
    Function get_jacobian(const std::string& name,
                                      const std::vector<std::string>& inames,
                                      const std::vector<std::string>& onames,
                                      const Dict& opts) const override;
    ///@}


    ///@{
    /** \brief Return function that calculates forward derivatives
     *    forward(nfwd) returns a cached instance if available,
     *    and calls <tt>Function get_forward(casadi_int nfwd)</tt>
     *    if no cached version is available.
     */
    bool has_forward(casadi_int nfwd) const override { return true; }
    Function get_forward(casadi_int nfwd, const std::string& name,
                                 const std::vector<std::string>& inames,
                                 const std::vector<std::string>& onames,
                                 const Dict& opts) const override;
    ///@}

    ///@{
    /** \brief Return function that calculates adjoint derivatives
     *    reverse(nadj) returns a cached instance if available,
     *    and calls <tt>Function get_reverse(casadi_int nadj)</tt>
     *    if no cached version is available.
     */
    bool has_reverse(casadi_int nadj) const override { return true; }
    Function get_reverse(casadi_int nadj, const std::string& name,
                                 const std::vector<std::string>& inames,
                                 const std::vector<std::string>& onames,
                                 const Dict& opts) const override;
    ///@}

    /** \brief Is codegen supported? */
    bool has_codegen() const override { return true;}

    /** \brief Generate code for the body of the C function */
    void codegen_body(CodeGenerator& g) const override;

    /** \brief Generate code for the declarations of the C function */
    void codegen_declarations(CodeGenerator& g) const override;

    /// A documentation string
    static const std::string meta_doc;

    ///@{
    /** \brief Options */
    static const Options options_;
    const Options& get_options() const override { return options_;}
    ///@}

    // Spline Function
    Function S_;

    /** \brief  Propagate sparsity forward */
    int sp_forward(const bvec_t** arg, bvec_t** res,
                    casadi_int* iw, bvec_t* w, void* mem) const override {
      return S_->sp_forward(arg, res, iw, w, mem);
    }

    /** \brief  Propagate sparsity backwards */
    int sp_reverse(bvec_t** arg, bvec_t** res,
        casadi_int* iw, bvec_t* w, void* mem) const override {
      return S_->sp_reverse(arg, res, iw, w, mem);
    }

    static MX greville_points(const MX& x, casadi_int deg);

    void serialize_body(SerializingStream &s) const override;

    /** \brief Deserialize with type disambiguation */
    static ProtoFunction* deserialize(DeserializingStream& s) { return new BSplineInterpolant(s); }

  protected:
     /** \brief Deserializing constructor */
    explicit BSplineInterpolant(DeserializingStream& s);

    static MX not_a_knot(const MX& x, casadi_int k);

    MX construct_graph(const MX& x, const MX& values, const MX& g, const Dict& linsol_options, const Dict& opts);

    enum FittingAlgorithm {ALG_NOT_A_KNOT, ALG_SMOOTH_LINEAR};

    /// Only used during init, no need to serialize these
    std::string linear_solver_;
    FittingAlgorithm algorithm_;
    double smooth_linear_frac_;
    std::vector<casadi_int> degree_;
  };


} // namespace casadi

/// \endcond
#endif // CASADI_BSPLINE_INTERPOLANT_HPP
