#pragma once

namespace alba
{

namespace algebra
{

class BaseSolver
{
public:
    BaseSolver();

    bool isSolved() const;
    bool isACompleteSolution() const;

protected:
    // No need for virtual destructor because this class is not destroyed polymorphically.
    // Guideline #4: A base class destructor should be either public and virtual, or protected and nonvirtual.
    // Source: http://www.gotw.ca/publications/mill18.htm
    ~BaseSolver() = default;

    void setAsCompleteSolution();
    void setAsIncompleteSolution();
private:
    bool m_isSolved;
    bool m_isACompleteSolution;};


}

}
