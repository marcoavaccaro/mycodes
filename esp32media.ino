#include <sstream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>


float scanReads = 0;
int scanTime = 10; //In seconds
float media = 0;
float totalDevices = 0;
BLEScan* pBLEScan;



class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      //Serial.printf(advertisedDevice.toString().c_str());
    }
};


void setup() {
  Serial.begin(115200);
  Serial.printf("Start BLE scan for %d seconds...\n", scanTime);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  Serial.println("setup end");


}

void loop() {

   Serial.println("Escaneando Beacons ");
   std::stringstream ss; //nessa posição para zerar a cada loop
   BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
   float count = foundDevices.getCount();
   for (int i = 0; i < count; i++)
   {  
     BLEAdvertisedDevice d = foundDevices.getDevice(i);
     std::stringstream aux; //nessa posição para zerar sempre que receber um novo address
     aux << d.getAddress().toString();
     //Serial.println(aux.str().c_str());
     //if(aux.str() == "c5:59:cc:ac:19:01"){ //aqui coloca o MAC dos beacons que quer filtrar
     ss << d.getAddress().toString() << "," << d.getRSSI() << "\n";
    }

   Serial.println("");
   Serial.println(ss.str().c_str());
   
   scanReads++;
   totalDevices = count + totalDevices;
   media = totalDevices / scanReads;

   Serial.printf("Devices encontrados: %.0f\n", count);
   Serial.printf("Total de Leituras Feitas %.0f\n", scanReads);
   Serial.printf("Media de devices encontrados com %d segundos de Scan: %.2f\n\n", scanTime, media);
   Serial.print("Aguardando nova leitura.");

   delay(250);
   Serial.print(".");
   delay(250);
   Serial.print(".");
   delay(250);
   Serial.print(".");
   delay(250);
   Serial.println(".");
   delay(250);

}