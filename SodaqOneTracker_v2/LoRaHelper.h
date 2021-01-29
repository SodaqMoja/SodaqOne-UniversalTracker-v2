#ifndef _LORAHELPER_h
#define _LORAHELPER_h

#include "Arduino.h"
#include "Sodaq_RN2483.h"

#define LORA_MAX_PACKET_LENGTH 250
#define LORA_MAX_RETRANSMISSIONS 3
#define LORA_MIN_RETRASMISSION_BACKOFF_SEC 10
#define LORA_RETRANSMISSION_ATTEMPTS_REPLENISH_AFTER_TRANSMIT_SEC 10 * 60

class LoRaHelper
{
public:
    LoRaHelper();

    void setDiag(Stream& stream) { _diagStream = &stream; };
    void init(Sodaq_RN2483& rn2483, uint32_t(*getNow)());
    void setKeys(const char* devAddrOrEUI, const char* appSKeyOrEUI, const char* nwSKeyOrAppKey) {
        _devAddrOrEUI = devAddrOrEUI;
        _appSKeyOrEUI = appSKeyOrEUI;
        _nwSKeyOrAppKey = nwSKeyOrAppKey;
    };
    void setOtaaOn(bool on) { _isOtaaOn = on; };
    bool isOtaaOn() { return _isOtaaOn; };

    void setAdrOn(bool on) { _isAdrOn = on; };
    bool isAdrOn() { return _isAdrOn; };

    void setAckOn(bool on) { _isAckOn = on; };
    bool isAckOn() { return _isAckOn; };

    void setReconnectOnTransmissionOn(bool on) { _isReconnectOnTransmissionOn = on; };
    bool isReconnectOnTransmissionOn() { return _isReconnectOnTransmissionOn; };

    void setDefaultLoRaPort(uint8_t port) { _defaultLoRaPort = port; };
    uint8_t getDefaultLoRaPort() { return _defaultLoRaPort; }

    void setRepeatTransmissionCount(uint8_t count) { _repeatTransmissionCount = count; };
    uint8_t getRepeatTransmissionCount() { return _repeatTransmissionCount; };

    void setSpreadingFactor(uint8_t spreadingFactor) { _spreadingFactor = spreadingFactor; };
    void setPowerIndex(uint8_t powerIndex) { _powerIndex = powerIndex; };
    void setActive(bool on);
    bool isInitialized() { return _isInitialized; };
    uint8_t getHWEUI(uint8_t* hweui, uint8_t size);
    bool join();
    uint8_t transmit(uint8_t* buffer, uint8_t size, int16_t overrideLoRaPort = -1);
    void extendSleep();
    void loopHandler();
private:
    Stream* _diagStream;
    Sodaq_RN2483* _rn2483;
    const char* _devAddrOrEUI;
    const char* _appSKeyOrEUI;
    const char* _nwSKeyOrAppKey;
    bool _isOtaaOn;
    bool _isAdrOn;
    bool _isAckOn;
    bool _isReconnectOnTransmissionOn;
    uint8_t _defaultLoRaPort;
    uint8_t _repeatTransmissionCount;
    uint8_t _spreadingFactor;
    uint8_t _powerIndex;
    bool _isInitialized;
    int8_t _transmissionAttemptsRemaining;
    bool _isRetransmissionPending;
    uint8_t _retransmissionPacketBuffer[LORA_MAX_PACKET_LENGTH];
    uint8_t _retransmissionPacketSize;
    int16_t _retransmissionOverrideLoRaPort;
    uint32_t _lastTransmissionAttemptTimestamp;
    uint32_t (*_getNow)();

    bool convertAndCheckHexArray(uint8_t* result, const char* hex, size_t resultSize);
    bool joinAbp();
    bool joinOtaa();
    void retransmissionUpdateOnSuccess();
    void retransmissionUpdateOnFailure();
};

extern LoRaHelper LoRa;

#endif

