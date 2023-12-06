#include <iostream>
#include "./libs/portaudio/include/portaudio.h"
#include "./libs/libsndfile/include/sndfile.h
"

#define FILENAME "./audio/victory.wav"

int main()
{
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    PaStream *stream;
    PaError err;

    // Open the WAV file for reading
    sndfile = sf_open(FILENAME, SFM_READ, &sfinfo);
    if (!sndfile)
    {
        std::cerr << "Error opening WAV file" << std::endl;
        return 1;
    }

    // Initialize PortAudio
    err = Pa_Initialize();
    if (err != paNoError)
    {
        std::cerr << "PortAudio initialization failed" << std::endl;
        sf_close(sndfile);
        return 1;
    }

    // Set up PortAudio stream parameters
    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = sfinfo.channels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    // Open PortAudio stream
    err = Pa_OpenStream(&stream, nullptr, &outputParameters, sfinfo.samplerate, paFramesPerBufferUnspecified, paNoFlag, nullptr, nullptr);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream opening failed" << std::endl;
        sf_close(sndfile);
        Pa_Terminate();
        return 1;
    }

    // Start the PortAudio stream
    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream starting failed" << std::endl;
        Pa_CloseStream(stream);
        sf_close(sndfile);
        Pa_Terminate();
        return 1;
    }

    // Read and play the audio data
    const int BUFFER_SIZE = 1024;
    float buffer[BUFFER_SIZE * sfinfo.channels];
    sf_count_t framesRead;

    while ((framesRead = sf_readf_float(sndfile, buffer, BUFFER_SIZE)) > 0)
    {
        err = Pa_WriteStream(stream, buffer, framesRead);
        if (err != paNoError)
        {
            std::cerr << "Error writing to PortAudio stream" << std::endl;
            break;
        }
    }

    // Stop and close the PortAudio stream
    err = Pa_StopStream(stream);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream stopping failed" << std::endl;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        std::cerr << "PortAudio stream closing failed" << std::endl;
    }

    // Terminate PortAudio and close the WAV file
    Pa_Terminate();
    sf_close(sndfile);

    return 0;
}
