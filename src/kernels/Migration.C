#include "Migration.h"

template<>
InputParameters validParams<Migration>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("concentration", "The concentration of the diffusing species");
  params.addRequiredParam<Real>("diffcoeff", "The diffusion coefficient for the diffusing species");
  params.addRequiredParam<Real>("valence", "Valence of ionic species");
  params.addRequiredParam<Real>("FaradayConst", "Faradays Constant");
  params.addRequiredCoupledVar("Potential", "Potential in the domain");
  params.addRequiredParam<Real>("gasconstR", "gas constant R");
  params.addRequiredParam<Real>("temp", "temperature");
  return params;
}

//Constructor
Migration::Migration(const InputParameters & parameters)
  :Kernel(parameters),
   _concentration(coupledValue("concentration")),
   _concentration_var(coupled("concentration")),
   _diffcoeff(getParam<Real>("diffcoeff")),
   _valence(getParam<Real>("valence")),
   _FaradayConst(getParam<Real>("FaradayConst")),
   _Potential(coupledValue("Potential")),
   _Potential_grad(coupledGradient("Potential")),
   _Potential_var(coupled("Potential")),
   _gasconstR(getParam<Real>("gasconstR")),
   _temp(getParam<Real>("temp"))

{
}

Real
Migration::computeQpResidual()
{
  return _grad_test[_i][_qp] * _concentration[_qp] * _diffcoeff * _FaradayConst * _valence * (1/(_temp * _gasconstR)) * _Potential_grad[_qp];
}

Real
Migration::computeQpJacobian()
{
  return _grad_test[_i][_qp] * _phi[_j][_qp] *  _diffcoeff * _FaradayConst * _valence * (1/(_temp * _gasconstR)) * _Potential_grad[_qp];
}

Real
Migration::computeQpOffDiagJacobian(unsigned int jvar)
{
  return _grad_phi[_j][_qp] * _grad_test[_i][_qp] * _concentration[_qp] * _diffcoeff * _FaradayConst * _valence * (1/(_temp * _gasconstR));
}
