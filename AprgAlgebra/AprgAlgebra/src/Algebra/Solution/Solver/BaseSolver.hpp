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
    void setAsCompleteSolution();
    void setAsIncompleteSolution();

private:
    bool m_isSolved;
    bool m_isACompleteSolution;
};


}

}
