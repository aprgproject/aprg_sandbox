#include "ProductDayProblem.hpp"

#include <Common/Bit/AlbaBitValueUtilities.hpp>

using namespace std;
namespace alba
{

ProductDayProblem::ProductDayProblem(PriceMatrix const& pricesInDayByProduct)
    : m_pricesInDayByProduct(pricesInDayByProduct)
{}

ProductDayProblem::Price ProductDayProblem::getMinimumPriceUsingMemoizationDP() const
{
    Price result(0);
    if(!m_pricesInDayByProduct.isEmpty())
    {
        PriceMatrix minimumPrices(getNumberOfDays(), getNumberOfProductsSubsets(), static_cast<Price>(MAX_PRICE));
        for(Day day=0; day<getNumberOfDays(); day++) // set zero cost on empty product bits
        {
            minimumPrices.setEntry(day, 0, 0);
        }
        for(Product product=0; product<getNumberOfProducts(); product++) // fill up first day
        {
            minimumPrices.setEntry(0, getProductBits(product), m_pricesInDayByProduct.getEntry(0, product));
        }
        result = getMinimumPriceUsingMemoizationDP(minimumPrices, getNumberOfDays()-1, getProductBitsWithAllProducts());
    }
    return result;
}

ProductDayProblem::Price ProductDayProblem::getMinimumPriceUsingTabularDP() const
{
    // set half max to all entries (half max because theres addition so values might exceed if we use max)
    PriceMatrix minimumPrices(getNumberOfDays(), getNumberOfProductsSubsets(), static_cast<Price>(MAX_PRICE));

    for(Day day=0; day<getNumberOfDays(); day++) // set zero cost on empty product bits
    {
        minimumPrices.setEntry(day, 0, 0);
    }

    for(Product product=0; product<getNumberOfProducts(); product++) // fill up first day
    {
        minimumPrices.setEntry(0, getProductBits(product), m_pricesInDayByProduct.getEntry(0, product));
    }

    for(Day day=1; day<getNumberOfDays(); day++) // fill up remaining days using dynamic programming
    {
        // productBits representation: 0 not included, 1 is included
        for(ProductBits productBits=0; productBits<getNumberOfProductsSubsets(); productBits++)
        {
            minimumPrices.setEntry(day, productBits, minimumPrices.getEntry(day-1, productBits)); // put total of previous day
            for(Product product=0; product<getNumberOfProducts(); product++)
            {
                if(isProductIncluded(productBits, product))
                {
                    Price previousDayWithoutProduct = minimumPrices.getEntry(day-1, removeProduct(productBits, product));
                    if(MAX_PRICE != previousDayWithoutProduct)
                    {
                        Price currentMinimum = min(
                                    minimumPrices.getEntry(day, productBits), // current value
                                    previousDayWithoutProduct + m_pricesInDayByProduct.getEntry(day, product)); // plus price of the product today
                        minimumPrices.setEntry(day, productBits, currentMinimum);
                    }
                }
            }
        }
    }

    Price result{};
    if(minimumPrices.isInside(getNumberOfDays()-1, getNumberOfProductsSubsets()-1)) // best price is on the last column and row
    {
        result = minimumPrices.getEntry(getNumberOfDays()-1, getNumberOfProductsSubsets()-1);
    }
    return result;
}

ProductDayProblem::Price ProductDayProblem::getMinimumPriceUsingMemoizationDP(
        PriceMatrix & minimumPrices,
        Day const day,
        ProductBits const productBits) const
{
    if(day<getNumberOfDays())
    {
        Price result(minimumPrices.getEntry(day, productBits));
        if(MAX_PRICE == result)
        {
            result = getMinimumPriceUsingMemoizationDP(minimumPrices, day-1, productBits); // put total of previous day
            for(Product product=0; product<getNumberOfProducts(); product++)
            {
                if(isProductIncluded(productBits, product))
                {
                    Price previousDayWithoutProduct = getMinimumPriceUsingMemoizationDP(minimumPrices, day-1, removeProduct(productBits, product));
                    if(MAX_PRICE != previousDayWithoutProduct)
                    {
                        result = min(result, // current value
                                     previousDayWithoutProduct // get total of previous day without the product
                                     + m_pricesInDayByProduct.getEntry(day, product)); // plus price of the product today
                    }
                }
            }
            minimumPrices.setEntry(day, productBits, result);
        }
        return result;
    }
    else
    {
        return MAX_PRICE;
    }
}

bool ProductDayProblem::isProductIncluded(ProductBits const productBits, Product const product) const
{
    return productBits & getProductBits(product);}

ProductDayProblem::Product ProductDayProblem::getNumberOfProducts() const
{
    return m_pricesInDayByProduct.getNumberOfRows();}

ProductDayProblem::Day ProductDayProblem::getNumberOfDays() const
{
    return m_pricesInDayByProduct.getNumberOfColumns();
}

ProductDayProblem::ProductBits ProductDayProblem::getNumberOfProductsSubsets() const
{
    return 1<<getNumberOfProducts();
}

ProductDayProblem::ProductBits ProductDayProblem::getProductBitsWithAllProducts() const
{
    return AlbaBitValueUtilities<ProductBits>::generateOnesWithNumberOfBits(getNumberOfProducts());
}

ProductDayProblem::ProductBits ProductDayProblem::getProductBits(Product const product) const
{
    return 1<<product;
}

ProductDayProblem::ProductBits ProductDayProblem::addProduct(ProductBits const productBits, Product const product) const
{
    return productBits | (1 << product);
}

ProductDayProblem::ProductBits ProductDayProblem::removeProduct(ProductBits const productBits, Product const product) const
{
    return productBits & ~(1 << product);
}

}