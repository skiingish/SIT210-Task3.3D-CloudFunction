/*
 * Project cloudFunction
 * Description: Listens to a particle located in Deakin's Riot lab which publishes a wave and pat event
 *              it then flashes 
 * Author: Sean Corcoran 
 * Date: 30/04/20 
 */

int led = D7;   // <- Pin 7 or onboard pin
String aString; // <- used to hold the event that was picked up by the subscribe
String bString; // <- used to hold the data was sent in the event

void setup()
{
  //deskin
  Particle.variable("eventRead", aString);
  Particle.variable("dataRead", bString);
  //set pinmode to out, and write low to start
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  //subscribe to the Deakin Photon, and use the handler function to take are of a incoming event
  Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", myHandler, ALL_DEVICES);
}

void loop()
{
  // no need for the loop here
}

void myHandler(String event, String data)
{
  //used to publish it's own events when events are recived
  aString = event;
  bString = data;

  //if a wave happens then long blink the led 3 times
  if (data == "wave")
  {
    //publish if a wave was picked up
    Particle.publish("whats_data_saying?", bString, 60, PRIVATE);
    digitalWrite(led, HIGH);
    delay(3000);
    digitalWrite(led, LOW);
    delay(3000);
    digitalWrite(led, HIGH);
    delay(3000);
    digitalWrite(led, LOW);
    delay(3000);
    digitalWrite(led, HIGH);
    delay(3000);
    digitalWrite(led, LOW);
  }
  // if pat is published then quickly flash the LED 10 times
  if (data == "pat")
  {
    //publish if a pat was picked up
    Particle.publish("whats_data_saying?", bString, 60, PRIVATE);
    for (int x = 0; x < 10; x++)
    {
      digitalWrite(led, HIGH);
      delay(200);
      digitalWrite(led, LOW);
      delay(200);
    }
  }
}