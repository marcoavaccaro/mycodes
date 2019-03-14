#include <sstream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 10; //In seconds
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
     

  Serial.println("");
  Serial.print("Escaneando Beacons ");
  
  std::stringstream ss; //nessa posição para zerar a cada loop
  //std::stringstream aux;
  //std::stringstream beaconfiltro;
  //beaconfiltro << "f3:f1:2b:01:15:67";
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  int count = foundDevices.getCount();
  for (int i = 0; i < count; i++)
  {  
    //if (i > 0) {
    //  ss << ";";
    //}
    BLEAdvertisedDevice d = foundDevices.getDevice(i);
    std::stringstream aux; //nessa posição para zerar sempre que receber um novo address
    aux << d.getAddress().toString();
    //Serial.println(aux.str().c_str());
    if(aux.str() == "f3:f1:2b:01:15:67" || aux.str() == "c5:a8:44:45:4d:43" || aux.str() == "ce:9b:2e:98:73:10"){ //aqui coloca os MAC dos beacons que quer filtrar
     ss << d.getAddress().toString() << "," << d.getRSSI() << "\n";
    }
  }
  Serial.println("\n");
  Serial.println(ss.str().c_str());
  //Serial.print("Devices Founded: ");
  //Serial.println(count);
  Serial.println("");
}