/*****************************************************************************
 * Project: BaBar detector at the SLAC PEP-II B-factory
 * Package: RooFitCore
 *    File: $Id: RooUnblindCPAsymVar.cc,v 1.6 2001/11/20 04:00:55 verkerke Exp $
 * Authors:
 *   DK, David Kirkby, Stanford University, kirkby@hep.stanford.edu
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu
 * History:
 *   07-Mar-2001 WV Created initial version
 *
 * Copyright (C) 2001 University of California
 *****************************************************************************/

// -- CLASS DESCRIPTION [REAL] --
//
// Implementation of BlindTools' CP asymmetry blinding method
// A RooUnblindCPAsymVar object is a real valued function
// object, constructed from a blind value holder and a 
// set of unblinding parameters. When supplied to a PDF
// in lieu of a regular parameter, the blind value holder
// supplied to the unblinder objects will in a fit be minimized 
// to blind value corresponding to the actual minimum of the
// parameter. The transformation is chosen such that the
// the error on the blind parameters is indentical to that
// of the unblind parameter

#include "RooFitCore/RooArgSet.hh"
#include "RooFitModels/RooUnblindCPAsymVar.hh"


ClassImp(RooUnblindCPAsymVar)
;



RooUnblindCPAsymVar::RooUnblindCPAsymVar() : _blindEngine("") 
{
  // Default constructor
}


RooUnblindCPAsymVar::RooUnblindCPAsymVar(const char *name, const char *title,
					 const char *blindString, RooAbsReal& cpasym)
  : RooAbsHiddenReal(name,title), _blindEngine(blindString), 
  _asym("asym","CP Asymmetry",this,cpasym)
{  
  // Constructor from a given RooAbsReal (to hold the blind value) and a set of blinding parameters
}


RooUnblindCPAsymVar::RooUnblindCPAsymVar(const char *name, const char *title,
					 const char *blindString, RooAbsReal& cpasym, RooAbsCategory& blindState)
  : RooAbsHiddenReal(name,title,blindState), _blindEngine(blindString), 
  _asym("asym","CP Asymmetry",this,cpasym)
{  
  // Constructor from a given RooAbsReal (to hold the blind value) and a set of blinding parameters
}


RooUnblindCPAsymVar::RooUnblindCPAsymVar(const RooUnblindCPAsymVar& other, const char* name) : 
  RooAbsHiddenReal(other, name), 
  _blindEngine(other._blindEngine), 
  _asym("asym",this,other._asym)
{
  // Copy constructor
}


RooUnblindCPAsymVar::~RooUnblindCPAsymVar() 
{
  // Copy constructor
}


Double_t RooUnblindCPAsymVar::evaluate() const
{
  if (isHidden()) {
    // Blinding active for this event
    return _blindEngine.UnHideAsym(_asym);
  } else {
    // Blinding not active for this event
    return _asym ;
  }
}
