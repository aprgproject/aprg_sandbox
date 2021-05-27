#pragma once

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>


namespace alba
{

/** The different types of audio file, plus some other types to
 * indicate a failure to load a file, or that one hasn't been
 * loaded yet
 */

enum class AprgAudioFormat
{
    Error,
    NotLoaded,
    Wave,
    Aiff
};

template <class T>
class AprgAudio
{
public:

    typedef std::vector<std::vector<T> > AudioBuffer;

    AprgAudio();

    bool load (std::string filePath);

    bool save (std::string filePath, AprgAudioFormat format = AprgAudioFormat::Wave);

    unsigned int getSampleRate() const;

    int getNumChannels() const;

    bool isMono() const;

    bool isStereo() const;

    int getBitDepth() const;

    int getNumSamplesPerChannel() const;

    /** @Returns the length in seconds of the audio file based on the number of samples and sample rate */
    double getLengthInSeconds() const;

    /** Prints a summary of the audio file to the console */
    void printSummary() const;


    /** Set the audio buffer for this AprgAudio by copying samples from another buffer.
     * @Returns true if the buffer was copied successfully.
     */
    bool setAudioBuffer (AudioBuffer& newBuffer);

    /** Sets the audio buffer to a given number of channels and number of samples per channel. This will try to preserve
     * the existing audio, adding zeros to any new channels or new samples in a given channel.
     */
    void setAudioBufferSize (int numChannels, int numSamples);

    /** Sets the number of samples per channel in the audio buffer. This will try to preserve
     * the existing audio, adding zeros to new samples in a given channel if the number of samples is increased.
     */
    void setNumSamplesPerChannel (int numSamples);

    /** Sets the number of channels. New channels will have the correct number of samples and be initialised to zero */
    void setNumChannels (int numChannels);

    /** Sets the bit depth for the audio file. If you use the save() function, this bit depth rate will be used */
    void setBitDepth (int numBitsPerSample);

    /** Sets the sample rate for the audio file. If you use the save() function, this sample rate will be used */
    void setSampleRate (unsigned int newSampleRate);

    /** A vector of vectors holding the audio samples for the AprgAudio. You can
     * access the samples by channel and then by sample index, i.e:
     *
     *      samples[channel][sampleIndex]
     */
    AudioBuffer samples;

private:

    enum class Endianness
    {
        LittleEndian,
        BigEndian
    };

    AprgAudioFormat determineAprgAudioFormat (std::vector<unsigned char>& fileData);
    bool decodeWaveFile (std::vector<unsigned char>& fileData);
    bool decodeAiffFile (std::vector<unsigned char>& fileData);

    bool saveToWaveFile (std::string filePath);
    bool saveToAiffFile (std::string filePath);

    void clearAudioBuffer();

    int32_t fourBytesToInt (std::vector<unsigned char>& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    int16_t twoBytesToInt (std::vector<unsigned char>& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    int getIndexOfString (std::vector<unsigned char>& source, std::string s);

    T sixteenBitIntToSample (int16_t sample);
    int16_t sampleToSixteenBitInt (T sample);

    unsigned char sampleToSingleByte (T sample);
    T singleByteToSample (unsigned char sample);

    unsigned int getAiffSampleRate (std::vector<unsigned char>& fileData, int sampleRateStartIndex);
    bool tenByteMatch (std::vector<unsigned char>& v1, int startIndex1, std::vector<unsigned char>& v2, int startIndex2);
    void addSampleRateToAiffData (std::vector<unsigned char>& fileData, unsigned int sampleRate);
    T clamp (T v1, T minValue, T maxValue);

    void addStringToFileData (std::vector<unsigned char>& fileData, std::string s);
    void addInt32ToFileData (std::vector<unsigned char>& fileData, int32_t i, Endianness endianness = Endianness::LittleEndian);
    void addInt16ToFileData (std::vector<unsigned char>& fileData, int16_t i, Endianness endianness = Endianness::LittleEndian);

    bool writeDataToFile (std::vector<unsigned char>& fileData, std::string filePath);

    AprgAudioFormat audioFileFormat;
    unsigned int sampleRate;
    int bitDepth;
};

}
