#ifndef TEKENGINE
#define TEKENGINE

//  global compilation flag configuring windows sdk headers
//  preventing inclusion of min and max macros clashing with <limits>
#define NOMINMAX 1

//  override byte to prevent clashes with <cstddef>
#define byte win_byte_override

#include <Windows.h> // gdi plus requires Windows.h
// ...includes for other windows header that may use byte...

//  Define min max macros required by GDI+ headers.
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#else
#error max macro is already defined
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#else
#error min macro is already defined
#endif

#include <gdiplus.h>

//  Undefine min max macros so they won't collide with <limits> header content.
#undef min
#undef max

//  Undefine byte macros so it won't collide with <cstddef> header content.
#undef byte
#include <Audioclient.h>
#include <Mmdeviceapi.h>
#include <assert.h>


class AudioManager {
public:
    void Initialize() {
        // Initialize COM
        CoInitializeEx(nullptr, COINIT_MULTITHREADED);

        // Create an audio client
        IMMDeviceEnumerator *pEnumerator = nullptr;
        IMMDevice *pDevice = nullptr;
        IAudioClient *pAudioClient = nullptr;

        HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
                                      (void **) &pEnumerator);
        assert(SUCCEEDED(hr));

        hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
        assert(SUCCEEDED(hr));

        hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void **) &pAudioClient);
        assert(SUCCEEDED(hr));

        // Set up audio format (e.g., 16-bit PCM, 44.1 kHz)
        WAVEFORMATEX* wfx = new WAVEFORMATEX;
        wfx->wFormatTag = WAVE_FORMAT_PCM; // PCM format
        wfx->nChannels = 2; // Stereo
        wfx->nSamplesPerSec = 44100; // 44.1 kHz
        wfx->wBitsPerSample = 16; // 16-bit
        wfx->nBlockAlign = (wfx->nChannels * wfx->wBitsPerSample) / 8;
        wfx->nAvgBytesPerSec = wfx->nSamplesPerSec * wfx->nBlockAlign;
        wfx->cbSize = 0; // No extra data

        // Initialize the audio client
        hr = pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_LOOPBACK, 0, 0, wfx, nullptr);
        assert(SUCCEEDED(hr));

        // Load your audio file (not shown here)
        // ...

        // Start audio playback (not shown here)
        // ...

        // Clean up
        pAudioClient->Release();
        pDevice->Release();
        pEnumerator->Release();

        delete wfx;

        CoUninitialize();
    }
};


#endif //TEKENGINE
