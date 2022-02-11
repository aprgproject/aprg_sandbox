#include "Audio.hpp"

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;

namespace alba
{

namespace AprgAudio
{

// Pre-defined 10-byte representations of common sample rates

unordered_map <unsigned int, vector<unsigned char>> aiffSampleRateTable = {
    {8000, {64, 11, 250, 0, 0, 0, 0, 0, 0, 0}},
    {11025, {64, 12, 172, 68, 0, 0, 0, 0, 0, 0}},
    {16000, {64, 12, 250, 0, 0, 0, 0, 0, 0, 0}},
    {22050, {64, 13, 172, 68, 0, 0, 0, 0, 0, 0}},
    {32000, {64, 13, 250, 0, 0, 0, 0, 0, 0, 0}},
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
Audio<T>::Audio()
{
    bitDepth = 16;
    sampleRate = 44100;
    samples.resize(1);
    samples[0].resize(0);
    audioFileFormat = AudioFormat::NotLoaded;
}

template <class T>
unsigned int Audio<T>::getSampleRate() const
{
    return sampleRate;
}

template <class T>
unsigned int Audio<T>::getNumChannels() const
{
    return samples.size();
}

template <class T>
bool Audio<T>::isMono() const
{
    return getNumChannels() == 1;
}

template <class T>
bool Audio<T>::isStereo() const
{
    return getNumChannels() == 2;
}

template <class T>
int Audio<T>::getBitDepth() const
{
    return bitDepth;
}

template <class T>
unsigned int Audio<T>::getNumSamplesPerChannel() const
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
std::vector<T> const& Audio<T>::getSamplesAtChannel(unsigned int const channelIndex) const
{
    return samples[channelIndex];
}

template <class T>
std::vector<T> & Audio<T>::getSamplesReferenceAtChannel(unsigned int const channelIndex)
{
    return samples[channelIndex];
}

template <class T>
double Audio<T>::getLengthInSeconds() const
{
    return (double)getNumSamplesPerChannel() / (double)sampleRate;
}

template <class T>
void Audio<T>::printSummary() const
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
bool Audio<T>::setAudioBuffer (AudioBuffer& newBuffer)
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
        }
    }

    return true;
}

template <class T>
void Audio<T>::setAudioBufferSize (unsigned int numChannels, unsigned int numSamples)
{
    samples.resize(numChannels);
    setNumSamplesPerChannel(numSamples);
}

template <class T>
void Audio<T>::setNumSamplesPerChannel (unsigned int numSamples)
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
void Audio<T>::setNumChannels (int numChannels)
{
    int originalNumChannels = static_cast<int>(getNumChannels());
    int originalNumSamplesPerChannel = static_cast<int>(getNumSamplesPerChannel());

    samples.resize(numChannels);

    // make sure any new channels are set to the right size
    // and filled with zeros
    if (numChannels > originalNumChannels)
    {
        for (int i = originalNumChannels; i < numChannels; i++)
        {
            samples[i].resize(originalNumSamplesPerChannel);
            fill (samples[i].begin(), samples[i].end(), (T)0.);
        }
    }
}

template <class T>
void Audio<T>::setBitDepth (int numBitsPerSample)
{
    bitDepth = numBitsPerSample;
}

template <class T>
void Audio<T>::setSampleRate (unsigned int newSampleRate)
{
    sampleRate = newSampleRate;
}

template <class T>
bool Audio<T>::load (string const& filePath)
{
    ifstream file (AlbaLocalPathHandler(filePath).getFullPath(), ios::binary);

    // check the file exists
    if (! file.good())
    {
        cout << "ERROR: File doesn't exist or otherwise can't load file" << endl;
        cout << filePath << endl;
        return false;
    }

    file.unsetf (ios::skipws);
    istream_iterator<unsigned char> begin (file), end;
    vector<unsigned char> fileDataBytes (begin, end);

    // get audio file format
    audioFileFormat = determineAudioFormat (fileDataBytes);

    if (audioFileFormat == AudioFormat::Wave)
    {
        return decodeWaveFile (fileDataBytes);
    }
    else if (audioFileFormat == AudioFormat::Aiff)
    {
        return decodeAiffFile (fileDataBytes);
    }
    else
    {
        cout << "Audio File Type: " << "Error" << endl;
        return false;
    }
}

template <class T>
bool Audio<T>::decodeWaveFile (vector<unsigned char>& fileDataBytes)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    string headerChunkID (fileDataBytes.begin(), fileDataBytes.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileDataBytes, 4) + 8;
    string format (fileDataBytes.begin() + 8, fileDataBytes.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfDataChunk = getIndexOfString (fileDataBytes, "data");
    int indexOfFormatChunk = getIndexOfString (fileDataBytes, "fmt");

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
    string formatChunkID (fileDataBytes.begin() + f, fileDataBytes.begin() + f + 4);
    //int32_t formatChunkSize = fourBytesToInt (fileDataBytes, f + 4);
    int16_t audioFormat = twoBytesToInt (fileDataBytes, f + 8);
    int16_t numChannels = twoBytesToInt (fileDataBytes, f + 10);
    sampleRate = (unsigned int) fourBytesToInt (fileDataBytes, f + 12);
    int32_t numBytesPerSecond = fourBytesToInt (fileDataBytes, f + 16);
    int16_t numBytesPerBlock = twoBytesToInt (fileDataBytes, f + 20);
    bitDepth = (int) twoBytesToInt (fileDataBytes, f + 22);

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
    string dataChunkID (fileDataBytes.begin() + d, fileDataBytes.begin() + d + 4);
    int32_t dataChunkSize = fourBytesToInt (fileDataBytes, d + 4);

    int numSamples = dataChunkSize / (numChannels * bitDepth / 8);
    int samplesStartIndex = indexOfDataChunk + 8;

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamples; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerBlock * i) + channel * numBytesPerSample;

            if (bitDepth == 8)
            {
                T sample = singleByteToSample (fileDataBytes[sampleIndex]);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileDataBytes, sampleIndex);
                T sample = sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileDataBytes[sampleIndex + 2] << 16) | (fileDataBytes[sampleIndex + 1] << 8) | fileDataBytes[sampleIndex];

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
bool Audio<T>::decodeAiffFile (vector<unsigned char>& fileDataBytes)
{
    // -----------------------------------------------------------
    // HEADER CHUNK
    string headerChunkID (fileDataBytes.begin(), fileDataBytes.begin() + 4);
    //int32_t fileSizeInBytes = fourBytesToInt (fileDataBytes, 4, Endianness::BigEndian) + 8;
    string format (fileDataBytes.begin() + 8, fileDataBytes.begin() + 12);

    // -----------------------------------------------------------
    // try and find the start points of key chunks
    int indexOfCommChunk = getIndexOfString (fileDataBytes, "COMM");
    int indexOfSoundDataChunk = getIndexOfString (fileDataBytes, "SSND");

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
    string commChunkID (fileDataBytes.begin() + p, fileDataBytes.begin() + p + 4);
    //int32_t commChunkSize = fourBytesToInt (fileDataBytes, p + 4, Endianness::BigEndian);
    int16_t numChannels = twoBytesToInt (fileDataBytes, p + 8, Endianness::BigEndian);
    int32_t numSamplesPerChannel = fourBytesToInt (fileDataBytes, p + 10, Endianness::BigEndian);
    bitDepth = (int) twoBytesToInt (fileDataBytes, p + 14, Endianness::BigEndian);
    sampleRate = getAiffSampleRate (fileDataBytes, p + 16);

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
    string soundDataChunkID (fileDataBytes.begin() + s, fileDataBytes.begin() + s + 4);
    int32_t soundDataChunkSize = fourBytesToInt (fileDataBytes, s + 4, Endianness::BigEndian);
    int32_t offset = fourBytesToInt (fileDataBytes, s + 8, Endianness::BigEndian);
    //int32_t blockSize = fourBytesToInt (fileDataBytes, s + 12, Endianness::BigEndian);

    int numBytesPerSample = bitDepth / 8;
    int numBytesPerFrame = numBytesPerSample * numChannels;
    int totalNumAudioSampleBytes = numSamplesPerChannel * numBytesPerFrame;
    int samplesStartIndex = s + 16 + (int)offset;

    // sanity check the data
    if ((soundDataChunkSize - 8) != totalNumAudioSampleBytes || totalNumAudioSampleBytes
            > static_cast<int>(fileDataBytes.size() - samplesStartIndex))
    {
        cout << "ERROR: the metadatafor this file doesn't seem right" << endl;
        return false;
    }

    clearAudioBuffer();
    samples.resize(numChannels);

    for (int i = 0; i < numSamplesPerChannel; i++)
    {
        for (int channel = 0; channel < numChannels; channel++)
        {
            int sampleIndex = samplesStartIndex + (numBytesPerFrame * i) + channel * numBytesPerSample;

            if (bitDepth == 8)
            {
                int8_t sampleAsSigned8Bit = (int8_t)fileDataBytes[sampleIndex];
                T sample = (T)sampleAsSigned8Bit / (T)128.;
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = twoBytesToInt (fileDataBytes, sampleIndex, Endianness::BigEndian);
                T sample = sixteenBitIntToSample (sampleAsInt);
                samples[channel].push_back (sample);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsInt = 0;
                sampleAsInt = (fileDataBytes[sampleIndex] << 16) | (fileDataBytes[sampleIndex + 1] << 8) | fileDataBytes[sampleIndex + 2];

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
unsigned int Audio<T>::getAiffSampleRate (vector<unsigned char>& fileDataBytes, int sampleRateStartIndex)
{
    for (auto it : aiffSampleRateTable)
    {
        if (tenByteMatch (fileDataBytes, sampleRateStartIndex, it.second, 0))
            return it.first;
    }

    return -1;
}

template <class T>
bool Audio<T>::tenByteMatch (vector<unsigned char>& v1, int startIndex1, vector<unsigned char>& v2, int startIndex2)
{
    for (int i = 0; i < 10; i++)
    {
        if (v1[startIndex1 + i] != v2[startIndex2 + i])
            return false;
    }

    return true;
}

template <class T>
void Audio<T>::addSampleRateToAiffData (vector<unsigned char>& fileDataBytes, unsigned int sampleRate)
{
    if (aiffSampleRateTable.count (sampleRate) > 0)
    {
        for (int i = 0; i < 10; i++)
            fileDataBytes.push_back (aiffSampleRateTable[sampleRate][i]);
    }
}

template <class T>
bool Audio<T>::save (string const& filePath, AudioFormat format)
{
    AlbaLocalPathHandler filePathHandler(filePath);
    if (format == AudioFormat::Wave)
    {
        return saveToWaveFile (filePathHandler.getFullPath());
    }
    else if (format == AudioFormat::Aiff)
    {
        return saveToAiffFile (filePathHandler.getFullPath());
    }

    return false;
}

template <class T>
bool Audio<T>::saveToWaveFile (string const& filePath)
{
    vector<unsigned char> fileDataBytes;

    int32_t dataChunkSize = static_cast<int32_t>(getNumSamplesPerChannel() * (getNumChannels() * bitDepth / 8));

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData (fileDataBytes, "RIFF");

    // The file size in bytes is the header chunk size (4, not counting RIFF and WAVE) + the format
    // chunk size (24) + the metadata part of the data chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 24 + 8 + dataChunkSize;
    addInt32ToFileData (fileDataBytes, fileSizeInBytes);

    addStringToFileData (fileDataBytes, "WAVE");

    // -----------------------------------------------------------
    // FORMAT CHUNK
    addStringToFileData (fileDataBytes, "fmt ");
    addInt32ToFileData (fileDataBytes, 16); // format chunk size (16 for PCM)
    addInt16ToFileData (fileDataBytes, 1); // audio format = 1
    addInt16ToFileData (fileDataBytes, static_cast<int16_t>(getNumChannels())); // num channels
    addInt32ToFileData (fileDataBytes, (int32_t)sampleRate); // sample rate

    int32_t numBytesPerSecond = static_cast<int32_t>((getNumChannels() * sampleRate * bitDepth) / 8);
    addInt32ToFileData (fileDataBytes, numBytesPerSecond);

    int16_t numBytesPerBlock = static_cast<int16_t>(getNumChannels() * (bitDepth / 8));
    addInt16ToFileData (fileDataBytes, numBytesPerBlock);

    addInt16ToFileData (fileDataBytes, (int16_t)bitDepth);

    // -----------------------------------------------------------
    // DATA CHUNK
    addStringToFileData (fileDataBytes, "data");
    addInt32ToFileData (fileDataBytes, dataChunkSize);

    for (unsigned int i = 0; i < getNumSamplesPerChannel(); i++)
    {
        for (unsigned int channel = 0; channel < getNumChannels(); channel++)
        {
            if (bitDepth == 8)
            {
                unsigned char byte = sampleToSingleByte (samples[channel][i]);
                fileDataBytes.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData (fileDataBytes, sampleAsInt);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = (int32_t) (samples[channel][i] * (T)8388608.);

                unsigned char bytes[3];
                bytes[2] = (unsigned char) (sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = (unsigned char) (sampleAsIntAgain >>  8) & 0xFF;
                bytes[0] = (unsigned char) sampleAsIntAgain & 0xFF;

                fileDataBytes.push_back (bytes[0]);
                fileDataBytes.push_back (bytes[1]);
                fileDataBytes.push_back (bytes[2]);
            }
            else
            {
                assert (false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(fileDataBytes.size() - 8)
            || dataChunkSize != static_cast<int32_t>(getNumSamplesPerChannel() * getNumChannels() * (bitDepth / 8)))
    {
        cout << "ERROR: couldn't save file to " << filePath << endl;
        return false;
    }

    // try to write the file
    return writeDataToFile (fileDataBytes, filePath);
}

template <class T>
bool Audio<T>::saveToAiffFile (string const& filePath)
{
    vector<unsigned char> fileDataBytes;

    int32_t numBytesPerSample = bitDepth / 8;
    int32_t numBytesPerFrame = static_cast<int32_t>(numBytesPerSample * getNumChannels());
    int32_t totalNumAudioSampleBytes = static_cast<int32_t>(getNumSamplesPerChannel() * numBytesPerFrame);
    int32_t soundDataChunkSize = totalNumAudioSampleBytes + 8;

    // -----------------------------------------------------------
    // HEADER CHUNK
    addStringToFileData (fileDataBytes, "FORM");

    // The file size in bytes is the header chunk size (4, not counting FORM and AIFF) + the COMM
    // chunk size (26) + the metadata part of the SSND chunk plus the actual data chunk size
    int32_t fileSizeInBytes = 4 + 26 + 16 + totalNumAudioSampleBytes;
    addInt32ToFileData (fileDataBytes, fileSizeInBytes, Endianness::BigEndian);

    addStringToFileData (fileDataBytes, "AIFF");

    // -----------------------------------------------------------
    // COMM CHUNK
    addStringToFileData (fileDataBytes, "COMM");
    addInt32ToFileData (fileDataBytes, 18, Endianness::BigEndian); // commChunkSize
    addInt16ToFileData (fileDataBytes, static_cast<int16_t>(getNumChannels()), Endianness::BigEndian); // num channels
    addInt32ToFileData (fileDataBytes, static_cast<int32_t>(getNumSamplesPerChannel()), Endianness::BigEndian); // num samples per channel
    addInt16ToFileData (fileDataBytes, bitDepth, Endianness::BigEndian); // bit depth
    addSampleRateToAiffData (fileDataBytes, sampleRate);

    // -----------------------------------------------------------
    // SSND CHUNK
    addStringToFileData (fileDataBytes, "SSND");
    addInt32ToFileData (fileDataBytes, soundDataChunkSize, Endianness::BigEndian);
    addInt32ToFileData (fileDataBytes, 0, Endianness::BigEndian); // offset
    addInt32ToFileData (fileDataBytes, 0, Endianness::BigEndian); // block size

    for (unsigned int i = 0; i < getNumSamplesPerChannel(); i++)
    {
        for (unsigned int channel = 0; channel < getNumChannels(); channel++)
        {
            if (bitDepth == 8)
            {
                unsigned char byte = sampleToSingleByte (samples[channel][i]);
                fileDataBytes.push_back (byte);
            }
            else if (bitDepth == 16)
            {
                int16_t sampleAsInt = sampleToSixteenBitInt (samples[channel][i]);
                addInt16ToFileData (fileDataBytes, sampleAsInt, Endianness::BigEndian);
            }
            else if (bitDepth == 24)
            {
                int32_t sampleAsIntAgain = (int32_t) (samples[channel][i] * (T)8388608.);

                unsigned char bytes[3];
                bytes[0] = (unsigned char) (sampleAsIntAgain >> 16) & 0xFF;
                bytes[1] = (unsigned char) (sampleAsIntAgain >>  8) & 0xFF;
                bytes[2] = (unsigned char) sampleAsIntAgain & 0xFF;

                fileDataBytes.push_back (bytes[0]);
                fileDataBytes.push_back (bytes[1]);
                fileDataBytes.push_back (bytes[2]);
            }
            else
            {
                assert (false && "Trying to write a file with unsupported bit depth");
                return false;
            }
        }
    }

    // check that the various sizes we put in the metadata are correct
    if (fileSizeInBytes != static_cast<int32_t>(fileDataBytes.size() - 8) ||
            soundDataChunkSize != static_cast<int32_t>(getNumSamplesPerChannel() *  numBytesPerFrame + 8))
    {
        cout << "ERROR: couldn't save file to " << filePath << endl;
        return false;
    }

    // try to write the file
    return writeDataToFile (fileDataBytes, filePath);
}

template <class T>
bool Audio<T>::writeDataToFile (vector<unsigned char>& fileDataBytes, string const& filePath)
{
    ofstream outputFile (filePath, ios::binary);

    if (outputFile.is_open())
    {
        for (unsigned char const fileDataBytesByte : fileDataBytes)
        {
            char value = static_cast<char>(fileDataBytesByte);
            outputFile.write (&value, sizeof (char));
        }
        outputFile.close();
        return true;
    }
    return false;
}

template <class T>
void Audio<T>::addStringToFileData (vector<unsigned char>& fileDataBytes, string const& s)
{
    for(char const c : s)
    {
        fileDataBytes.push_back(c);
    }
    //for (int i = 0; i < static_cast<int>(s.length()); i++)
    //    fileDataBytes.push_back ((unsigned char) s[i]);
}

template <class T>
void Audio<T>::addInt32ToFileData (vector<unsigned char>& fileDataBytes, int32_t i, Endianness endianness)
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

    for (unsigned char byte : bytes)
    {
        fileDataBytes.push_back(byte);
    }
}

template <class T>
void Audio<T>::addInt16ToFileData (vector<unsigned char>& fileDataBytes, int16_t i, Endianness endianness)
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

    fileDataBytes.push_back (bytes[0]);
    fileDataBytes.push_back (bytes[1]);
}

template <class T>
void Audio<T>::clearAudioBuffer()
{
    for (int i = 0; i < static_cast<int>(samples.size()); i++)
    {
        samples[i].clear();
    }

    samples.clear();
}

template <class T>
AudioFormat Audio<T>::determineAudioFormat (vector<unsigned char>& fileDataBytes)
{
    string header (fileDataBytes.begin(), fileDataBytes.begin() + 4);

    if (header == "RIFF")
        return AudioFormat::Wave;
    else if (header == "FORM")
        return AudioFormat::Aiff;
    else
        return AudioFormat::Error;
}

template <class T>
int32_t Audio<T>::fourBytesToInt (vector<unsigned char>& source, int startIndex, Endianness endianness)
{
    int32_t result;

    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 3] << 24) | (source[startIndex + 2] << 16) | (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 24) | (source[startIndex + 1] << 16) | (source[startIndex + 2] << 8) | source[startIndex + 3];

    return result;
}

template <class T>
int16_t Audio<T>::twoBytesToInt (vector<unsigned char>& source, int startIndex, Endianness endianness)
{
    int16_t result;

    if (endianness == Endianness::LittleEndian)
        result = (source[startIndex + 1] << 8) | source[startIndex];
    else
        result = (source[startIndex] << 8) | source[startIndex + 1];

    return result;
}

template <class T>
int Audio<T>::getIndexOfString (vector<unsigned char>& source, string const& stringToSearchFor)
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
T Audio<T>::sixteenBitIntToSample (int16_t sample)
{
    return static_cast<T> (sample) / static_cast<T> (32768.);
}

template <class T>
int16_t Audio<T>::sampleToSixteenBitInt (T sample)
{
    sample = clamp (sample, -1., 1.);
    return static_cast<int16_t> (sample * 32767.);
}

template <class T>
unsigned char Audio<T>::sampleToSingleByte (T sample)
{
    sample = clamp (sample, -1., 1.);
    sample = (sample + 1.) / 2.;
    return static_cast<unsigned char> (sample * 255.);
}

template <class T>
T Audio<T>::singleByteToSample (unsigned char sample)
{
    return static_cast<T> (sample - 128) / static_cast<T> (128.);
}

template <class T>
T Audio<T>::clamp (T value, T minValue, T maxValue)
{
    value = min (value, maxValue);
    value = max (value, minValue);
    return value;
}

//===========================================================
template class Audio<float>;
template class Audio<double>;

}

}
