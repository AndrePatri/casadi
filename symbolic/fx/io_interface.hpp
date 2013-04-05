/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
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

#ifndef IO_INTERFACE_HPP
#define IO_INTERFACE_HPP

#include "../autogenerated.hpp"
#include "../sx/sx.hpp"
#include "../mx/mx.hpp"
#include "../options_functionality.hpp"

namespace CasADi{
  
  /** \brief  Structure that contains the numerical values for the inputs or outputs of a function
      \author Joel Andersson 
      \date 2010-2011
  */
  struct FunctionIO{    
    /// Input/output data
    Matrix<double> data;
  
    /// Forward derivative data
    std::vector< Matrix<double> > dataF;
    
    /// Adjoint derivative data
    std::vector< Matrix<double> > dataA;

    /// Temporary marker (initialized to zero)
    int tmp;

    // Constructor
    FunctionIO() : tmp(0){}
  };

  /** \brief Interface for accessing input and output data structures
      \author Joel Andersson
      \date 2013
  */
  template<class Derived>
  class IOInterface {
  public:
    
    //@{
    /// Access input argument
    inline const Matrix<double>& input(int iind=0) const{ return inputS<true>(iind).data;}
    inline const Matrix<double>& input(const std::string &iname) const{  return input(inputSchemeEntry(iname)); }
    inline const Matrix<double>& inputNoCheck(int iind=0) const{ return inputS<false>(iind).data;}
#ifdef SWIG
    %rename(inputRef) input;
#endif
    inline Matrix<double>& input(int iind=0){ return inputS<true>(iind).data;}
    inline Matrix<double>& input(const std::string &iname){ return input(inputSchemeEntry(iname));}
    inline Matrix<double>& inputNoCheck(int iind=0){ return inputS<false>(iind).data;}
    //@}
    
    //@{
    /// Access output argument
    inline const Matrix<double>& output(int oind=0) const{ return outputS<true>(oind).data;}
    inline const Matrix<double>& outputNoCheck(int oind=0) const{ return outputS<false>(oind).data;}
#ifdef SWIG
    %rename(outputRef) output;
#endif
    inline Matrix<double>& output(int oind=0){ return outputS<true>(oind).data;}
    inline Matrix<double>& outputNoCheck(int oind=0){ return outputS<false>(oind).data;}
    //@}

    //@{
    /// Access forward seed
    const Matrix<double>& fwdSeed(int iind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->fwdSeed(iind,dir); }
    const Matrix<double>& fwdSeedNoCheck(int iind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->fwdSeedNoCheck(iind,dir); }
#ifdef SWIG
    %rename(fwdSeedRef) fwdSeed;
#endif
    Matrix<double>& fwdSeed(int iind=0, int dir=0){
      try{
        return inputS<true>(iind).dataF.at(dir);
      } catch(std::out_of_range&){
        std::stringstream ss;
        if(inputS<true>(iind).dataF.empty()){
          ss << "No forward directions ";
        } else {
          ss << "Forward direction " << dir << " is out of range [0," << inputS<true>(iind).dataF.size() << ") ";
        }
        ss << "for function " << static_cast<const Derived*>(this)->getOption("name");
        throw CasadiException(ss.str());
      }
    }
    Matrix<double>& fwdSeedNoCheck(int iind=0, int dir=0){ return inputS<false>(iind).dataF[dir]; }
    //@}

    //@{
    /// Access forward sensitivity
    const Matrix<double>& fwdSens(int oind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->fwdSens(oind,dir);}
    const Matrix<double>& fwdSensNoCheck(int oind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->fwdSensNoCheck(oind,dir);}
#ifdef SWIG
    %rename(fwdSensRef) fwdSens;
#endif
    Matrix<double>& fwdSens(int oind=0, int dir=0){
      try{
        return outputS<true>(oind).dataF.at(dir);
      } catch(std::out_of_range&){
        std::stringstream ss;
        if(outputS<true>(oind).dataF.empty()){
          ss << "No forward directions ";
        } else {
          ss << "Forward direction " << dir << " is out of range [0," << outputS<true>(oind).dataF.size() << ") ";
        }
        ss << "for function " << static_cast<const Derived*>(this)->getOption("name");
        throw CasadiException(ss.str());
      }
    }
    Matrix<double>& fwdSensNoCheck(int oind=0, int dir=0){ return outputS<false>(oind).dataF[dir]; }
    //@}

    //@{
    /// Access adjoint seed
    const Matrix<double>& adjSeed(int oind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->adjSeed(oind,dir);}
    const Matrix<double>& adjSeedNoCheck(int oind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->adjSeedNoCheck(oind,dir);}
#ifdef SWIG
    %rename(adjSeedRef) adjSeed;
#endif
    Matrix<double>& adjSeed(int oind=0, int dir=0){
      try{
        return outputS<true>(oind).dataA.at(dir);
      } catch(std::out_of_range&){
        std::stringstream ss;
        if(outputS<true>(oind).dataA.empty()){
          ss << "No adjoint directions ";
        } else {
          ss << "Adjoint direction " << dir << " is out of range [0," << outputS<true>(oind).dataA.size() << ") ";
        }
        ss << "for function " << static_cast<const Derived*>(this)->getOption("name");
        throw CasadiException(ss.str());
      }
    }
    Matrix<double>& adjSeedNoCheck(int oind=0, int dir=0){ return outputS<false>(oind).dataA[dir];}
    //@}

    //@{
    /// Access forward sensitivity
    const Matrix<double>& adjSens(int iind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->adjSens(iind,dir);}
    const Matrix<double>& adjSensNoCheck(int iind=0, int dir=0) const{ return const_cast<IOInterface<Derived>*>(this)->adjSensNoCheck(iind,dir);}
#ifdef SWIG
    %rename(adjSensRef) adjSens;
#endif
    Matrix<double>& adjSens(int iind=0, int dir=0){
      try{
        return inputS<true>(iind).dataA.at(dir);
      } catch(std::out_of_range&){
        std::stringstream ss;
        if(inputS<true>(iind).dataA.empty()){
          ss << "No adjoint directions ";
        } else {
          ss << "Adjoint direction " << dir << " is out of range [0," << inputS<true>(iind).dataA.size() << ") ";
        }
        ss << "for function " << static_cast<const Derived*>(this)->getOption("name");
        throw CasadiException(ss.str());
      }
    }
    Matrix<double>& adjSensNoCheck(int iind=0, int dir=0){ return inputS<false>(iind).dataA[dir];}
    //@}

    /// Get the number of function inputs
    inline int getNumInputs() const{ return static_cast<const Derived*>(this)->input_struct().size();}

    /// Get the number of function outputs
    inline int getNumOutputs() const{ return static_cast<const Derived*>(this)->output_struct().size();}

    /// Set the number of function inputs
    inline void setNumInputs(int num_in){ static_cast<Derived*>(this)->input_struct().resize(num_in); }
    
    /// Set the number of function outputs
    inline void setNumOutputs(int num_out){ static_cast<Derived*>(this)->output_struct().resize(num_out); }

    /** \brief  Access an input */
    template<bool check>
    FunctionIO& inputS(int i){
      if(check){
	try{
	  return static_cast<Derived*>(this)->input_struct().at(i);
	} catch(std::out_of_range&){
	  std::stringstream ss;
	  ss <<  "In function " << static_cast<const Derived*>(this)->getOption("name") << ": input " << i << " not in interval [0," << getNumInputs() << ")";
	  if (!static_cast<const Derived*>(this)->isInit()) ss << std::endl << "Did you forget to initialize?";
	  throw CasadiException(ss.str());
	}
      } else {
	return static_cast<Derived*>(this)->input_struct()[i];	
      }
    }

    /** \brief  Const access an input */
    template<bool check>
    inline const FunctionIO& inputS(int i) const{
      return const_cast<IOInterface<Derived>*>(this)->inputS<check>(i);
    }
    
    /** \brief  Access an output*/
    template<bool check>
    FunctionIO& outputS(int i){
      if(check){
	try{
	  return static_cast<Derived*>(this)->output_struct().at(i);
	} catch(std::out_of_range&){
	  std::stringstream ss;
	  ss <<  "In function " << static_cast<const Derived*>(this)->getOption("name") << ": output " << i << " not in interval [0," << getNumOutputs() << ")";
	  if (!static_cast<const Derived*>(this)->isInit()) ss << std::endl << "Did you forget to initialize?";
	  throw CasadiException(ss.str());
	}
      } else {
	return static_cast<Derived*>(this)->output_struct()[i];	
      }
    }

    /** \brief  Const access an output*/
    template<bool check>
    inline const FunctionIO& outputS(int i) const{
      return const_cast<IOInterface<Derived>*>(this)->outputS<check>(i);
    }

    /** \brief Set input scheme */
    void setInputScheme(CasADi::InputOutputScheme scheme){ static_cast<Derived*>(this)->inputScheme() = scheme;}

    /** \brief Set output scheme */
    void setOutputScheme(CasADi::InputOutputScheme scheme){ static_cast<Derived*>(this)->outputScheme() = scheme;}

    /** \brief Get input scheme */
    CasADi::InputOutputScheme getInputScheme() const{ return static_cast<const Derived*>(this)->inputScheme(); }

    /** \brief Get output scheme */
    CasADi::InputOutputScheme getOutputScheme() const{ return static_cast<const Derived*>(this)->outputScheme(); }

    /** \brief Find the index for a string describing a particular entry of an input scheme
     * example:  schemeEntry("x_opt")  -> returns  NLP_X_OPT if FXInternal adheres to SCHEME_NLPINput 
     */
    int inputSchemeEntry(const std::string &name) const{ return schemeEntry(static_cast<const Derived*>(this)->inputScheme(),name);}

    /** \brief Find the index for a string describing a particular entry of an output scheme
     * example:  schemeEntry("x_opt")  -> returns  NLP_X_OPT if FXInternal adheres to SCHEME_NLPINput 
     */
    int outputSchemeEntry(const std::string &name) const{ return schemeEntry(static_cast<const Derived*>(this)->outputScheme(),name);}

    /** \brief Find the index for a string describing a particular entry of a scheme
     * example:  schemeEntry("x_opt")  -> returns  NLP_X_OPT if FXInternal adheres to SCHEME_NLPINput 
     */
    int schemeEntry(CasADi::InputOutputScheme scheme,const std::string &name) const{
      if (scheme==SCHEME_unknown) casadi_error("Unable to look up '" <<  name<< "' in input scheme, as the input scheme of this function is unknown. You can only index with integers.");
      if (name=="") casadi_error("FXInternal::inputSchemeEntry: you supplied an empty string as the name of a entry in " << getSchemeName(scheme) << ". Available names are: " << getSchemeEntryNames(scheme) << ".");
      int n = getSchemeEntryEnum(scheme,name);
      if (n==-1) casadi_error("FXInternal::inputSchemeEntry: could not find entry '" << name << "' in " << getSchemeName(scheme) << ". Available names are: " << getSchemeEntryNames(scheme) << ".");
      return n;
    }

#ifdef DOXYGENPROC
    //// \defgroup setter_getter_T
    //// T can be double&, double*, std::vector<double>&, Matrix<double> &\n
    /// Assumes a properly allocated val.\n

    /// \name Setters
    /// Set/get an input, output, forward seed/sensitivity or adjoint seed/sensitivity\n
    /// \copydoc setter_getter_T
    /// 
    /// @{
    /** 
	\brief Reads in the input argument from val.
	\copydoc setter_getter_T
    */
    void setInput(T val, int iind=0) const;
    /** 
	\brief Reads in the output argument from val.
	\copydoc setter_getter_T
    */
    void setOutput(T val, int oind=0) const;
    /** 
	\brief Reads in the forward seed from val.
	\copydoc setter_getter_T
    */
    void setFwdSeed(T val,  int iind=0, int dir=0) const;
    /** 
	\brief Reads in the forward sensitivity from val.
    */
    void setFwdSens(T val, int oind=0, int dir=0) const ;
    /** 
	\brief Reads in the adjoint seed from val.
	\copydoc setter_getter_T
    */
    void setAdjSeed(T val,  int oind=0, int dir=0) const;
    /** 
	\brief Reads in the adjoint sensitivity from val.
	\copydoc setter_getter_T
    */
    void setAdjSens(T val, int iind=0, int dir=0) const ;
    /// @}

#endif

#define SETTERS(T)							\
    void setInput(T val, int iind=0)             { static_cast<const Derived*>(this)->assertInit(); input(iind).set(val);  } \
    void setOutput(T val, int oind=0)            { static_cast<const Derived*>(this)->assertInit(); output(oind).set(val); } \
    void setFwdSeed(T val, int iind=0, int dir=0){ static_cast<const Derived*>(this)->assertInit(); fwdSeed(iind,dir).set(val); } \
    void setFwdSens(T val, int oind=0, int dir=0){ static_cast<const Derived*>(this)->assertInit(); fwdSens(oind,dir).set(val); } \
    void setAdjSeed(T val, int oind=0, int dir=0){ static_cast<const Derived*>(this)->assertInit(); adjSeed(oind,dir).set(val); } \
    void setAdjSens(T val, int iind=0, int dir=0){ static_cast<const Derived*>(this)->assertInit(); adjSens(iind,dir).set(val); }

#ifndef DOXYGENPROC
    SETTERS(double);
#ifndef SWIG
    SETTERS(const double*);
#endif // SWIG
    SETTERS(const std::vector<double>&);
    SETTERS(const Matrix<double>&);
#endif // DOXYGENPROC

#undef SETTERS

#define GETTERS(T)							\
    void getInput(T val, int iind=0) const             { static_cast<const Derived*>(this)->assertInit(); input(iind).get(val);} \
    void getOutput(T val, int oind=0) const            { static_cast<const Derived*>(this)->assertInit(); output(oind).get(val);} \
    void getFwdSeed(T val, int iind=0, int dir=0) const{ static_cast<const Derived*>(this)->assertInit(); fwdSeed(iind,dir).get(val);} \
    void getFwdSens(T val, int oind=0, int dir=0) const{ static_cast<const Derived*>(this)->assertInit(); fwdSens(oind,dir).get(val);} \
    void getAdjSeed(T val, int oind=0, int dir=0) const{ static_cast<const Derived*>(this)->assertInit(); adjSeed(oind,dir).get(val);} \
    void getAdjSens(T val, int iind=0, int dir=0) const{ static_cast<const Derived*>(this)->assertInit(); adjSens(iind,dir).get(val);}

#ifndef DOXYGENPROC
    GETTERS(double&);
#ifndef SWIG
    GETTERS(double*);
#endif // SWIG
    GETTERS(std::vector<double>&);
    GETTERS(Matrix<double>&);
#endif // DOXYGENPROC
#undef GETTERS

#ifdef DOXYGENPROC
    /// \name Getters
    /// A group of accessor for numerical data that operate on preallocated data.\n
    /// get an input, output, forward seed/sensitivity or adjoint seed/sensitivity\n
    /// \copydoc setter_getter_T
    /// @{

    /** \brief Writes out the input argument into val.
	\copydoc setter_getter_T
    */
    void getInput(T val, int iind=0) const;
 
    /** 
	\brief Writes out the output argument into val.
	\copydoc setter_getter_T
    */
    void getOutput(T val, int oind=0) const;

    /** 
	\brief Writes out the forward seed into val.
	\copydoc setter_getter_T
    */
    void getFwdSeed(T val,  int iind=0, int dir=0) const;

    /**  
	 \brief Writes out the forward sensitivity into val.
	 \copydoc setter_getter_T
    */
    void getFwdSens(T val, int oind=0, int dir=0) const;
    /** 
	\brief Writes out the adjoint seed into val.
	\copydoc setter_getter_T
    */
    void getAdjSeed(T val,  int oind=0, int dir=0) const ;

    /** 
	\brief Writes out the adjoint sensitivity into val.
	\copydoc setter_getter_T
    */
    void getAdjSens(T val, int iind=0, int dir=0) const;
    /// @}
#endif

  };


} // namespace CasADi


#endif // IO_INTERFACE_HPP
