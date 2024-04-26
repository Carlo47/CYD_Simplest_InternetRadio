/**
 * Program      CYD_Simplest_Internetradio.cpp
 * 
 * Author       2024-04-26 Charles Geiser (www.dodeka.ch)
 * 
 * Purpose      Shows how to implement an internet radio with the CYD (Cheap Yellow Display)
 * 
 * Remarks      - Output through the internal DAC of the ESP32 
 *              - The only external component is an 8 Ohm loudspeaker on spkr-pins of the CYD
 *              - No user interface (no display, no touch, no volume control)
 * 
 * Libraries    - AudioTools (Phil Schatzmann)
 *              - CodecMP3Helix
 * 
 * References   https://github.com/pschatzmann/arduino-audio-tools/blob/main/examples/ 
 **/
 
#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"

ICYStream url("ssid", "password");                   // Your WiFi SSID and password
AnalogAudioStream out; 
EncodedAudioStream dec(&out, new MP3DecoderHelix()); // decode stream an route it to the esp32 analog stream
StreamCopy copier(dec, url);                         // copies mp3-stream from url to the decoder


void setup(void) 
{   
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // configure the analog output
  AnalogConfigESP32 config = out.defaultConfig(TX_MODE);   // use ESP32 DAC channel on GPIO_NUM_26
 
  url.begin("http://stream.srg-ssr.ch/m/rsc_de/mp3_128","audio/mp3");  // start reading the mp3-stream from url
  dec.begin();                                                         // start the decoder
  out.begin(config);                                                   // start the output stream
}

 
void loop() 
{
  copier.copy();
}