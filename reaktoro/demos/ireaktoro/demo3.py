import sys
sys.path.append('/home/leal_a/git/Reaktoro/reaktoro/')
from reaktoro.interpreter.ireaktoro import interpret

input = """
ChemicalSystem:
    Database: supcrt98.xml
    AqueousPhase:
        Species: H2O(l) H+ OH- HCO3- CO2(aq) Ca+2 Mg+2 Na+ Cl-
    GaseousPhase:
        Species: H2O(g) CO2(g)
    MineralPhases: Calcite Dolomite

ReactionSystem:
    MineralReaction Calcite:
        Equation: -1:Calcite -1:H+ 1:Ca+2 1:HCO3-
        SpecificSurfaceArea: 9.8 cm2/g
        Mechanism Acid:
            RateConstant: 10**(-0.30) mol/(m2*s)
            ActivationEnergy: 14.4 kJ/mol
            ActivityPower H+: 1.0
        Mechanism Neutral:
            RateConstant: 10**(-5.81) mol/(m2*s)
            ActivationEnergy: 23.5 kJ/mol

    MineralReaction Dolomite:
        Equation: -1:Dolomite -2:H+ 2:HCO3- 1:Ca+2 1:Mg+2
        SpecificSurfaceArea: 9.8 cm2/g
        Mechanism Acid:
            RateConstant: 10**(-3.19) mol/(m2*s)
            ActivationEnergy: 36.1 kJ/mol
            ActivityPower H+: 0.5
        Mechanism Neutral:
            RateConstant: 10**(-7.53) mol/(m2*s)
            ActivationEnergy: 52.2 kJ/mol

Equilibrium State:
    Temperature: 60 celsius
    Pressure: 150 bar
    Mixture:
        H2O: 1 kg
        CO2: 10 mol
        NaCl: 1 mol
        MgCl2: 0.05 mol
        CaCl2: 0.01 mol
    InertSpecies:
        Calcite: 3 mol
        Dolomite: 1e-12 mol

KineticPath:
    From: 0
    To: 1 month
    InitialCondition: State
    KineticSpecies: Calcite Dolomite
    Plot 1:
        x: t:month
        y: n[Dolomite]
    Plot 2:
        x: t:month
        y: n[Calcite]
    Plot 3:
        x: t:month
        y: pH
"""

interpret(input)
