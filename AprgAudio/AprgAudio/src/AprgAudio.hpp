#pragma once

#include <iostream>
#include <vector>
#include <assert.h>
#include <string>


namespace alba {

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

    /** Constructor */
    AprgAudio();

    /** Loads an audio file from a given file path.
     * @Returns true if the file was successfully loaded
     */
    bool load (std::string filePath);

    /** Saves an audio file to a given file path.
     * @Returns true if the file was successfully saved
     */
    bool save (std::string filePath, AprgAudioFormat format = AprgAudioFormat::Wave);

    /** @Returns the sample rate */
    uint32_t getSampleRate() const;

    /** @Returns the number of audio channels in the buffer */
    int getNumChannels() const;

    /** @Returns true if the audio file is mono */
    bool isMono() const;

    /** @Returns true if the audio file is stereo */
    bool isStereo() const;

    /** @Returns the bit depth of each sample */
    int getBitDepth() const;

    /** @Returns the number of samples per channel */
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
    void setSampleRate (uint32_t newSampleRate);

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

    AprgAudioFormat determineAprgAudioFormat (std::vector<uint8_t>& fileData);
    bool decodeWaveFile (std::vector<uint8_t>& fileData);
    bool decodeAiffFile (std::vector<uint8_t>& fileData);

    bool saveToWaveFile (std::string filePath);
    bool saveToAiffFile (std::string filePath);

    void clearAudioBuffer();

    int32_t fourBytesToInt (std::vector<uint8_t>& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    int16_t twoBytesToInt (std::vector<uint8_t>& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    int getIndexOfString (std::vector<uint8_t>& source, std::string s);

    T sixteenBitIntToSample (int16_t sample);
    int16_t sampleToSixteenBitInt (T sample);

    uint8_t sampleToSingleByte (T sample);
    T singleByteToSample (uint8_t sample);

    uint32_t getAiffSampleRate (std::vector<uint8_t>& fileData, int sampleRateStartIndex);
    bool tenByteMatch (std::vector<uint8_t>& v1, int startIndex1, std::vector<uint8_t>& v2, int startIndex2);
    void addSampleRateToAiffData (std::vector<uint8_t>& fileData, uint32_t sampleRate);
    T clamp (T v1, T minValue, T maxValue);

    void addStringToFileData (std::vector<uint8_t>& fileData, std::string s);
    void addInt32ToFileData (std::vector<uint8_t>& fileData, int32_t i, Endianness endianness = Endianness::LittleEndian);
    void addInt16ToFileData (std::vector<uint8_t>& fileData, int16_t i, Endianness endianness = Endianness::LittleEndian);

    bool writeDataToFile (std::vector<uint8_t>& fileData, std::string filePath);

    AprgAudioFormat audioFileFormat;
    uint32_t sampleRate;
    int bitDepth;
};

}
