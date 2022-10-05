/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#ifndef AUDIOENCODER_HPP
#define AUDIOENCODER_HPP

#include <opus.h>
#include <string>

#include "IAudioEncoder.hpp"

namespace babel::audio
{
    class AudioEncoder : public IAudioEncoder {
        public:
            AudioEncoder(int channels, int frameSize, int rate);
            ~AudioEncoder();
            AudioEncoder(const AudioEncoder &audioEncoder);
            AudioEncoder &operator=(const AudioEncoder &audioEncoder);

            std::string encode(int16_t *data) override;
            int16_t *decode(const std::string &encodedData, int dataLength) const override;

            [[nodiscard]] int getDataLength() const noexcept override;

    private:
            OpusEncoder *_encoder;
            OpusDecoder *_decoder;

            int _channels;
            int _frameSize;
            int _rate;
            int _dataLength;
    };
}

#endif //BABEL_SERVER_AUDIOENCODER_HPP
