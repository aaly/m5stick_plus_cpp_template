#include <M5StickCPlus.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class IBeaconAdvertised: public BLEAdvertisedDeviceCallbacks {
  public:
    // Callback when BLE is detected
    void onResult(BLEAdvertisedDevice device) {
      if (!isIBeacon(device)) {
        return;
      }
      printIBeacon(device);
    }

  private:
    // iBeacon packet judgment
    bool isIBeacon(BLEAdvertisedDevice device) {
      if (device.getManufacturerData().length() < 25) {
        return false;
      }
      if (getCompanyId(device) != 0x004C) {
        return false;
      }
      if (getIBeaconHeader(device) != 0x1502) {
        return false;
      }
      return true;
    }

    // CompanyId acquisition
    unsigned short getCompanyId(BLEAdvertisedDevice device) {
      const unsigned short* pCompanyId = (const unsigned short*)&device
                                         .getManufacturerData()
                                         .c_str()[0];
      return *pCompanyId;
    }

    // Get iBeacon Header
    unsigned short getIBeaconHeader(BLEAdvertisedDevice device) {
      const unsigned short* pHeader = (const unsigned short*)&device
                                      .getManufacturerData()
                                      .c_str()[2];
      return *pHeader;
    }

    // Get UUID
    String getUuid(BLEAdvertisedDevice device) {
      const char* pUuid = &device.getManufacturerData().c_str()[4];
      char uuid[64] = {0};
      sprintf(
        uuid,
        "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
        pUuid[0], pUuid[1], pUuid[2], pUuid[3], pUuid[4], pUuid[5], pUuid[6], pUuid[7],
        pUuid[8], pUuid[9], pUuid[10], pUuid[11], pUuid[12], pUuid[13], pUuid[14], pUuid[15]
      );
      return String(uuid);
    }

    // Get TxPower
    signed char getTxPower(BLEAdvertisedDevice device) {
      const signed char* pTxPower = (const signed char*)&device
                                    .getManufacturerData()
                                    .c_str()[24];
      return *pTxPower;
    }

    // Serial output of iBeacon information
    void printIBeacon(BLEAdvertisedDevice device) {
      Serial.printf("addr:%s rssi:%d uuid:%s power:%d\r\n",
                    device.getAddress().toString().c_str(),
                    device.getRSSI(),
                    getUuid(device).c_str(),
                    *(signed char*)&device.getManufacturerData().c_str()[24]);
    }
};

void setup() {
  M5.begin();
  Serial.begin(115200);
  BLEDevice::init("");
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.print("Ready");
}

void loop() {
  M5.Lcd.print("start.");
  Serial.println("start.");
  BLEScan* scan = BLEDevice::getScan();
  scan->setAdvertisedDeviceCallbacks(new IBeaconAdvertised(), true);
  scan->setActiveScan(true);
  scan->start(60);
  Serial.println("complete.");
  M5.Lcd.print("complete.");
}
extern "C" void app_main()
{
    initArduino();
    M5.begin();

    setup();

    while(true) {
        loop();
    }
}