#include <Arduino.h>
#include <driver/can.h>
#include <driver/gpio.h>

int gaz=0;
int speed=0;
int rpm=0;

void setup_can_driver() {
  can_general_config_t general_config {
    .mode = CAN_MODE_NORMAL,
    .tx_io = (gpio_num_t)GPIO_NUM_22,
    .rx_io = (gpio_num_t)GPIO_NUM_21,
    .clkout_io = (gpio_num_t)CAN_IO_UNUSED,
    .bus_off_io = (gpio_num_t)CAN_IO_UNUSED,
    .tx_queue_len = 0,
    .rx_queue_len = 65,
    .alerts_enabled = CAN_ALERT_ALL,
    .clkout_divider = 0
  };

  can_timing_config_t timing_config = CAN_TIMING_CONFIG_125KBITS();
  can_filter_config_t filter_config = CAN_FILTER_CONFIG_ACCEPT_ALL();

  esp_err_t error;
  error = can_driver_install(&general_config,&timing_config,&filter_config);

  if(error==ESP_OK) {
    Serial.println("Can driver installation OK");
  } else {
    Serial.println("Can driver installation NOK");
    return;
  };

  error = can_start();

  if(error==ESP_OK){
    Serial.println("Can Driver started");
  }else{
    Serial.println("Can Driver failed to start");
    return;
  }

}

void setup() {
  Serial.begin(115200);
  
  setup_can_driver();

  sleep(1);
  Serial.println(" > Setup Complete");
}



void loop() {

  can_message_t rx_frame;
  if(can_receive(&rx_frame,pdMS_TO_TICKS(1000))==ESP_OK){
    /**
    printf("from 0x%08X,DLC%d,Data",rx_frame.identifier,rx_frame.data_length_code);
    for(int i=0;i<rx_frame.data_length_code;i++){
      printf(" 0x%02X ", rx_frame.data[i]);
    }
    printf("\n");
    */

    if (rx_frame.identifier==0x00000080){
// 122 max
// 0x12 > 18
      if(rpm!=rx_frame.data[3]){
        //printf("Gaz: 0x%02X", rx_frame.data[4]);

        int currentRPM = 0;
        int currentSpeed = 0;
        //highByte(currentRPM) = rx_frame.data[2];
        //lowByte(currentRPM) = rx_frame.data[3];

        //currentRPM = (rx_frame.data[2] << 16) | (rx_frame.data[3] << 8);
        currentRPM = (rx_frame.data[2] << 8) | rx_frame.data[3];
        currentSpeed = (rx_frame.data[0] << 8) | rx_frame.data[1];
        //printf("RPM: 0x%02X%02X", rx_frame.data[2],rx_frame.data[3]);
        Serial.print("RPM: ");
        Serial.print(currentRPM);
        Serial.println(" ");
        rpm=rx_frame.data[3];

/**
        int readvalue = rx_frame.data[4];
        int outvalue = (readvalue*100)/122;
        Serial.print("Gaz: ");
        Serial.print(outvalue);
        Serial.print("%  ");
        gaz=rx_frame.data[4];

*/

      }

      



    }

    

  }
  
}