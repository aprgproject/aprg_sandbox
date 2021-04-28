#include "AprgBitmapFilters.hpp"

#include <AprgColorUtilities.hpp>
#include <DataStatistics.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <Randomizer/AlbaRandomizer.hpp>
#include <TwoDimensions/Circle.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

using namespace alba::ColorUtilities;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba
{

AprgBitmapFilters::AprgBitmapFilters(string const& path)
    : m_backgroundColor(0xFFFFFF)
    , m_bitmap(path)
    , m_inputCanvas(m_bitmap.getSnippetReadFromFileWholeBitmap())
    , m_outputCanvas(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor))
{}

bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const //RGB algo
{
    bool isRedDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractRed(color1)-(int)extractRed(color2))>(int)similarityColorLimit);
    bool isGreenDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractGreen(color1)-(int)extractGreen(color2))>(int)similarityColorLimit);
    bool isBlueDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractBlue(color1)-(int)extractBlue(color2))>(int)similarityColorLimit);
    return  !(isRedDifferenceBeyondLimit || isGreenDifferenceBeyondLimit || isBlueDifferenceBeyondLimit);
}

/*
bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const//Pythagorean algo
{
    double colorDifferenceAcrossDifferentColors(mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>((double)getRed(color1)-(double)getRed(color2), (double)getGreen(color1)-(double)getGreen(color2), (double)getBlue(color1)-(double)getBlue(color2)));
    return colorDifferenceAcrossDifferentColors < m_similarityColorLimit;
}
*/

bool AprgBitmapFilters::isNotBackgroundColor(unsigned int const color) const
{
    return color != m_backgroundColor;
}

void AprgBitmapFilters::clearOutputCanvas()
{
    unsigned char backgroundColorByte = static_cast<unsigned char>(m_backgroundColor);
    m_outputCanvas = m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(backgroundColorByte);
}

void AprgBitmapFilters::copyInputCanvasToOutputCanvas()
{
    m_outputCanvas = m_inputCanvas;
}

void AprgBitmapFilters::copyOutputCanvasToInputCanvas()
{
    m_inputCanvas = m_outputCanvas;
}

void AprgBitmapFilters::determinePenPixels(double const penSearchRadius, unsigned int const similarityColorLimit)
{
    m_inputCanvas.traverse([&](BitmapXY const& centerXY, unsigned int const centerColor)
    {
        Circle circle(convertBitmapXYToPoint(centerXY), penSearchRadius);
        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        circle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY pointInCircle(convertPointToBitmapXY(point));
            if(m_inputCanvas.isPositionInsideTheSnippet(pointInCircle))
            {
                unsigned int const currentColor(m_inputCanvas.getColorAt(pointInCircle));
                if(isSimilar(centerColor, currentColor, similarityColorLimit))
                {
                    bitmapPointsWithSimilarColors.emplace_back(pointInCircle);
                }
                else
                {
                    bitmapPointsWithDisimilarColors.emplace_back(pointInCircle);
                }
            }
        });
        if(bitmapPointsWithSimilarColors.size() > bitmapPointsWithDisimilarColors.size())
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithDisimilarColors);
        }
        else
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithSimilarColors);
        }
    });
}

void AprgBitmapFilters::getConnectedComponentsOneComponentAtATime()
{
    unsigned int currentLabel=1;
    deque<BitmapXY> pointsInDeque;
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && currentPixelInfo.label==PixelInformation::INITIAL_LABEL_VALUE)
        {
            currentPixelInfo.label = currentLabel;
            pointsInDeque.push_front(currentPoint);
            while(!pointsInDeque.empty())
            {
                BitmapXY poppedPoint(pointsInDeque.back());
                pointsInDeque.pop_back();
                analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(pointsInDeque, poppedPoint, currentLabel);
            }
            currentLabel++;
        }
    });
}

/*void AprgBitmapFilters::getConnectedComponentsOneComponentAtATime()
{
    copyInputCanvasToOutputCanvas();
    unsigned int currentLabel=1;
    unsigned int fileNumber=1000;
    deque<BitmapXY> pointsInDeque;
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        //ALBA_PRINT2(currentPoint.getDisplayableString(), "0x"<<hex<<currentPointColor<<dec);
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && currentPixelInfo.label==PixelInformation::INITIAL_LABEL_VALUE)
        {
            //ALBA_PRINT3(currentPoint.getDisplayableString(), currentPixelInfo.label, currentLabel);
            currentPixelInfo.label = currentLabel;
            pointsInDeque.push_front(currentPoint);

            stringstream sstr;
            sstr<<"BitmapRun"<<fileNumber<<".bmp";
            setColoredPixelsForDifferentLabelsIntoOutputCanvas();
            saveOutputCanvasIntoDifferentFile(sstr.str());
            fileNumber++;
            while(!pointsInDeque.empty())
            {
                BitmapXY poppedPoint(pointsInDeque.back());
                pointsInDeque.pop_back();
                analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(pointsInDeque, poppedPoint, currentLabel);
                stringstream sstr2;
                sstr2<<"BitmapRun"<<fileNumber<<".bmp";
                setColoredPixelsForDifferentLabelsIntoOutputCanvas();
                saveOutputCanvasIntoDifferentFile(sstr2.str());
                fileNumber++;
            }
            currentLabel++;
        }
    });
}*/

void AprgBitmapFilters::getConnectedComponentsTwoPass()
{
    unsigned int currentLabel=1;
    UnionFindForLabels unionFindForLabels;
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        if(isNotBackgroundColor(currentPointColor))
        {
            PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
            unsigned int smallestNeighborLabel = analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
                        unionFindForLabels,
                        currentPoint);
            if(smallestNeighborLabel != PixelInformation::INVALID_LABEL_VALUE)
            {
                currentPixelInfo.label = smallestNeighborLabel;
            }
            else
            {
                currentPixelInfo.label = currentLabel;
                currentLabel++;
            }
        }
    });
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && currentPixelInfo.label!=PixelInformation::INITIAL_LABEL_VALUE)
        {
            unsigned int smallestLabel = unionFindForLabels.getRoot(currentPixelInfo.label);
            currentPixelInfo.label = smallestLabel;
        }
    });
}

/*
void AprgBitmapFilters::getConnectedComponentsTwoPass()
{
    copyInputCanvasToOutputCanvas();
    unsigned int fileNumber=10000;
    unsigned int currentLabel=1;
    UnionFindForLabels unionFindForLabels;
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        if(isNotBackgroundColor(currentPointColor))
        {
            PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
            unsigned int smallestNeighborLabel = analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
                        unionFindForLabels,
                        currentPoint);
            if(smallestNeighborLabel != PixelInformation::INVALID_LABEL_VALUE)
            {
                currentPixelInfo.label = smallestNeighborLabel;
            }
            else
            {
                currentPixelInfo.label = currentLabel;
                currentLabel++;
            }
            ALBA_PRINT4(currentPoint.getDisplayableString(), currentPixelInfo.label, smallestNeighborLabel, currentLabel);
            stringstream sstr;
            sstr<<"BitmapRun"<<fileNumber<<".bmp";
            setColoredPixelsForDifferentLabelsIntoOutputCanvas();
            saveOutputCanvasIntoDifferentFile(sstr.str());
            fileNumber++;
        }
    });
    stringstream sstr;
    sstr<<"BitmapRun"<<fileNumber<<".bmp";
    setColoredPixelsForDifferentLabelsIntoOutputCanvas();
    saveOutputCanvasIntoDifferentFile(sstr.str());
    fileNumber++;
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && currentPixelInfo.label!=PixelInformation::INITIAL_LABEL_VALUE)
        {
            unsigned int smallestLabel = unionFindForLabels.getRoot(currentPixelInfo.label);
            currentPixelInfo.label = smallestLabel;
            ALBA_PRINT3(currentPoint.getDisplayableString(), currentPixelInfo.label, smallestLabel);
            stringstream sstr;
            sstr<<"BitmapRun"<<fileNumber<<".bmp";
            setColoredPixelsForDifferentLabelsIntoOutputCanvas();
            saveOutputCanvasIntoDifferentFile(sstr.str());
            fileNumber++;
        }
    });
}*/

void AprgBitmapFilters::saveOutputCanvasToCurrentBitmapFile() const
{
    m_bitmap.setSnippetWriteToFile(m_outputCanvas);
}

void AprgBitmapFilters::saveOutputCanvasIntoDifferentFile(string const& filename)
{
    AlbaLocalPathHandler originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    AlbaLocalPathHandler newFilePathHandler(originalBitmapPathHandler.getDirectory()+filename);
    originalBitmapPathHandler.copyToNewFile(newFilePathHandler.getFullPath());
    AprgBitmap newBitmap(newFilePathHandler.getFullPath());
    newBitmap.setSnippetWriteToFile(m_outputCanvas);
}

void AprgBitmapFilters::setBackgroundColor(unsigned int const backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void AprgBitmapFilters::setBlankGapsUsingBlurToOutputCanvas(double const blurRadius)
{
    AprgBitmapSnippet canvas1(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor));
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        canvas1.setPixelAt(bitmapPoint, color);
    });

    unsigned int numberOfPixelsWithChangedColor(1);
    while(numberOfPixelsWithChangedColor!=0)
    {
        numberOfPixelsWithChangedColor=0;
        AprgBitmapSnippet canvas2(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor));
        canvas1.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
        {
            unsigned int newColor(color);
            if(m_backgroundColor == color)
            {
                newColor = getBlurredColor(canvas1, bitmapPoint, blurRadius, [&](unsigned int , unsigned int currentColor, BitmapXY )
                {
                    return m_backgroundColor!=currentColor;
                });
                if(m_backgroundColor != newColor)
                {
                    numberOfPixelsWithChangedColor++;
                }
            }
            canvas2.setPixelAt(bitmapPoint, newColor);
        });
        canvas1=canvas2;
    }
    m_outputCanvas=canvas1;
}

void AprgBitmapFilters::setBlurredNonPenPixelsToOutputCanvas(double const blurRadius, unsigned int const similarityColorLimit)
{
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type != PixelType::Pen)
        {
            m_outputCanvas.setPixelAt(bitmapPoint, getBlurredColor(m_inputCanvas, bitmapPoint, blurRadius,[&](unsigned int centerColor, unsigned int currentColor, BitmapXY pointInCircle)
            {
                PixelInformation pointInCirclePixelInformation(m_pixelInformationDatabase.getPixelInformation(pointInCircle));
                return isSimilar(centerColor, currentColor, similarityColorLimit) && currentColor!=m_backgroundColor && pointInCirclePixelInformation.type != PixelType::Pen;
            }));
        }
    });
}

void AprgBitmapFilters::setNonPenPixelsToOutputCanvas()
{
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type != PixelType::Pen)
        {
            m_outputCanvas.setPixelAt(bitmapPoint, color);
        }
    });
}

void AprgBitmapFilters::setPenPixelsToOutputCanvas()
{
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.type == PixelType::Pen)
        {
            m_outputCanvas.setPixelAt(bitmapPoint, color);
        }
    });
}

void AprgBitmapFilters::setColoredPixelsForDifferentLabelsIntoOutputCanvas()
{
    AlbaRandomizer randomizer;
    randomizer.resetRandomSeed();
    map<unsigned int, unsigned int> labelToColorMap;
    setLabelToColorMapForStableRun(labelToColorMap);
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        PixelInformation pixelInformation(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInformation.label != PixelInformation::INITIAL_LABEL_VALUE)
        {
            if(labelToColorMap.find(pixelInformation.label) == labelToColorMap.end())
            {
                labelToColorMap.emplace(pixelInformation.label, randomizer.getRandomValueInUniformDistribution(0, 0x00FFFFFF));
            }
            unsigned int color = labelToColorMap.at(pixelInformation.label);
            m_outputCanvas.setPixelAt(bitmapPoint, color);
        }
    });
    for(pair<unsigned int, unsigned int> const& labelAndColorPair : labelToColorMap)
    {
        unsigned int label = labelAndColorPair.first;
        unsigned int color = labelAndColorPair.second;
        //cout<<"labelToColorMap["<<label<<"]=0x"<<hex<<color<<";"<<dec<<endl;
    }
}

void AprgBitmapFilters::gatherAndSaveColorDataAndStatistics()
{
    AlbaLocalPathHandler bitmapPathHandler(m_bitmap.getConfiguration().getPath());
    AlbaLocalPathHandler colorDataFileHandler(bitmapPathHandler.getDirectory() + R"(\)" + bitmapPathHandler.getFilenameOnly() + R"(_SortedColorData.csv)");
    AlbaLocalPathHandler statisticsFileHandler(bitmapPathHandler.getDirectory() + R"(\)" + bitmapPathHandler.getFilenameOnly() + R"(_Statistics.txt)");
    ofstream colorDataFileStream(colorDataFileHandler.getFullPath());
    ofstream statisticsFileStream(statisticsFileHandler.getFullPath());
    multiset<double> colorIntensitySet;
    multiset<double> luma601Set;
    multiset<double> luma709Set;
    multiset<double> hueDegreesSet;
    multiset<double> saturationLightnessSet;
    multiset<double> lightnessSet;
    multiset<double> saturationValueSet;
    multiset<double> valueSet;

    using OneDimensionStatistics = DataStatistics<1>;
    OneDimensionStatistics::Samples colorIntensitySamples;
    OneDimensionStatistics::Samples saturationLightnessSamples;
    OneDimensionStatistics::Samples lightnessSamples;
    OneDimensionStatistics::Samples saturationValueSamples;
    OneDimensionStatistics::Samples valueSamples;
    OneDimensionStatistics::Samples luma601Samples;
    OneDimensionStatistics::Samples luma709Samples;

    unsigned int count=0;
    m_inputCanvas.traverse([&](BitmapXY const&, unsigned int const color)
    {
        double colorIntensity(calculateColorIntensityDecimal(color));
        double luma601(calculateLuma601Decimal(color));
        double luma709(calculateLuma709Decimal(color));
        colorIntensitySet.emplace(colorIntensity);
        luma601Set.emplace(luma601);
        luma709Set.emplace(luma709);
        HueSaturationLightnessData hslData(convertColorToHueSaturationLightnessData(color));
        HueSaturationValueData hsvData(convertColorToHueSaturationValueData(color));
        hueDegreesSet.emplace(hslData.hueDegrees);
        saturationLightnessSet.emplace(hslData.saturationLightnessDecimal);
        lightnessSet.emplace(hslData.lightnessDecimal);
        saturationValueSet.emplace(hsvData.saturationValueDecimal);
        valueSet.emplace(hsvData.valueDecimalOfColorMax);

        colorIntensitySamples.emplace_back(OneDimensionStatistics::Sample{colorIntensity});
        saturationLightnessSamples.emplace_back(OneDimensionStatistics::Sample{hslData.saturationLightnessDecimal});
        lightnessSamples.emplace_back(OneDimensionStatistics::Sample{hslData.lightnessDecimal});
        saturationValueSamples.emplace_back(OneDimensionStatistics::Sample{hsvData.saturationValueDecimal});
        valueSamples.emplace_back(OneDimensionStatistics::Sample{hsvData.valueDecimalOfColorMax});
        luma601Samples.emplace_back(OneDimensionStatistics::Sample{luma601});
        luma709Samples.emplace_back(OneDimensionStatistics::Sample{luma709});
    });

    unsigned int size(colorIntensitySet.size());
    multiset<double>::const_iterator colorIntensityIterator(colorIntensitySet.cbegin());
    multiset<double>::const_iterator hueDegreesIterator(hueDegreesSet.cbegin());
    multiset<double>::const_iterator saturationLightnessIterator(saturationLightnessSet.cbegin());
    multiset<double>::const_iterator lightnessIterator(lightnessSet.cbegin());
    multiset<double>::const_iterator saturationValueIterator(saturationValueSet.cbegin());
    multiset<double>::const_iterator valueIterator(valueSet.cbegin());
    multiset<double>::const_iterator luma601Iterator(luma601Set.cbegin());
    multiset<double>::const_iterator luma709Iterator(luma709Set.cbegin());

    colorDataFileStream
            << "colorIntensity, "
            << "saturationLightness, "
            << "lightness, "
            << "saturationValueI, "
            << "value, "
            << "luma601, "
            << "luma709" << endl;
    count=0;
    while(count<size)
    {
        colorDataFileStream
                << *colorIntensityIterator << ", " ", "
                << *saturationLightnessIterator << ", "
                << *lightnessIterator << ", "
                << *saturationValueIterator << ", "
                << *valueIterator << ", "
                << *luma601Iterator << ", "
                << *luma709Iterator << endl;
        colorIntensityIterator++;
        hueDegreesIterator++;
        saturationLightnessIterator++;
        lightnessIterator++;
        saturationValueIterator++;
        valueIterator++;
        luma601Iterator++;
        luma709Iterator++;
        count++;
    }

    OneDimensionStatistics colorIntensityStatistics(colorIntensitySamples);
    OneDimensionStatistics saturationLightnessStatistics(saturationLightnessSamples);
    OneDimensionStatistics lightnessStatistics(lightnessSamples);
    OneDimensionStatistics saturationValueStatistics(saturationValueSamples);
    OneDimensionStatistics valueStatistics(valueSamples);
    OneDimensionStatistics luma601Statistics(luma601Samples);
    OneDimensionStatistics luma709Statistics(luma709Samples);

    statisticsFileStream << "Color Intensity Mean: " << colorIntensityStatistics.getMean().getDisplayableString()
                         << " StdDev: " << colorIntensityStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Saturation Lightness Mean: " << saturationLightnessStatistics.getMean().getDisplayableString()
                         << " StdDev: " << saturationLightnessStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Lightness Mean: " << lightnessStatistics.getMean().getDisplayableString()
                         << " StdDev: " << lightnessStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Saturation Value Mean: " << saturationValueStatistics.getMean().getDisplayableString()
                         << " StdDev: " << saturationValueStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Value Mean: " << valueStatistics.getMean().getDisplayableString()
                         << " StdDev: " << valueStatistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Luma 601 Mean: " << luma601Statistics.getMean().getDisplayableString()
                         << " StdDev: " << luma601Statistics.getSampleStandardDeviation().getDisplayableString() << endl;
    statisticsFileStream << "Luma 709 Mean: " << luma709Statistics.getMean().getDisplayableString()
                         << " StdDev: " << luma709Statistics.getSampleStandardDeviation().getDisplayableString() << endl;
}

void AprgBitmapFilters::convertToAnimeColor(string const& fileName)
{
    //isLightnessLikeAnAnime -> mean should be 0.40-0.60, and std dev should be greater than 0.20

    map<double, unsigned int> lightnessToCount;

    unsigned int count=0;
    m_inputCanvas.traverse([&](BitmapXY const&, unsigned int const color)
    {
        HueSaturationLightnessData hslData(convertColorToHueSaturationLightnessData(color));
        lightnessToCount.emplace(hslData.lightnessDecimal, 0);
        lightnessToCount[hslData.lightnessDecimal]++;
        count++;
    });

    map<double, double> lightnessToNewLightness;
    unsigned int partialCount(0);
    for(pair<double, unsigned int> lightnessToCountPair : lightnessToCount)
    {
        unsigned int currentWeight = partialCount+(lightnessToCountPair.second/2);
        lightnessToNewLightness[lightnessToCountPair.first] = (double)currentWeight/count;
        partialCount += lightnessToCountPair.second;
    }

    copyInputCanvasToOutputCanvas();
    m_inputCanvas.traverse([&](BitmapXY const& position, unsigned int const color)
    {
        HueSaturationLightnessData hslData(convertColorToHueSaturationLightnessData(color));
        map<double, double>::iterator itLightness = lightnessToNewLightness.lower_bound(hslData.lightnessDecimal);
        if(itLightness != lightnessToNewLightness.end())
        {
            hslData.lightnessDecimal = itLightness->second;
            m_outputCanvas.setPixelAt(position, convertHueSaturationLightnessDataToColor(hslData));
        }
    });

    saveOutputCanvasIntoDifferentFile(fileName);
}

unsigned int AprgBitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
        UnionFindForLabels & unionFindForLabels,
        BitmapXY const & neighborPoint)
{
    //4-connectivity
    unsigned int smallestLabel = PixelInformation::INVALID_LABEL_VALUE;
    BitmapXY neighbor1(neighborPoint.getX()-1, neighborPoint.getY());
    BitmapXY neighbor2(neighborPoint.getX(), neighborPoint.getY()-1);
    unsigned int neighbor1Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(neighbor1);
    unsigned int neighbor2Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(neighbor2);
    smallestLabel = min(smallestLabel, neighbor1Label);
    smallestLabel = min(smallestLabel, neighbor2Label);
    updateUnionFindForLabels(unionFindForLabels, smallestLabel, neighbor1Label, neighbor2Label);
    return smallestLabel;
}

unsigned int AprgBitmapFilters::analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
        BitmapXY const & neighborPoint)
{
    unsigned int labelResult = PixelInformation::INVALID_LABEL_VALUE;
    if(m_inputCanvas.isPositionInsideTheSnippet(neighborPoint))
    {
        unsigned int neighborPointColor = m_inputCanvas.getColorAt(neighborPoint);
        PixelInformation & neighborPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(neighborPoint));
        if(isNotBackgroundColor(neighborPointColor) && neighborPixelInfo.label!=PixelInformation::INITIAL_LABEL_VALUE)
        {
            labelResult = neighborPixelInfo.label;
        }
    }
    return labelResult;
}

void AprgBitmapFilters::updateUnionFindForLabels(
        UnionFindForLabels& unionFindForLabels,
        unsigned int const smallestLabel,
        unsigned int const neighbor1Label,
        unsigned int const neighbor2Label) const
{
    if(smallestLabel != PixelInformation::INVALID_LABEL_VALUE && neighbor1Label != PixelInformation::INVALID_LABEL_VALUE)
    {
        unionFindForLabels.connect(smallestLabel, neighbor1Label);
    }
    if(smallestLabel != PixelInformation::INVALID_LABEL_VALUE && neighbor2Label != PixelInformation::INVALID_LABEL_VALUE)
    {
        unionFindForLabels.connect(smallestLabel, neighbor2Label);
    }
}

void AprgBitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
        deque<BitmapXY> & pointsInDeque,
        BitmapXY const & poppedPoint,
        unsigned int const currentLabel)
{
    //4-connectivity
    BitmapXY neighbor1(poppedPoint.getX()-1, poppedPoint.getY());
    BitmapXY neighbor2(poppedPoint.getX(), poppedPoint.getY()-1);
    BitmapXY neighbor3(poppedPoint.getX()+1, poppedPoint.getY());
    BitmapXY neighbor4(poppedPoint.getX(), poppedPoint.getY()+1);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor1, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor2, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor3, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor4, currentLabel);
}

void AprgBitmapFilters::analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
        deque<BitmapXY> & pointsInDeque,
        BitmapXY const & neighborPoint,
        unsigned int const currentLabel)
{
    if(m_inputCanvas.isPositionInsideTheSnippet(neighborPoint))
    {
        unsigned int neighborPointColor = m_inputCanvas.getColorAt(neighborPoint);
        PixelInformation & neighborPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(neighborPoint));
        if(isNotBackgroundColor(neighborPointColor) && neighborPixelInfo.label==PixelInformation::INITIAL_LABEL_VALUE)
        {
            neighborPixelInfo.label = currentLabel;
            pointsInDeque.push_front(neighborPoint);
        }
    }
}

Point AprgBitmapFilters::convertBitmapXYToPoint(BitmapXY const& bitmapPosition) const
{
    return Point(bitmapPosition.getX(), bitmapPosition.getY());
}

BitmapXY AprgBitmapFilters::convertPointToBitmapXY(Point const& pointPosition) const
{
    return BitmapXY(round(pointPosition.getX()), round(pointPosition.getY()));
}

unsigned int AprgBitmapFilters::getBlurredColor(AprgBitmapSnippet const& canvas, BitmapXY const& centerXY, double const blurRadius, BlurCondition const& isIncludedInBlur) const
{
    unsigned int const centerColor(canvas.getColorAt(centerXY));
    double totalBlurredColorRed(0);
    double totalBlurredColorGreen(0);
    double totalBlurredColorBlue(0);
    double totalBlurWeight(0);
    bool isChanged(false);
    Circle circle(convertBitmapXYToPoint(centerXY), blurRadius);
    circle.traverseArea(1, [&](Point const& point)
    {
        BitmapXY pointInCircle(convertPointToBitmapXY(point));
        if(canvas.isPositionInsideTheSnippet(pointInCircle))
        {
            unsigned int const currentColor(canvas.getColorAt(pointInCircle));
            if(isIncludedInBlur(centerColor, currentColor, pointInCircle))
            {
                isChanged=true;
                double distanceFromCenter(twoDimensionsHelper::getDistance(convertBitmapXYToPoint(centerXY), convertBitmapXYToPoint(pointInCircle)));
                double blurWeight(getBlurWeight(distanceFromCenter, blurRadius));
                totalBlurredColorRed+=blurWeight*extractRed(currentColor);
                totalBlurredColorGreen+=blurWeight*extractGreen(currentColor);
                totalBlurredColorBlue+=blurWeight*extractBlue(currentColor);
                totalBlurWeight+=blurWeight;
            }
        }
    });
    unsigned int blurredColor(m_backgroundColor);
    if(isChanged)
    {
        blurredColor = combineRgbToColor(
                    static_cast<unsigned char>(totalBlurredColorRed/totalBlurWeight),
                    static_cast<unsigned char>(totalBlurredColorGreen/totalBlurWeight),
                    static_cast<unsigned char>(totalBlurredColorBlue/totalBlurWeight));
    }
    return blurredColor;
}

double AprgBitmapFilters::getBlurWeight(double const distanceFromCenter, double const blurRadius) const
{
    return (blurRadius-distanceFromCenter+1)/(blurRadius+1);
}

void AprgBitmapFilters::setLabelToColorMapForStableRun(map<unsigned int, unsigned int> & labelToColorMap) const
{
    labelToColorMap[1]=0xff;
    labelToColorMap[2]=0xff00;
    labelToColorMap[3]=0xff0000;
    labelToColorMap[4]=0xffff;
    labelToColorMap[5]=0xffff00;
    labelToColorMap[6]=0x9c2e00;
    labelToColorMap[7]=0xca6600;
    labelToColorMap[8]=0x346400;
    labelToColorMap[9]=0xf23d4d;
    labelToColorMap[10]=0xd983ab;
    labelToColorMap[11]=0xe43400;
    labelToColorMap[12]=0x967200;
    labelToColorMap[13]=0xfb4400;
    labelToColorMap[14]=0x78c090;
    labelToColorMap[15]=0xaa6200;
    labelToColorMap[16]=0x834000;
    labelToColorMap[17]=0xeb6200;
    labelToColorMap[18]=0xb61e00;
    labelToColorMap[19]=0x3a6200;
    labelToColorMap[20]=0xb68a00;
    labelToColorMap[21]=0x841e00;
    labelToColorMap[22]=0xbea200;
    labelToColorMap[23]=0x693a00;
    labelToColorMap[24]=0xf6c080;
    labelToColorMap[25]=0x8dc200;
    labelToColorMap[26]=0x175600;
    labelToColorMap[27]=0xe6ba00;
    labelToColorMap[28]=0x468c00;
    labelToColorMap[29]=0x5fc070;
    labelToColorMap[30]=0xd05055;
    labelToColorMap[31]=0xe75000;
    labelToColorMap[32]=0x10c200;
    labelToColorMap[33]=0x57ee00;
    labelToColorMap[34]=0x8b5000;
    labelToColorMap[35]=0x5c5000;
    labelToColorMap[36]=0x963800;
    labelToColorMap[37]=0x96aa00;
    labelToColorMap[38]=0xec3c00;
    labelToColorMap[39]=0x42b200;
    labelToColorMap[40]=0xa62000;
    labelToColorMap[41]=0x824200;
    labelToColorMap[42]=0xa9f800;
    labelToColorMap[43]=0x106600;
    labelToColorMap[44]=0x8ed200;
    labelToColorMap[45]=0x9f5400;
    labelToColorMap[46]=0x67d800;
    labelToColorMap[47]=0xc81000;
    labelToColorMap[48]=0x274050;
    labelToColorMap[49]=0x290400;
    labelToColorMap[50]=0xff8200;
    labelToColorMap[51]=0xbb5e00;
    labelToColorMap[52]=0xf02800;
    labelToColorMap[53]=0x259400;
    labelToColorMap[54]=0x635a00;
    labelToColorMap[55]=0x83c400;
    labelToColorMap[56]=0xb9ac00;
    labelToColorMap[57]=0x655e00;
    labelToColorMap[58]=0xc16800;
    labelToColorMap[59]=0x39ca00;
    labelToColorMap[60]=0xad8c00;
    labelToColorMap[61]=0xb46a00;
    labelToColorMap[62]=0xec0060;
    labelToColorMap[63]=0x72d000;
    labelToColorMap[64]=0x2dc200;
    labelToColorMap[65]=0x668040;
    labelToColorMap[66]=0xa36e00;
    labelToColorMap[67]=0xd5e050;
}

}
