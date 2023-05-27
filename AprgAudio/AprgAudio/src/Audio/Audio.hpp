#pragma once

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

namespace alba {

namespace AprgAudio {

/** The different types of audio file, plus some other types to
 * indicate a failure to load a file, or that one hasn't been
 * loaded yet
 */

enum class AudioFormat { Error, NotLoaded, Wave, Aiff };

template <class T>
class Audio {
public:
    typedef std::vector<std::vector<T> > AudioBuffer;

    Audio();

    bool load(std::string const& filePath);

    bool save(std::string const& filePath, AudioFormat format = AudioFormat::Wave);

    int getSampleRate() const;

    int getNumChannels() const;

    bool isMono() const;
    bool isStereo() const;

    int getBitDepth() const;

    int getNumSamplesPerChannel() const;

    std::vector<T> const& getSamplesAtChannel(int const channelIndex) const;
    std::vector<T>& getSamplesReferenceAtChannel(int const channelIndex);

    /** @Returns the length in seconds of the audio file based on the number of samples and sample rate */
    double getLengthInSeconds() const;
    /** Prints a summary of the audio file to the console */
    void printSummary() const;
    /** Set the audio buffer for this Audio by copying samples from another buffer.
     * @Returns true if the buffer was copied successfully.
     */
    bool setAudioBuffer(AudioBuffer& newBuffer);

    /** Sets the audio buffer to a given number of channels and number of samples per channel. This will try to preserve
     * the existing audio, adding zeros to any new channels or new samples in a given channel.
     */
    void setAudioBufferSize(int numChannels, int numSamples);

    /** Sets the number of samples per channel in the audio buffer. This will try to preserve
     * the existing audio, adding zeros to new samples in a given channel if the number of samples is increased.
     */
    void setNumSamplesPerChannel(int numSamples);

    /** Sets the number of channels. New channels will have the correct number of samples and be initialised to zero */
    void setNumChannels(int numChannels);
    /** Sets the bit depth for the audio file. If you use the save() function, this bit depth rate will be used */
    void setBitDepth(int numBitsPerSample);

    /** Sets the sample rate for the audio file. If you use the save() function, this sample rate will be used */
    void setSampleRate(int newSampleRate);

    /** A vector of vectors holding the audio samples for the Audio. You can
     * access the samples by channel and then by sample index, i.e:     *
     *      samples[channel][sampleIndex]
     */
    AudioBuffer samples;
private:
    enum class Endianness { LittleEndian, BigEndian };

    AudioFormat determineAudioFormat(std::vector<uint8_t>& fileDataBytes);
    bool decodeWaveFile(std::vector<uint8_t>& fileDataBytes);
    bool decodeAiffFile(std::vector<uint8_t>& fileDataBytes);

    bool saveToWaveFile(std::string const& filePath);
    bool saveToAiffFile(std::string const& filePath);
    void clearAudioBuffer();

    int32_t fourBytesToInt(
        std::vector<uint8_t> const& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    int16_t twoBytesToInt(
        std::vector<uint8_t> const& source, int startIndex, Endianness endianness = Endianness::LittleEndian);
    int getIndexOfString(std::vector<uint8_t> const& source, std::string const& s);

    T sixteenBitIntToSample(int16_t sample);
    int16_t sampleToSixteenBitInt(T sample);

    uint8_t sampleToSingleByte(T sample);
    T singleByteToSample(uint8_t sample);

    int getAiffSampleRate(std::vector<uint8_t>& fileDataBytes, int sampleRateStartIndex);
    bool tenByteMatch(std::vector<uint8_t>& v1, int startIndex1, std::vector<uint8_t>& v2, int startIndex2);
    void addSampleRateToAiffData(std::vector<uint8_t>& fileDataBytes, int sampleRate);
    T clamp(T value, T minValue, T maxValue);

    void addStringToFileData(std::vector<uint8_t>& fileDataBytes, std::string const& s);
    void addInt32ToFileData(
        std::vector<uint8_t>& fileDataBytes, int32_t i, Endianness endianness = Endianness::LittleEndian);
    void addInt16ToFileData(
        std::vector<uint8_t>& fileDataBytes, int16_t i, Endianness endianness = Endianness::LittleEndian);

    bool writeDataToFile(std::vector<uint8_t>& fileDataBytes, std::string const& filePath);

    AudioFormat audioFileFormat;
    int sampleRate;    int bitDepth;
};

}  // namespace AprgAudio
}  // namespace alba
