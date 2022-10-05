/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#include <vector>
#include "audio/AudioEncoder.hpp"
#include "audio/Exception.hpp"

using namespace babel::audio;

AudioEncoder::AudioEncoder(int channels, int frameSize, int rate) : _channels(channels), _frameSize(frameSize), _rate(rate), _dataLength(0)
{
    int err = 0;

    _encoder = opus_encoder_create(rate, channels, OPUS_APPLICATION_AUDIO, &err);

    if (err != OPUS_OK)
        throw AudioException("Initialisation of Opus encoder failed");

    _decoder = opus_decoder_create(rate, channels, &err);

    if (err != OPUS_OK)
        throw AudioException("Initialisation of Opus decoder failed");
}

AudioEncoder::~AudioEncoder()
{
    opus_encoder_destroy(_encoder);
    opus_decoder_destroy(_decoder);
}

AudioEncoder::AudioEncoder(const AudioEncoder &audioEncoder) : 
    _channels(audioEncoder._channels),
    _frameSize(audioEncoder._frameSize),
    _rate(audioEncoder._rate),
    _dataLength(audioEncoder._dataLength),
    _encoder(audioEncoder._encoder),
    _decoder(audioEncoder._decoder)
{
}

AudioEncoder &AudioEncoder::operator=(const AudioEncoder &audioEncoder)
{
    _channels = audioEncoder._channels;
    _frameSize = audioEncoder._frameSize;
    _rate = audioEncoder._rate;
    _dataLength = audioEncoder._dataLength;
    _encoder = audioEncoder._encoder;
    _decoder = audioEncoder._decoder;
    return (*this);
}

std::string AudioEncoder::encode(int16_t *data)
{
    std::string encodedData;

    encodedData.reserve(_frameSize * _channels);
    _dataLength = opus_encode(_encoder, data, _frameSize, reinterpret_cast<unsigned char *>(encodedData.data()), _frameSize * _channels);

    if (_dataLength < 0)
        throw AudioException("Opus failed to encode audio.");
    return encodedData;
}

int AudioEncoder::getDataLength() const noexcept
{
    return _dataLength;
}

int16_t *AudioEncoder::decode(const std::string &encodedData, int dataLength) const
{
    int decodeLength = 0;
    int16_t *decodeData = new int16_t[_frameSize * _channels * sizeof(int16_t)];

    decodeLength = opus_decode(_decoder, reinterpret_cast<const unsigned char *>(encodedData.c_str()), dataLength, decodeData, _frameSize, 0);
    if (decodeLength < 0)
        throw AudioException("Opus failed to decode audio.");
    return decodeData;
}
