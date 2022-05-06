#pragma once

#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>

#include <iostream>

namespace alba
{

namespace algorithm
{

template <unsigned int RADIX>
class RunLengthEncodingCompression
{
public :

    RunLengthEncodingCompression()
    {}

    void compress(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);        AlbaStreamBitWriter writer(output);
        char count{};
        bool b(false), old(false);
        while(!input.eof())        {
            b = reader.readBoolData();
            if(!input.eof())
            {
                if(b != old)
                {
                    writer.writeCharData(count);
                    count = 0;
                    old = !old;
                }
                else if(count == RADIX-1)
                {
                    writer.writeCharData(count);
                    count = 0;
                    writer.writeCharData(count);
                }
                count++;
            }
        }
        writer.writeCharData(count);
    }

    void expand(std::istream & input, std::ostream & output)
    {
        AlbaStreamBitReader reader(input);
        AlbaStreamBitWriter writer(output);
        bool b(false);
        while(!input.eof())
        {
            char count(reader.readCharData());
            if(!input.eof())
            {
                for(char i=0; i<count; i++)
                {
                    writer.writeBoolData(b);
                }
                b = !b;
            }
        }
    }

};

}
}
