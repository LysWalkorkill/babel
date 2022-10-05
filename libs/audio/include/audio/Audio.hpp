/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <portaudio.h>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>

#include "Exception.hpp"
#include "network/QTSocketUDP.hpp"
#include "AudioEncoder.hpp"
#include "IAudio.hpp"

#define SAMPLE_RATE 24000
#define FRAME_RATE 480
#define CHANNELS 2

namespace babel::audio
{
    struct UserData
    {
        std::shared_ptr<babel::network::ISocket> socketUDP;
        std::shared_ptr<IAudioEncoder> audioEncoder;
        std::queue<int16_t *> datas;
        int size;
        std::mutex mutex;

        class ScopedLock
        {
            public:
                ScopedLock(UserData &userdata): _userData(userdata)
                {
                    _userData.mutex.lock();
                }

                ~ScopedLock() {
                    _userData.mutex.unlock();
                }

            private:
                UserData &_userData;
        };
    };

    static babel::audio::UserData userDataPa;

    class Audio : public IAudio {
        public:
            Audio();
            ~Audio();
            Audio(const Audio &audio);
            Audio &operator=(const Audio &audio);

            void openPort() override;
            void start() const override;
            void stop() const override;
            void sleep(int sec) const override;
            void close() override;

            void setCallbackFunction(PaStreamCallback *readFct);

        private:
            PaStream *_stream = nullptr;
            PaStreamCallback *_readFct = nullptr;
    };
} // namespace babel::audio


#endif /* !AUDIO_HPP_ */
