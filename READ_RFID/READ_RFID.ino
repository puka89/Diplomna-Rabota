int ID_tag[55];

int current_clock_state = 0;
int last_clock_state = 0;

static int RFID_clock = 4;
static int RFID_data = 5;
static int RFID_speed =6;
static int RFID_mode = 7;
static int RFID_modu = 8;

void setup() {
  Serial.begin(9600);
  pinMode(RFID_clock, INPUT_PULLUP);
  pinMode(RFID_data, INPUT_PULLUP);
  pinMode(RFID_speed, OUTPUT);
  pinMode(RFID_mode, OUTPUT);
  pinMode(RFID_modu, OUTPUT);
  
  digitalWrite(RFID_speed, LOW);
  digitalWrite(RFID_mode, LOW);
  digitalWrite(RFID_modu, HIGH);
}

void loop() {
  wait_header();

  int tag_counter;
  for(tag_counter = 0; tag_counter < 55; tag_counter++){
    last_clock_state = current_clock_state;
    current_clock_state = digitalRead(RFID_clock);

    if(last_clock_state == 0 && current_clock_state == 1){
      ID_tag[tag_counter] = digitalRead(RFID_data);
    }else {
      tag_counter--;
      continue;
    }
  }
  
  int print_counter;
  for(print_counter = 0; print_counter < 55; print_counter++){
    Serial.print(ID_tag[print_counter]);
  }
  Serial.println();
}

void wait_header(){
  int header_counter = 0, check_counter = 0;
  while(true){
    last_clock_state = current_clock_state;
    current_clock_state = digitalRead(RFID_clock);
    
    if(last_clock_state == 0 && current_clock_state == 1){
      if(digitalRead(RFID_data) == 1){
        check_counter++;
      } else {
        check_counter = 0;
      }
    }
    if(check_counter == 9) break;
  }
}
