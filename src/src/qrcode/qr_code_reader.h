#include <ESP32QRCodeReader.h>
#include <string>

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);
boolean qrDone = false;
std::string qrCodeText = "";

void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;

  while (true)
  {
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        qrCodeText = (const char *)qrCodeData.payload;
        if (qrCodeText.find("WIFI:") == 0)
        {
          qrDone = true;
          vTaskDelete(NULL);
        }
        else
        {
          Serial.printf("Non-WiFi payload: %s\r\n", (const char *)qrCodeData.payload);
        }
      }
      else
      {
        Serial.printf("Invalid payload: %s\r\n", (const char *)qrCodeData.payload);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

std::string ReadWifiQrCode()
{
  reader.setup();

  Serial.println("Setup QRCode Reader");

  reader.beginOnCore(1);

  Serial.println("Begin on Core 1");

  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);

  while (!qrDone)
  {
    delay(100);
  }
  reader.end();
  return qrCodeText;
}
