#include "AprgAudio.hpp"

#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;

namespace alba
{

namespace AprgAudio
{

// Pre-defined 10-byte representations of common sample rates

unordered_map <unsigned int, vector<unsigned char>> aiffSampleRateTable = {    {8000, {64, 11, 250, 0, 0, 0, 0, 0, 0, 0}},
    {11025, {64, 12, 172, 68, 0, 0, 0, 0, 0, 0}},
    {16000, {64, 12, 250, 0, 0, 0, 0, 0, 0, 0}},
    {22050, {64, 13, 172, 68, 0, 0, 0, 0, 0, 0}},    {32000, {64, 13, 250, 0, 0, 0, 0, 0, 0, 0}},
    {37800, {64, 14, 147, 168, 0, 0, 0, 0, 0, 0}},
    {44056, {64, 14, 172, 24, 0, 0, 0, 0, 0, 0}},
    {44100, {64, 14, 172, 68, 0, 0, 0, 0, 0, 0}},
    {47250, {64, 14, 184, 146, 0, 0, 0, 0, 0, 0}},
    {48000, {64, 14, 187, 128, 0, 0, 0, 0, 0, 0}},
    {50000, {64, 14, 195, 80, 0, 0, 0, 0, 0, 0}},
    {50400, {64, 14, 196, 224, 0, 0, 0, 0, 0, 0}},
    {88200, {64, 15, 172, 68, 0, 0, 0, 0, 0, 0}},
    {96000, {64, 15, 187, 128, 0, 0, 0, 0, 0, 0}},
    {176400, {64, 16, 172, 68, 0, 0, 0, 0, 0, 0}},
    {192000, {64, 16, 187, 128, 0, 0, 0, 0, 0, 0}},
    {352800, {64, 17, 172, 68, 0, 0, 0, 0, 0, 0}},
    {2822400, {64, 20, 172, 68, 0, 0, 0, 0, 0, 0}},
    {5644800, {64, 21, 172, 68, 0, 0, 0, 0, 0, 0}}
};

template <class T>
AprgAudio<T>::AprgAudio()
{
    bitDepth = 16;
    sampleRate = 44100;
    samples.resize(1);
    samples[0].resize(0);
    audioFileFormat = AprgAudioFormat::NotLoaded;
}
template <class T>
unsigned int AprgAudio<T>::getSampleRate() const
{    return sampleRate;
}

template <class T>
unsigned int AprgAudio<T>::getNumChannels() const
{
    return samples.size();
}

template <class T>bool AprgAudio<T>::isMono() const
{
    return getNumChannels() == 1;
}
template <class T>
bool AprgAudio<T>::isStereo() const
{
    return getNumChannels() == 2;
}

template <class T>
int AprgAudio<T>::getBitDepth() const
{
    return bitDepth;
}

template <class T>
unsigned int AprgAudio<T>::getNumSamplesPerChannel() const
{
    if (!samples.empty())
    {
        return samples[0].size();
    }
    else
    {
        return 0;
    }
}

template <class T>
T* AprgAudio<T>::getSamplePointerAtChannel(unsigned int const channelIndex)
{
    T* result=nullptr;
    if(channelIndex<samples.size())    {
        result=&(samples[channelIndex].front());
    }
    return result;}

template <class T>
double AprgAudio<T>::getLengthInSeconds() const
{
    return (double)getNumSamplesPerChannel() / (double)sampleRate;
}

template <class T>
void AprgAudio<T>::printSummary() const
{
    cout << "|======================================|" << endl;
    cout << "Num Channels: " << getNumChannels() << endl;
    cout << "Num Samples Per Channel: " << getNumSamplesPerChannel() << endl;
    cout << "Sample Rate: " << sampleRate << endl;
    cout << "Bit Depth: " << bitDepth << endl;
    cout << "Length in Seconds: " << getLengthInSeconds() << endl;
    cout << "|======================================|" << endl;
}

template <class T>
bool AprgAudio<T>::setAudioBuffer (AudioBuffer& newBuffer)
{
    int numChannels = (int)newBuffer.size();

    if (numChannels <= 0)
    {
        assert (false && "The buffer your are trying to use has no channels");
        return false;
    }

    unsigned int numSamples = newBuffer[0].size();

    // set the number of channels
    samples.resize(newBuffer.size());

    for (unsigned int k = 0; k < getNumChannels(); k++)
    {
        assert (newBuffer[k].size() == numSamples);

        samples[k].resize(numSamples);

        for (unsigned int i = 0; i < numSamples; i++)
        {
            samples[k][i] = newBuffer[k][i];
        }    }

    return true;
}

template <class T>
void AprgAudio<T>::setAudioBufferSize (unsigned int numChannels, unsigned int numSamples)
{
    samples.resize(numChannels);
    setNumSamplesPerChannel(numSamples);
}

template <class T>
void AprgAudio<T>::setNumSamplesPerChannel (unsigned int numSamples)
{
    unsigned int originalSize = getNumSamplesPerChannel();

    for (unsigned int i = 0; i < getNumChannels();i++)
    {
        samples[i].resize(numSamples);

        // set any new samples to zero
        if (numSamples > originalSize)
            fill (samples[i].begin() + originalSize, samples[i].end(), (T)0);
    }
}
template <class T>
void AprgAudio<T>::setNumChannels (int numChannels)
{
    int originalNumChannels = static_cast<int>(getNumChannels());
    int originalNumSamplesPerChannel = static_cast<int>(getNumSamplesPerChannel());

    samples.resize(numChannels);

    // make sure any new channels are set to the right size
    // and filled with zeros    if (numChannels > originalNumChannels)
    {
        for (int i = originalNumChannels; i < numChannels; i++)
        {
            samples[i].resize(originalNumSamplesPerChannel);
            fill (samples[i].begin(), samples[i].end(), (T)0.);
        }
    }}

template <class T>
void AprgAudio<T>::setBitDepth (int numBitsPerSample){
    bitDepth = numBitsPerSample;
}

template <class T>
void AprgAudio<T>::setSampleRate (unsigned int newSampleRate)
{
    sampleRate = newSampleRate;
}

template <class T>
bool AprgAudio<T>::load (string const& filePath)
{
    ifstream file (filePath, ios::binary);

    // check the file exists
    if (! file.good())
    {
        cout << "ERROR: File doesn't exist or otherwise can't load file" << endl;
        cout << filePath << endl;
        return false;
    }

    file.unsetf (ios::skipws);
    istream_iterator<unsigned char> begin (file), end;
    vector<unsigned char> fileData (begin, end);

    // get audio file format
    audioFileFormat = determineAprgAudioFormat (fileData);

    if (audioFileFormat == AprgAudioFormat::Wave)
    {
        return decodeWaveFile (fileData);
    }
    else if (audioFileFormat == AprgAudioFormat::Aiff)
    {
        return decodeAiffFile (fileData);
    }
    else
    {
        cout << "Audio File Type: " << "Error" << endl;
        return false;
    }
}

template <class T>
bool AprgAudio<T>::decodeWaveFile (vector<unsigned char>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    string headerChunkID (fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4) + 8;
    string format (fileData.begin() + 8, fileData.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfDataChunk = getIndexOfString (fileData, "data");
    int indexOfFormatChunk = getIndexOfString (fileData, "fmt");

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfDataChunk == -1 || indexOfFormatChunk == -1 || headerChunkID != "RIFF" || format != "WAVE")
    {
        cout << "ERROR: this doesn't seem to be a valid .WAV file" << endl;
        return false;
    }

    // -----------------------------------------------------------
    // FORMAT CHUNK
    int f = indexOfFormatChunk;
    string formatChunkID (fileData.begin() + f, fileData.begin() + f + 4);
    //int32_t formatChunkSize = fourBytesToInt (fileData, f + 4);
    int16_t audioFormat = twoBytesToInt (fileData, f + 8);
    int16_t numChannels = twoBytesToInt (fileData, f + 10);
    sampleRate = (unsigned int) fourBytesToInt (fileData, f + 12);
    int32_t numBytesPerSecond = fourBytesToInt (fileData, f + 16);
    int16_t numBytesPerBlock = twoBytesToInt (fileData, f + 20);
    bitDepth = (int) twoBytesToInt (fileData, f + 22);

    int numBytesPerSample = bitDepth / 8;

    // check that the audio format is PCM
    if (audioFormat != 1)
    {
        cout << "ERROR: this is a compressed .WAV file and this library does not support decoding them at present" << endl;
        return false;
    }

    // check the number of channels is mono or stereo
    if (numChannels < 1 ||numChannels > 2)
    {
        cout << "ERROR: this WAV file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)" << endl;
        return false;
    }

    // check header data is consistent
    if ((numBytesPerSecond != numChannels * sampleRate * bitDepth) / 8
            || (numBytesPerBlock != (numChannels * numBytesPerSample)))
    {
        cout << "ERROR: the header data in this WAV file seems to be inconsistent" << endl;
        return false;
    }

    // check bit depth is either 8, 16 or 24 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24)
    {
        cout << "ERROR: this file has a bit depth that is not 8, 16 or 24 bits" << endl;
        return false;
    }

    // -----------------------------------------------------------
    // DATA CHUNK
    int d = indexOfDataChunk;
    string dataChunkID (fileData.begin() + d, fileData.begin() + d + 4);
    int32_t dataChunkSize = fourBytesToInt (fileData, d + 4);

    int numSamples = dataChunkSize / (numChannels * bitDepth / 8);
    int samplesStartIndex = indexOfDataChunk + 8;

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamples; i++)
    {        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerBlock * i) + channel * numBytesPerSample;
            if (bitDepth == 8)
            {
                T sample = singleByteToSample (fileData[sampleIndex]);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex);
                T sample = sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex + 2] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex];

                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                T sample = (T)sampleAsInt / (T)8388608.;
                samples[channel].push_back (sample);
            }
            else
            {
                assert (false);
            }
        }
    }

    return true;
}

template <class T>
bool AprgAudio<T>::decodeAiffFile (vector<unsigned char>& fileData)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    string headerChunkID (fileData.begin(), fileData.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileData, 4, Endianness::BigEndian) + 8;
    string format (fileData.begin() + 8, fileData.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfCommChunk = getIndexOfString (fileData, "COMM");
    int indexOfSoundDataChunk = getIndexOfString (fileData, "SSND");

    // if we can't find the data or format chunks, or the IDs/formats don't seem to be as expected
    // then it is unlikely we'll able to read this file, so abort
    if (indexOfSoundDataChunk == -1 || indexOfCommChunk == -1 || headerChunkID != "FORM" || format != "AIFF")
    {
        cout << "ERROR: this doesn't seem to be a valid AIFF file" << endl;
        return false;
    }

    // -----------------------------------------------------------
    // COMM CHUNK
    int p = indexOfCommChunk;
    string commChunkID (fileData.begin() + p, fileData.begin() + p + 4);
    //int32_t commChunkSize = fourBytesToInt (fileData, p + 4, Endianness::BigEndian);
    int16_t numChannels = twoBytesToInt (fileData, p + 8, Endianness::BigEndian);
    int32_t numSamplesPerChannel = fourBytesToInt (fileData, p + 10, Endianness::BigEndian);
    bitDepth = (int) twoBytesToInt (fileData, p + 14, Endianness::BigEndian);
    sampleRate = getAiffSampleRate (fileData, p + 16);

    // check the sample rate was properly decoded
    if (sampleRate == -1)
    {
        cout << "ERROR: this AIFF file has an unsupported sample rate" << endl;
        return false;
    }

    // check the number of channels is mono or stereo
    if (numChannels < 1 ||numChannels > 2)
    {
        cout << "ERROR: this AIFF file seems to be neither mono nor stereo (perhaps multi-track, or corrupted?)" << endl;
        return false;
    }

    // check bit depth is either 8, 16 or 24 bit
    if (bitDepth != 8 && bitDepth != 16 && bitDepth != 24)
    {
        cout << "ERROR: this file has a bit depth that is not 8, 16 or 24 bits" << endl;
        return false;
    }

    // -----------------------------------------------------------
    // SSND CHUNK
    int s = indexOfSoundDataChunk;
    string soundDataChunkID (fileData.begin() + s, fileData.begin() + s + 4);
    int32_t soundDataChunkSize = fourBytesToInt (fileData, s + 4, Endianness::BigEndian);
    int32_t offset = fourBytesToInt (fileData, s + 8, Endianness::BigEndian);
    //int32_t blockSize = fourBytesToInt (fileData, s + 12, Endianness::BigEndian);

    int numBytesPerSample = bitDepth / 8;
    int numBytesPerFrame = numBytesPerSample * numChannels;
    int totalNumAudioSampleBytes = numSamplesPerChannel * numBytesPerFrame;
    int samplesStartIndex = s + 16 + (int)offset;

    // sanity check the data
    if ((soundDataChunkSize - 8) != totalNumAudioSampleBytes || totalNumAudioSampleBytes
            > static_cast<int>(fileData.size() - samplesStartIndex))
    {
        cout << "ERROR: the metadatafor this file doesn't seem right" << endl;
        return false;
    }

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamplesPerChannel; i++)
    {        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerFrame * i) + channel * numBytesPerSample;
            if (bitDepth == 8)
            {
                int8_t sampleAsSigned8Bit = (int8_t)fileData[sampleIndex];
                T sample = (T)sampleAsSigned8Bit / (T)128.;
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileData, sampleIndex, Endianness::BigEndian);
                T sample = sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileData[sampleIndex] << 16) | (fileData[sampleIndex + 1] << 8) | fileData[sampleIndex + 2];

                if (sampleAsInt & 0x800000) //  if the 24th bit is set, this is a negative number in 24-bit world
                    sampleAsInt = sampleAsInt | ~0xFFFFFF; // so make sure sign is extended to the 32 bit float

                T sample = (T)sampleAsInt / (T)8388608.;
                samples[channel].push_back (sample);
            }
            else
            {
                assert (false);
            }
        }
    }

    return true;
}

template <class T>
unsigned int AprgAudio<T>::getAiffSampleRate (vector<unsigned char>& fileData, int sampleRateStartIndex)
{
    for (auto it : aiffSampleRateTable)
    {
        if (tenByteMatch (fileData, sampleRateStartIndex, it.second, 0))
            return it.first;
    }

    return -1;
}

template <class T>
bool AprgAudio<T>::tenByteMatch (vector<unsigned char>& v1, int startIndex1, vector<unsigned char>& v2, int startIndex2)
{
    for (int i = 0; i < 10; i++)
    {
        if (v1[startIndex1 + i] != v2[startIndex2 + i])
            return false;
    }

    return true;
}

template <class T>
void AprgAudio<T>::addSampleRateToAiffData (vector<unsigned char>& fileData, unsigned int sampleRate)
{
    if (aiffSampleRateTable.count (sampleRate) > 0)
    {
        for (int i = 0; i < 10; i++)
            fileData.push_back (aiffSampleRateTable[sampleRate][i]);
    }
}

template <class T>
bool AprgAudio<T>::save (string const& filePath, AprgAudioFormat format)
{
    if (format == AprgAudioFormat::Wave)
    {
        return saveToWaveFile (filePath);
    }
    else if (format == AprgAudioFormat::Aiff)
    {
        return saveToAiffFile (filePath);
    }

    return false;
}

template <class T>
bool AprgAudio<T>::saveToWaveFile (string const& filePath)
{
    vector<unsigned char> fileData;

    int32_t dataChunkSize = static_cast<int32_t>(getNumSamplesPerChannel() * (getNumChannels() * bitDepth / 8));

    // -----------------------------------------------------------
    // HEADER CHUNK    addStringToFileData (fileData, "RIFF");

    // The file size in bytes is the header chunk size (4, not counting RIFF and WAVE) + the format
    // chunk size (24) + the metadata part of the data chunk plus the actual data chunk size    int32_t fileSizeInBytes = 4 + 24 + 8 + dataChunkSize;
    addInt32ToFileData (fileData, fileSizeInBytes);

    addStringToFileData (fileData, "WAVE");

    // -----------------------------------------------------------
    // FORMAT CHUNK
    addStringToFileData (fileData, "fmt ");
    addInt32ToFileData (fileData, 16); // format chunk size (16 for PCM)
    addInt16ToFileData (fileData, 1); // audio format = 1
    addInt16ToFileData (fileData, static_cast<int16_t>(getNumChannels())); // num channels
    addInt32ToFileData (fileData, (int32_t)sampleRate); // sample rate

    int32_t numBytesPerSecond = static_cast<int32_t>((getNumChannels() * sampleRate * bitDepth) / 8);
    addInt32ToFileData (fileData, numBytesPerSecond);

    int16_t numBytesPerBlock = static_cast<int16_t>(getNumChannels() * (bitDepth / 8));
    addInt16ToFileData (fileData, numBytesPerBlock);

    addInt16ToFileData (fileData, (int16_t)bitDepth);
    // -----------------------------------------------------------
    // DATA CHUNK
    addStringToFileData (fileData, "data");
    addInt32ToFileData (fileData, dataChunkSize);

    for (unsigned int i = 0; i < getNumSamplesPerChannel(); i++)
    {
        for (unsigned int channel = 0; channel < getNumChannels(); channel++)
        {
            if (bitDepth == 8)
            {                unsigned char byte = sampleToSingleByte (samples[channel][i]);
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)            {
                int16_t sampleAsInt = sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData (fileData, sampleAsInt);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = (int32_t) (samples[channel][i] * (T)8388608.);

                unsigned char bytes[3];
                bytes[2] = (unsigned char) (sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = (unsigned char) (sampleAsIntAgain >>  8) & 0xFF;
                bytes[0] = (unsigned char) sampleAsIntAgain & 0xFF;

                fileData.push_back (bytes[0]);
                fileData.push_back (bytes[1]);
                fileData.push_back (bytes[2]);
            }
            else
            {
                assert (false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(fileData.size() - 8)
            || dataChunkSize != static_cast<int32_t>(getNumSamplesPerChannel() * getNumChannels() * (bitDepth / 8)))
    {
        cout << "ERROR: couldn't save file to " << filePath << endl;
        return false;    }

    // try to write the file
    return writeDataToFile (fileData, filePath);}

template <class T>
bool AprgAudio<T>::saveToAiffFile (string const& filePath)
{
    vector<unsigned char> fileData;

    int32_t numBytesPerSample = bitDepth / 8;
    int32_t numBytesPerFrame = static_cast<int32_t>(numBytesPerSample * getNumChannels());
    int32_t totalNumAudioSampleBytes = static_cast<int32_t>(getNumSamplesPerChannel() * numBytesPerFrame);
    int32_t soundDataChunkSize = totalNumAudioSampleBytes + 8;

    // -----------------------------------------------------------    // HEADER CHUNK
    addStringToFileData (fileData, "FORM");

    // The file size in bytes is the header chunk size (4, not counting FORM and AIFF) + the COMM    // chunk size (26) + the metadata part of the SSND chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 26 + 16 + totalNumAudioSampleBytes;
    addInt32ToFileData (fileData, fileSizeInBytes, Endianness::BigEndian);

    addStringToFileData (fileData, "AIFF");

    // -----------------------------------------------------------
    // COMM CHUNK
    addStringToFileData (fileData, "COMM");
    addInt32ToFileData (fileData, 18, Endianness::BigEndian); // commChunkSize
    addInt16ToFileData (fileData, static_cast<int16_t>(getNumChannels()), Endianness::BigEndian); // num channels
    addInt32ToFileData (fileData, static_cast<int32_t>(getNumSamplesPerChannel()), Endianness::BigEndian); // num samples per channel
    addInt16ToFileData (fileData, bitDepth, Endianness::BigEndian); // bit depth
    addSampleRateToAiffData (fileData, sampleRate);
    // -----------------------------------------------------------
    // SSND CHUNK
    addStringToFileData (fileData, "SSND");    addInt32ToFileData (fileData, soundDataChunkSize, Endianness::BigEndian);
    addInt32ToFileData (fileData, 0, Endianness::BigEndian); // offset
    addInt32ToFileData (fileData, 0, Endianness::BigEndian); // block size

    for (unsigned int i = 0; i < getNumSamplesPerChannel(); i++)
    {
        for (unsigned int channel = 0; channel < getNumChannels(); channel++)
        {
            if (bitDepth == 8)
            {                unsigned char byte = sampleToSingleByte (samples[channel][i]);
                fileData.push_back (byte);
            }
            else if (bitDepth == 16)            {
                int16_t sampleAsInt = sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData (fileData, sampleAsInt, Endianness::BigEndian);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = (int32_t) (samples[channel][i] * (T)8388608.);

                unsigned char bytes[3];
                bytes[0] = (unsigned char) (sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = (unsigned char) (sampleAsIntAgain >>  8) & 0xFF;
                bytes[2] = (unsigned char) sampleAsIntAgain & 0xFF;

                fileData.push_back (bytes[0]);
                fileData.push_back (bytes[1]);
                fileData.push_back (bytes[2]);
            }
            else
            {
                assert (false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(fileData.size() - 8) ||
            soundDataChunkSize != static_cast<int32_t>(getNumSamplesPerChannel() *  numBytesPerFrame + 8))
    {
        cout << "ERROR: couldn't save file to " << filePath << endl;
        return false;    }

    // try to write the file
    return writeDataToFile (fileData, filePath);}

template <class T>
bool AprgAudio<T>::writeDataToFile (vector<unsigned char>& fileData, string const& filePath)
{
    ofstream outputFile (filePath, ios::binary);

    if (outputFile.is_open())
    {
        for (int i = 0; i < static_cast<int>(fileData.size()); i++)
        {
            char value = (char) fileData[i];
            outputFile.write (&value, sizeof (char));
        }

        outputFile.close();

        return true;
    }

    return false;
}

template <class T>
void AprgAudio<T>::addStringToFileData (vector<unsigned char>& fileData, string const& s)
{
    for (int i = 0; i < static_cast<int>(s.length()); i++)
        fileData.push_back ((unsigned char) s[i]);
}

template <class T>
void AprgAudio<T>::addInt32ToFileData (vector<unsigned char>& fileData, int32_t i, Endianness endianness)
{
    unsigned char bytes[4];

    if (endianness == Endianness::LittleEndian)
    {
        bytes[3] = (i >> 24) & 0xFF;
        bytes[2] = (i >> 16) & 0xFF;
        bytes[1] = (i >> 8) & 0xFF;
        bytes[0] = i & 0xFF;
    }
    else
    {
        bytes[0] = (i >> 24) & 0xFF;
        bytes[1] = (i >> 16) & 0xFF;
        bytes[2] = (i >> 8) & 0xFF;
        bytes[3] = i & 0xFF;
    }

    for (int i = 0; i < 4; i++)
        fileData.push_back (bytes[i]);
}

template <class T>
void AprgAudio<T>::addInt16ToFileData (vector<unsigned char>& fileData, int16_t i, Endianness endianness)
{
    unsigned char bytes[2];

    if (endianness == Endianness::LittleEndian)
    {
        bytes[1] = (i >> 8) & 0xFF;
        bytes[0] = i & 0xFF;
    }
    else
    {
        bytes[0] = (i >> 8) & 0xFF;
        bytes[1] = i & 0xFF;
    }

    fileData.push_back (bytes[0]);
    fileData.push_back (bytes[1]);
}

template <class T>
void AprgAudio<T>::clearAudioBuffer()
{
    for (int i = 0; i < static_cast<int>(samples.size()); i++)
    {
        samples[i].clear();
    }

    samples.clear();
}

template <class T>
AprgAudioFormat AprgAudio<T>::determineAprgAudioFormat (vector<unsigned char>& fileData)
{
    string header (fileData.begin(), fileData.begin() + 4);

    if (header == "RIFF")
        return AprgAudioFormat::Wave;
    else if (header == "FORM")
        return AprgAudioFormat::Aiff;
    else
        return AprgAudioFormat::Error;
}

template <class T>
int32_t AprgAudio<T>::fourBytesToInt (vector<unsigned char>& source, int startIndex, Endianness endianness)
{
    int32_t result;

    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 3] << 24) | (source[startIndex + 2] << 16) | (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 24) | (source[startIndex + 1] << 16) | (source[startIndex + 2] << 8) | source[startIndex + 3];

    return result;
}

template <class T>
int16_t AprgAudio<T>::twoBytesToInt (vector<unsigned char>& source, int startIndex, Endianness endianness)
{
    int16_t result;

    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 8) | source[startIndex + 1];

    return result;
}

template <class T>
int AprgAudio<T>::getIndexOfString (vector<unsigned char>& source, string const& stringToSearchFor)
{
    int index = -1;
    int stringLength = (int)stringToSearchFor.length();

    for (int i = 0; i < static_cast<int>(source.size() - stringLength); i++)
    {
        string section (source.begin() + i, source.begin() + i + stringLength);

        if (section == stringToSearchFor)
        {
            index = i;
            break;
        }
    }

    return index;
}

template <class T>
T AprgAudio<T>::sixteenBitIntToSample (int16_t sample)
{
    return static_cast<T> (sample) / static_cast<T> (32768.);
}

template <class T>
int16_t AprgAudio<T>::sampleToSixteenBitInt (T sample)
{
    sample = clamp (sample, -1., 1.);
    return static_cast<int16_t> (sample * 32767.);
}

template <class T>
unsigned char AprgAudio<T>::sampleToSingleByte (T sample)
{
    sample = clamp (sample, -1., 1.);
    sample = (sample + 1.) / 2.;
    return static_cast<unsigned char> (sample * 255.);
}

template <class T>
T AprgAudio<T>::singleByteToSample (unsigned char sample)
{
    return static_cast<T> (sample - 128) / static_cast<T> (128.);
}

template <class T>
T AprgAudio<T>::clamp (T value, T minValue, T maxValue)
{
    value = min (value, maxValue);
    value = max (value, minValue);
    return value;
}

//===========================================================
template class AprgAudio<float>;
template class AprgAudio<double>;

}

}