#include "ProductDayProblem.hpp"

#include <limits>

using namespace std;

namespace alba
{

ProductDayProblem::ProductDayProblem(PriceMatrix const& pricesInProductByDay)
    : m_pricesInDayByProduct(pricesInProductByDay)
{
    initialize();
}

ProductDayProblem::Price ProductDayProblem::getProductAndDayPairsForMinimumPrice()
{
    // fill up first day
    for(Product product=0; product<getNumberOfProducts(); product++)
    {
        m_totalPricesInDayByProductBits.setEntry(0, getProductBits(product), m_pricesInDayByProduct.getEntry(product, 0));
    }
    // fill up remaining days
    for(Day day=1; day<getNumberOfDays(); day++)
    {
        for(ProductBits productBits=0; productBits<getNumberOfProductsSubsets(); productBits++)
        {
            m_totalPricesInDayByProductBits.setEntry(day, productBits, m_totalPricesInDayByProductBits.getEntry(productBits, day-1));
            for(Product product=0; product<getNumberOfProducts(); product++)
            {
                if(isProductIncluded(productBits, product))
                {
                    Price currentMinimum = min(
                                m_totalPricesInDayByProductBits.getEntry(day, productBits),
                                m_totalPricesInDayByProductBits.getEntry(day-1, removeProduct(productBits, product))
                                + m_pricesInDayByProduct.getEntry(day,product));
                    m_totalPricesInDayByProductBits.setEntry(productBits, day, currentMinimum);
                }
            }
        }
    }
    Price result{};
    if(m_totalPricesInDayByProductBits.isInside(getNumberOfDays()-1, getNumberOfProductsSubsets()-1))
    {
        result = m_totalPricesInDayByProductBits.getEntry(getNumberOfDays()-1, getNumberOfProductsSubsets()-1);
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
    m_totalPricesInDayByProductBits.clearAndResize(getNumberOfDays(), getNumberOfProductsSubsets(), numeric_limits<Price>::max());
}

}
