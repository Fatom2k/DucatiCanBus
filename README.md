# DucatiCanBus
Contains all information for ducatiCanBus hacking

## Documentation

### Can ID's and datas
| ID | interresting bytes | race chrono map msg
|----|--------------------|--------------------|
| CAN ID 080 | byte 1 & 2 Velocity | mapped to Analogue 3 |
| CAN ID 080 | byte 3 & 4 Speed | mapped to RPM |
| CAN ID 080 | byte 5 Throttle position | mapped to Analogue 1 |
| CAN ID 020 | byte 1 Engine temperature | mapped to Analogue 4 |
| CAN ID 300  |byte 3 & 4 Mileage | mapped to Analogue 2 |

## Sources

- https://pulsesecurity.co.nz/articles/ducati-can-bus
