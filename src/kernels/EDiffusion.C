#include "EDiffusion.h"

template<>
InputParameters validParams<EDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("concentration", "The concentration of the diffusing species");
  params.addRequiredParam<Real>("diffcoeff", "The EDiffusion coefficient for the diffusing species");
  return params;
}

//Constructor
EDiffusion::EDiffusion(const InputParameters & parameters)
  :Kernel(parameters),
   _concentration(coupledValue("concentration")),
   _concentration_grad(coupledGradient("concentration")),
   _concentration_var(coupled("concentration")),
   _diffcoeff(getParam<Real>("diffcoeff"))

{
}

Real
EDiffusion::computeQpResidual()
{
  return _grad_test[_i][_qp] * _diffcoeff * _concentration_grad[_qp];
}


Real
EDiffusion::computeQpJacobian()
{
  return _grad_test[_i][_qp] * _diffcoeff * _grad_phi[_j][_qp];
}
