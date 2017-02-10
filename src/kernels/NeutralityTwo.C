#include "NeutralityTwo.h"

template<>
InputParameters validParams<NeutralityTwo>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("concentrationone", "The concentration of the diffusing species");
  params.addRequiredParam<Real>("valenceone", "Valence of diffusing species");
  params.addRequiredCoupledVar("concentrationtwo", "The concentration of the dissolving species");
  params.addRequiredParam<Real>("valencetwo", "Valence of dissolving species");
  params.addRequiredParam<Real>("FaradayConst", "Faradays Constant");
  return params;
}

//Constructor
NeutralityTwo::NeutralityTwo(const InputParameters & parameters)
  :Kernel(parameters),
   _concentrationone(coupledValue("concentrationone")),
   _concentrationone_var(coupled("concentrationone")),
   _valenceone(getParam<Real>("valenceone")),
   _concentrationtwo(coupledValue("concentrationtwo")),
   _concentrationtwo_var(coupled("concentrationtwo")),
   _valencetwo(getParam<Real>("valencetwo")),
   _FaradayConst(getParam<Real>("FaradayConst"))

{
}

Real
NeutralityTwo::computeQpResidual()
{
  return _test[_i][_qp]* _FaradayConst *(_valenceone * _concentrationone[_qp] + _valencetwo * _concentrationtwo[_qp]);
}

Real
NeutralityTwo::computeQpJacobian()
{
  return _phi[_j][_qp]* _FaradayConst *(_valenceone * _concentrationone[_qp] + _valencetwo * _concentrationtwo[_qp]);
}


Real
NeutralityTwo::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real summed = 0.0;
  if (jvar == _concentrationone_var || jvar == _concentrationtwo_var)
  {
    if (jvar == _concentrationone_var)
    {
      summed += _test[_i][_qp] * _FaradayConst *(_valenceone * _phi[_j][_qp]);
    }
    else if (jvar == _concentrationtwo_var)
    {
      summed += _test[_i][_qp] * _FaradayConst *(_valencetwo * _phi[_j][_qp]);
    }
    return summed;
  }
  else
  {
    return 0.0;
  }
}
