#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/Math/Matrix/Utilities/SimplexHeaders.hpp>

namespace alba
{

namespace matrix
{

template <typename DataType>
AlbaMatrix<DataType> constructSimplexTableWithLessThanConstraints(
        AlbaMatrix<DataType> const& constraintsCoefficients,
        AlbaMatrixData<DataType> const& constraintsValues,
        AlbaMatrixData<DataType> const& objectiveFunctionCoefficients){
    // Table should look like this:
    // A is constraintsCoefficients
    // b is constraintsValues    // c is objectiveFunctionCoefficients
    //
    //         ** n size *   m size        * 1 *
    //* m size *|        |                 |   |
    //*        *|    A   | Identity matrix | b |
    //*        *|        |                 |   |
    //*    1   *|    c   |        0        | 0 |

    assert(constraintsCoefficients.getNumberOfColumns() == objectiveFunctionCoefficients.size());
    assert(constraintsCoefficients.getNumberOfRows() == constraintsValues.size());
    unsigned int numberOfColumns = constraintsCoefficients.getNumberOfColumns() + constraintsCoefficients.getNumberOfRows() + 1;
    unsigned int numberOfRows = constraintsCoefficients.getNumberOfRows()+1;

    AlbaMatrix<DataType> result(numberOfColumns, numberOfRows);
    constraintsCoefficients.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {
        result.setEntry(x, y, constraintsCoefficients.getEntry(x, y));
    });
    for(unsigned int i=0; i<constraintsCoefficients.getNumberOfRows(); i++) // setting 1 for identity matrix
    {
        result.setEntry(i+constraintsCoefficients.getNumberOfColumns(), i, 1);
    }
    result.setRow(numberOfRows-1, objectiveFunctionCoefficients);
    result.setColumn(numberOfColumns-1, constraintsValues);
    return result;
}

template <typename DataType>
void solveSimplexTable(AlbaMatrix<DataType> & simplexTable)
{
    bool didPivot(true);
    while(didPivot)
    {
        didPivot=false;
        unsigned int pivotingColumn(getPivotingColumnUsingBlandsRule(simplexTable));
        if(pivotingColumn < simplexTable.getNumberOfColumns())
        {
            unsigned int pivotingRow(getPivotingRowUsingMinRatioRule(simplexTable, pivotingColumn));
            if(pivotingRow < simplexTable.getNumberOfRows()) // if no pivoting row then its unbounded
            {
                pivotAt(simplexTable, pivotingColumn, pivotingRow);
                // Pivoting makes the column of the objective function (last row) result to zero
                didPivot=true;
            }
        }    }
}

template <typename DataType>bool isOptimal(AlbaMatrix<DataType> const& simplexTable)
{
    unsigned int lastY(simplexTable.getNumberOfRows()-1);
    bool result(true);
    for(unsigned int x=0; x<simplexTable.getNumberOfColumns(); x++)
    {
        if(simplexTable.getEntry(x, lastY) > 0)
        {
            result = false;
        }
    }
    return result;
}

template <typename DataType>
unsigned int getPivotingColumnUsingBlandsRule(AlbaMatrix<DataType> const& simplexTable)
{
    // Findint entring q using Bland's rule: index of first column whose objective function coefficient is positive

    unsigned int lastY(simplexTable.getNumberOfRows()-1);
    unsigned int x=0;
    for(; x<simplexTable.getNumberOfColumns(); x++)
    {
        if(simplexTable.getEntry(x, lastY) > 0)
        {
            break;
        }
    }
    return x;
}

template <typename DataType>
unsigned int getPivotingRowUsingMinRatioRule(AlbaMatrix<DataType> const& simplexTable, unsigned int const pivotingColumn)
{
    bool isFirst(true);
    unsigned int pivotingRow=0;
    DataType pivotingRatio{};
    unsigned int lastX(simplexTable.getNumberOfColumns()-1);
    for(unsigned int y=0; y<simplexTable.getNumberOfRows()-1; y++) // pivoting row does not include the last row (because last row contains the objective function)
    {
        if(simplexTable.getEntry(pivotingColumn, y) > 0) // consider only positive coefficient and positive value
        {
            // If there are no positive entries in the pivot column then the objective function is unbounded and there is no optimal solution.
            DataType currentRatio = simplexTable.getEntry(lastX, y)/simplexTable.getEntry(pivotingColumn, y);            if(isFirst)
            {
                pivotingRow = y;
                pivotingRatio = currentRatio;                isFirst = false;
            }
            else if(currentRatio < pivotingRatio) // ratio must be smaller
            {
                pivotingRow = y;
                pivotingRatio = currentRatio;
            }
        }
    }
    if(isFirst)
    {
        pivotingRow = simplexTable.getNumberOfRows();
    }
    return pivotingRow;
}
template <typename DataType>
void pivotAt(AlbaMatrix<DataType> & simplexTable, unsigned int const pivotingColumn, unsigned int const pivotingRow)
{    // scale all entries but pivoting row and pivoting column
    simplexTable.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {        if(x != pivotingColumn && y != pivotingRow)
        {
            DataType valueToSubtract(simplexTable.getEntry(x, pivotingRow) * simplexTable.getEntry(pivotingColumn, y) / simplexTable.getEntry(pivotingColumn, pivotingRow));
            simplexTable.setEntry(x, y, simplexTable.getEntry(x, y)-valueToSubtract);        }
    });

    // zero out pivoting column
    // -> this also sets the objective function coefficient to zero (guaranteeing forward progress)
    for(unsigned int y=0; y<simplexTable.getNumberOfRows(); y++)
    {
        if(y != pivotingRow)        {
            simplexTable.setEntry(pivotingColumn, y, 0);
        }
    }
    // scale pivoting row
    for(unsigned int x=0; x<simplexTable.getNumberOfColumns(); x++)
    {
        if(x != pivotingColumn)
        {
            simplexTable.setEntry(x, pivotingRow, simplexTable.getEntry(x, pivotingRow)/simplexTable.getEntry(pivotingColumn, pivotingRow));
        }
    }

    // set one on intersection
    simplexTable.setEntry(pivotingColumn, pivotingRow, 1);
}

//Simplex algorithm:
//-> Developed shortly after WWII in response to logistical problems including the Berlin airlift
//-> Ranked as one of the top 10 scientific algorithms of 20th century

//Generic algorithm:
//-> Start at some extreme point
//-> Pivot from one extreme point to an adjacent one
//-> Repeat until optimal

//How to implement?
//-> Linear algebra

//Basis
//-> A basis is a subset of m of the n variables.
//-> Basic feasible solution
//---> Set n-m nonbasic variables to 0, solve from remaining m variables.
//---> Solve m equations in m unknowns
//---> If unique and feasible -> BFS
//---> BFS <-> extreme point

// Simplex algorithm: running time
// Remarkable property: In typical practical applications, simplex algorithm terminates after at most 2(m+n) pivots. -> linear!
// -> Still today is somewhat mysterious
// -> Paper: "Smoothed Analysis of Algorithms: Why the Simplex Algorithm Usually takes Polynomial Time."

// Pivoting rules: Carefully balance the cost of finding an entering variable with the number of pivots needed
// -> No pivot rule is known that is guaranteed to be polynomial
// -> Mose pivot rules are known to be exponential (or worse) in worst-case.

// Simplex algorithm degeneracy
// -> Degeneracy here means that there is a new basis, but same extreme point

// Cycling: Get stuck by cycling through different bases that all correspond to same extreme point.
// -> Doesn't occur in the wild
// -> Bland's rule guarantees finite # of pivots

// Simplex algorithm: implementation issues
// To improve the bare-bones implementation:
// -> Avoid stalling -> requires artful engineering
// -> Maintain sparsity -> requires fancy data structures
// -> Numerical stability -> requires advanced math (take note floating points errors)
// -> Defect infeasibility - > run "phase I" simplex algorithm (How about we run simplex when there is no solution)
// -> Defect unboundedness - > no leaving row (there are not enough constraints)

// Best practice: Don't implement it yourself

// Basic implementations: Available in many programming environments.
// Industrial-strength solvers: Routinely solve LPs with millions of variables.
// -> IBM ILOG CPLEX, COIN|OR, MOSEK

// Modeling languages: Simplify task of modeling problem as LP
// -> AMPL, AIMMS 3

}

} // namespace alba
