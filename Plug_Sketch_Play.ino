#define button 4     // connect button to D4
 
int button_state = 0;         // variable for reading the pushbutton status
 
void setup() {
    Serial.begin(9600);
    // initialize the pushbutton pin as an input:
    pinMode(button, INPUT);
}
 
void loop(){
    // read the state of the pushbutton value:
    button_state = digitalRead(button);
 
    if (button_state == HIGH) {
        // turn LED on:
        Serial.println("Button pressed!");
    }
delay(50);
}