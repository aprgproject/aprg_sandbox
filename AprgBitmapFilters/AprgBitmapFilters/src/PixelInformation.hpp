#pragma once

namespace alba
{

class PixelInformation
{
public:
    static constexpr unsigned int INITIAL_LABEL_VALUE=0;
    static constexpr unsigned int INVALID_LABEL_VALUE=0x1FFFFFFF;

    PixelInformation();
    bool isPenPixel() const;
    bool isInitialLabel() const;
    bool isInvalidLabel() const;
    bool isInitialOrInvalidLabel() const;
    unsigned int getLabel() const;

    void setAsPenPoint(bool const isPenPixel);
    void setLabel(unsigned int const label);

private:
    bool m_isPenPixel;
    unsigned int m_label;
};

}
