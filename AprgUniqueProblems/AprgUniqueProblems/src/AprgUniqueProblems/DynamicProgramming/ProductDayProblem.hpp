#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <vector>

namespace alba
{

class ProductDayProblem
{
public:
    // We are given the prices of k products over n days, and we want to buy each product exactly once.
    // However, we are allowed to buy at most one product in a day. What is the minimum total price?

    using Price = unsigned int;
    using Product = unsigned int;
    using Day = unsigned int;
    using ProductBits = unsigned int;
    using PriceMatrix = matrix::AlbaMatrix<Price>;
    using ProductAndDayPair = std::pair<Product, Day>;
    using ProductAndDayPairs = std::vector<ProductAndDayPair>;

    ProductDayProblem(PriceMatrix const& pricesInProductByDay);

    Price getProductAndDayPairsForMinimumPrice();
private:
    bool isProductIncluded(ProductBits const productBits, Product const product) const;
    Product getNumberOfProducts() const;
    Day getNumberOfDays() const;
    ProductBits getNumberOfProductsSubsets() const;
    ProductBits getProductBits(Product const product) const;
    ProductBits removeProduct(ProductBits const productBits, Product const product) const;
    void initialize();
    PriceMatrix m_pricesInDayByProduct;
    PriceMatrix m_totalPricesInDayByProductBits;
};

}
