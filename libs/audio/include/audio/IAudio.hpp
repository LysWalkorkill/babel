/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
    #define IAUDIO_HPP_

namespace babel::audio
{
    class IAudio {
    public:
        virtual ~IAudio() = default;

        virtual void openPort() = 0;
        virtual void start() const = 0;
        virtual void stop() const = 0;
        virtual void sleep(int sec) const = 0;
        virtual void close() = 0;

    private:
    };
} // namespace babel::audio



#endif /* !IAUDIO_HPP_ */