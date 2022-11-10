#include "ProductDayProblem.hpp"

#include <limits>

using namespace std;

namespace alba
{

ProductDayProblem::ProductDayProblem(PriceMatrix const& pricesInDayByProduct)
    : m_pricesInDayByProduct(pricesInDayByProduct)
{
    initialize();
}
ProductDayProblem::Price ProductDayProblem::getProductAndDayPairsForMinimumPrice()
{
    // fill up remaining days
    for(Day day=1; day<getNumberOfDays(); day++)
    {
        for(ProductBits productBits=0; productBits<getNumberOfProductsSubsets(); productBits++)
        {
            m_totalInDayByProductBits.setEntry(day, productBits, m_totalInDayByProductBits.getEntry(day-1, productBits)); // put total of previous day
            for(Product product=0; product<getNumberOfProducts(); product++)
            {
                if(isProductIncluded(productBits, product))                {
                    Price currentMinimum = min(
                                m_totalInDayByProductBits.getEntry(day, productBits), // current value
                                m_totalInDayByProductBits.getEntry(day-1, removeProduct(productBits, product)) // get total of previous day without the product
                                + m_pricesInDayByProduct.getEntry(day, product)); // plus price of the product on that day

                    m_totalInDayByProductBits.setEntry(day, productBits, currentMinimum);
                }
            }
        }    }
    Price result{};
    if(m_totalInDayByProductBits.isInside(getNumberOfDays()-1, getNumberOfProductsSubsets()-1))
    {        result = m_totalInDayByProductBits.getEntry(getNumberOfDays()-1, getNumberOfProductsSubsets()-1);
    }
    return result;
}

bool ProductDayProblem::isProductIncluded(ProductBits const productBits, Product const product) const
{
    return productBits & getProductBits(product);
}

ProductDayProblem::Product ProductDayProblem::getNumberOfProducts() const
{
    return m_pricesInDayByProduct.getNumberOfRows();
}

ProductDayProblem::Day ProductDayProblem::getNumberOfDays() const
{
    return m_pricesInDayByProduct.getNumberOfColumns();
}

ProductDayProblem::ProductBits ProductDayProblem::getNumberOfProductsSubsets() const
{
    return 1<<getNumberOfProducts();
}

ProductDayProblem::ProductBits ProductDayProblem::getProductBits(Product const product) const
{
    return 1<<product;
}

ProductDayProblem::ProductBits ProductDayProblem::removeProduct(ProductBits const productBits, Product const product) const
{
    return productBits & ~(1 << product);
}

void ProductDayProblem::initialize()
{
    // set half max to all entries (half max because theres addition so values might exceed if we use max)
    m_totalInDayByProductBits.clearAndResize(getNumberOfDays(), getNumberOfProductsSubsets(), numeric_limits<Price>::max()/2);

    // set zero cost on empty product bits
    for(Day day=0; day<getNumberOfDays(); day++)
    {
        m_totalInDayByProductBits.setEntry(day, 0, 0);
    }

    // fill up first day
    for(Product product=0; product<getNumberOfProducts(); product++)
    {
        m_totalInDayByProductBits.setEntry(0, getProductBits(product), m_pricesInDayByProduct.getEntry(0, product));
    }
}

}