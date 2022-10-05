/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** IAudioEncoder
*/

#ifndef IAUDIOENCODER_HPP_
#define IAUDIOENCODER_HPP_

#include <string>
#include <memory>

namespace babel::audio
{
    class IAudioEncoder {
        public:
            virtual ~IAudioEncoder() = default;

            virtual std::string encode(int16_t *) = 0;
            virtual int16_t *decode(const std::string &encodedData, int dataLength) const = 0;
            virtual int getDataLength() const noexcept = 0;

        private:
    };
} // namespace babel::audio



#endif /* !IAUDIOENCODER_HPP_ */
