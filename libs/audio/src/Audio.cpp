/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Audio
*/

#include "audio/Audio.hpp"
#include <iostream>

using namespace babel::audio;

Audio::Audio()
{
    PaError rv = Pa_Initialize();
    if (rv != paNoError)
        throw AudioException(std::string(Pa_GetErrorText(rv)));
}

Audio::~Audio()
{
    if (_stream)
        Pa_CloseStream(_stream);
    Pa_Terminate();
}

void Audio::openPort()
{
    PaError rv;

    rv = Pa_OpenDefaultStream(
        &_stream,
        CHANNELS,
        CHANNELS,
        paInt16,
        SAMPLE_RATE,
        FRAME_RATE,
        _readFct,
        nullptr
    );
    if (rv != paNoError) {
        throw AudioException(std::string(Pa_GetErrorText(rv)));
    }
}

void Audio::setCallbackFunction(PaStreamCallback *readFct)
{
    _readFct = readFct;
}

void Audio::start() const
{
    PaError rv;

    rv = Pa_StartStream(_stream);
    if (rv != paNoError) {
        throw AudioException(std::string(Pa_GetErrorText(rv)));
    }
}

void Audio::stop() const
{
    PaError rv;

    rv = Pa_StopStream(_stream);
    if (rv != paNoError) {
        throw AudioException(std::string(Pa_GetErrorText(rv)));
    }
}

void Audio::sleep(int sec) const
{
    Pa_Sleep(1000 * sec);
}

void Audio::close()
{
    PaError rv;

    if (_stream) {
        rv = Pa_CloseStream(_stream);
        _stream = nullptr;
        if (rv != paNoError) {
            throw AudioException(std::string(Pa_GetErrorText(rv)));
        }
    }
}