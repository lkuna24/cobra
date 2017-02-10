
[Mesh]
# x left right , y top bottom , z front back
#   1     2         3    4         5      6
  type = GeneratedMesh
  dim = 2
  nx = 90
  ny = 45
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  elem_type = QUAD4
[]


[Functions]
  [./c_one_y]
    type = ParsedFunction
    value = '(exp(((x-0.5)/(0.01)))+1)^(-1)'
  [../]

  [./c_two_y]
    type = ParsedFunction
    value = '(exp(-((x-0.5)/(0.01)))+1)^(-1)'
  [../]

  [./boundary_one_y]
    type = ParsedFunction
    value = '(sin(y))'
  [../]

  [./boundary_two_y]
    type = ParsedFunction
    value = '(sin(y))'
  [../]
[]

[ICs]
  [./concentrationone_ic]
    type = FunctionIC
    variable = concentrationone
    function = c_one_y
  [../]

  [./concentrationtwo_ic]
    type = FunctionIC
    variable = concentrationtwo
    function = c_two_y
  [../]
[]

[GlobalParams]
  diffcoeff = 1.0
  permittivity = 1.0
  valence = 1.0
  FaradayConst = 1.0
  gasconstR = 1.0
  temp = 1.0
  valenceone = 1.0
  valencetwo = -1.0
  concentrationone = concentrationone
  concentrationtwo = concentrationtwo
  Potential = Potential

[]


[AuxVariables]

  [./totalconcentration]
    order = CONSTANT
    family = MONOMIAL
  [../]

[]

[Variables]

  [./Potential]
    order = FIRST
    family = LAGRANGE
  [../]

  [./concentrationone]
    order = FIRST
    family = LAGRANGE
  [../]

  [./concentrationtwo]
    order = FIRST
    family = LAGRANGE
  [../]

[]

[AuxKernels]

  [./concentrationsum]
    type = ConcentrationSum
    variable = totalconcentration
[]

[Kernels]

  [./diffusionone]
    type = EDiffusion
    variable = concentrationone
    concentration = concentrationone
  [../]

  [./diffusiontwo]
    type = EDiffusion
    variable = concentrationtwo
    concentration = concentrationtwo
  [../]


  [./migrationone]
    type = Migration
    variable = concentrationone
    concentration = concentrationone
  [../]

  [./migrationtwo]
    type = Migration
    variable = concentrationtwo
    concentration = concentrationtwo
  [../]

  [./electroneutrality]
    type = NeutralityTwo
    variable = Potential
  [../]

  [./laplace]
    type = Electrostatics
    variable = Potential
  [../]

  [./timederiv1]
    type = TimeDerivative
    variable = concentrationone
  [../]

  [./timederiv2]
    type = TimeDerivative
    variable = concentrationtwo
  [../]

[]

[BCs]
   #Mesh Generation produces boundaries in counter-clockwise fashion
  [./leftpotential]
    type = FunctionDirichletBC
    variable = Potential
    boundary = 3
    function = boundary_one_y
  [../]

  [./rightpotential]
    type = FunctionDirichletBC
    variable = Potential
    boundary = 1
    function = boundary_two_y
  [../]

  #[./leftpotential]
  #  type = DirichletBC
  #  variable = Potential
  #  boundary = 3
  #  value = 0.5
  #[../]
  #
  #[./rightpotential]
  #  type = DirichletBC
  #  variable = Potential
  #  boundary = 1
  #  value = -0.5
  #[../]

  #[./concentrationone]
  #  type = DirichletBC
  #  variable = concentrationone
  #  boundary = 3
  #  value = 1
  #[../]
  #
  #[./concentrationtwo]
  #  type = DirichletBC
  #  variable = concentrationtwo
  #  boundary = 1
  #  value = 1
  #[../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    #petsc_options = '-snes_check_jacobian' #this only works for small problems and with solve_type NEWTON
    petsc_options_iname = '-ksp_gmres_restart  -snes_rtol -ksp_rtol     -pc_factor_zeropivot'
    petsc_options_value = '    121            1e-8      1e-8            1e-50     '
    # snes_rtol e-8 is default
    # ksp_rtol e-8 is default but rule of thumb says e-4 -> e-8 is acceptable
  [../]
[]

[Executioner]
  type = Transient
  #Transient = TimeDependenet , Steady = No Time Kernels
  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'
  num_steps = 100
  dt = 0.005
[]

[Outputs]
  execute_on = 'timestep_end'
  file_base = out_corrosiontest
  exodus = true
[]
