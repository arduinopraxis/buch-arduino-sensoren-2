// Kompass mit LED-Anzeige
// Datei: arduino-sensoren-2-kap6-kompass-led.ino


/*****************************************************************************/	
//	Function:	 Get the Geographic direction of the X-axis.
//				If X-axis points to the North, it is 0 degree.
//				If X-axis points to the East, it is 90 degrees.
//				If X-axis points to the South, it is 180 degrees.
//				If X-axis points to the West, it is 270 degrees.
//  Hardware:   Grove - 3-Axis Digital Compass
//	Arduino IDE: Arduino-1.0
//	Author:	 Frankie.Chu		
//	Date: 	 Jan 10,2013
//	Version: v1.0
//	by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*******************************************************************************/

#include <Wire.h>
#include <HMC5883L.h>

// Kompass Objekt
HMC5883L compass;
// Fehler
int error = 0;

// Wert Winkel
float headingDegrees;

// LED-Pins
int PinLED1 = 2;
int PinLED2 = 3;
int PinLED3 = 4;
int PinLED4 = 5;
int PinLED5 = 6;
int PinLED6 = 7;
int PinLED7 = 8;
int PinLED8 = 9;


void setup()
{
  // Ausgänge LED
  pinMode(PinLED1, OUTPUT);
  pinMode(PinLED2, OUTPUT);
  pinMode(PinLED3, OUTPUT);
  pinMode(PinLED4, OUTPUT);
  pinMode(PinLED5, OUTPUT);
  pinMode(PinLED6, OUTPUT);
  pinMode(PinLED7, OUTPUT);
  pinMode(PinLED8, OUTPUT);
  
  // Start serielle Schnittstelle
  Serial.begin(9600);

  Serial.println("Starting the I2C interface.");
  Wire.begin(); // Start the I2C interface.

  Serial.println("Constructing new HMC5883L");
    
  Serial.println("Setting scale to +/- 1.3 Ga");
  error = compass.setScale(1.3); // Set the scale of the compass.
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.getErrorText(error));
  
  Serial.println("Setting measurement mode to continous.");
  error = compass.setMeasurementMode(MEASUREMENT_CONTINUOUS); // Set the measurement mode to Continuous
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.getErrorText(error));
}


void loop()
{
  // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.readRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.readScaledAxis();
  
  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -2��37' which is -2.617 Degrees, or (which we need) -0.0456752665 radians, I will use -0.0457
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = -0.0457;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Umrechnung Radiant zu Grad
  headingDegrees = heading * 180/M_PI; 

  // Output the data via the serial port.
  //Output(raw, scaled, heading, headingDegrees);

  // Ansteuerung LED
  SetLED(headingDegrees);

  // Ausgabe Winkel
  Serial.print(headingDegrees);
  Serial.println(" Grad");

  delay(100);
}


void SetLED(float headingDegrees)
{
  float w = headingDegrees;

  // Ausgabe des Winkels, Aktivierung der zugehörigen LED
  
  // LED1, 337.5 - 360, 0-22.5
  if (w > 337.5 &&  w < 361)
  {
    digitalWrite(PinLED1, HIGH);
  }
  else
  {
    digitalWrite(PinLED1, LOW);
  }
  if (w > 0 &&  w < 22.5)
  {
    digitalWrite(PinLED1, HIGH);
  }
   else
  {
    digitalWrite(PinLED1, LOW);
  }
  
  // LED2, 22.5-67.5
  if (w > 22.5 &&  w < 67.5)
  {
    digitalWrite(PinLED2, HIGH);
  }
  else
  {
    digitalWrite(PinLED2, LOW);
  } 
  
  // LED3, 67.5-112.5
  if (w > 67.5 &&  w < 112.5)
  {
    digitalWrite(PinLED3, HIGH);
  }
  else
  {
    digitalWrite(PinLED3, LOW);
  }
 
  // LED4, 112.5-157.5
  if (w > 112.5 &&  w < 157.5)
  {
    digitalWrite(PinLED4, HIGH);
  }
  else
  {
    digitalWrite(PinLED4, LOW);
  }
  
  // LED5, 157.5-202.5
  if (w > 157.5 &&  w < 202.5)
  {
    digitalWrite(PinLED5, HIGH);
  }
  else
  {
    digitalWrite(PinLED5, LOW);
  }

  // LED6, 202.5-247.5
  if (w > 202.5 &&  w < 247.5)
  {
    digitalWrite(PinLED6, HIGH);
  }
  else
  {
    digitalWrite(PinLED6, LOW);
  }

  // LED7, 247.5-292.5
  if (w > 247.5 &&  w < 292.5)
  {
    digitalWrite(PinLED7, HIGH);
  }
  else
  {
    digitalWrite(PinLED7, LOW);
  }

  // LED8, 292.5-337.5
  if (w > 292.5 &&  w < 337.5)
  {
    digitalWrite(PinLED8, HIGH);
  }
  else
  {
    digitalWrite(PinLED8, LOW);
  }    

}
  


