#include "libs/portaudio/include/portaudio.h"
#include <iostream>
#include <cmath>

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)

// Function to generate a simple sine wave
static int paCallback(const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo *timeInfo,
                      PaStreamCallbackFlags statusFlags,
                      void *userData)
{
    float *out = (float *)outputBuffer;
    const double TWO_PI = 6.28318530718;
    static double phase = 0.0;

    for (unsigned int i = 0; i < framesPerBuffer; i++)
    {
        *out++ = static_cast<float>(0.5 * std::sin(phase)); // Left channel
        *out++ = static_cast<float>(0.5 * std::sin(phase)); // Right channel
        phase += (TWO_PI * 440.0) / SAMPLE_RATE;
        if (phase > TWO_PI)
            phase -= TWO_PI;
    }

    return paContinue;
}

int main()
{
    PaError err;
    PaStream *stream;

    err = Pa_Initialize();
    if (err != paNoError)
    {
        std::cerr << "PortAudio initialization failed: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, SAMPLE_RATE,
                               FRAMES_PER_BUFFER, paCallback, nullptr);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream opening failed: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream starting failed: " << Pa_GetErrorText(err) << std::endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    err = Pa_StopStream(stream);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream stopping failed: " << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream closing failed: " << Pa_GetErrorText(err) << std::endl;
    }

    Pa_Terminate();

    return 0;
}