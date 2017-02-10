#include "ConcentrationSum.h"

template<>

InputParameters validParams<ConcentrationSum>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("concentrationone","concentrationone");
  params.addRequiredCoupledVar("concentrationtwo","concentrationtwo");
  return params;
}

ConcentrationSum::ConcentrationSum(const InputParameters & parameters) :
  AuxKernel(parameters),
   _concentrationone(coupledValue("concentrationone")),
   _concentrationtwo(coupledValue("concentrationtwo"))
{
}

Real
ConcentrationSum::computeValue()

{
  return _concentrationone[_qp] * _concentrationtwo[_qp];
}
