/**
For now it reads problem in mps format.
Manipulating/building functions will be supported later.


 **/


#ifndef OsiConicSolverInterface_H
#define OsiConicSolverInterface_H

// OSI headers
#include <OsiSolverInterface.hpp>

class OsiConicCuts;

typedef enum {
  OSI_QUAD=0,
  OSI_RQUAD
} OsiConeType;

class OsiConicSolverInterface: virtual public OsiSolverInterface {
public:
  // void read(const char * data_file);
  // get conic constraints
  virtual void getConicConstraint(int index, OsiConeType & type,
				  int & numMembers,
				  int *& members) const = 0;
  // add conic constraints
  virtual void addConicConstraint(OsiConeType type,
				  int numMembers,
				  const int * members) = 0;
  virtual void removeConicConstraint(int index) = 0;
  virtual int getNumCones() const = 0;
  virtual OsiConicSolverInterface * clone(bool) const = 0;
  virtual ~OsiConicSolverInterface() {};
  virtual int readMps(const char * filename, const char * extension="mps");
  // un-hide OsiSolverInterfaces applyCuts function
  // todo(aykut): It is usefull for what? Explain
  // using OsiSolverInterface::applyCuts;
  // virtual OsiSolverInterface::ApplyCutsReturnCode applyCuts (
  // 	const OsiCuts & cs,
  //       double effectivenessLb=0.0);
  // overloads applyCuts for linear cuts with conic cut argument
  // for applying row cuts we use methods inherited from OsiSolverInterface
  using OsiSolverInterface::applyCuts;
  virtual OsiSolverInterface::ApplyCutsReturnCode applyCuts (
   	const OsiConicCuts & cs,
	double effectivenessLb=0.0);
};

#endif
