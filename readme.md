# it4-em-ampel
Umsetzungen der Projektanforderungen für ein Ampelsystem auf dem Atmega328p geschrieben in C unter Verwendung der AVR Libc und der AVR-gcc toolchain. Als Umgebung wird PlatformIO in Vscode verwendet.


## Projektstruktur
* Dieses Repo enthält drei Projekte:
    * Verkehrssystem
    * Leitsystem
    * pc-interface
* Es kann zwischen dem pio-envs "Verkehrssystem" und "Leitsystem" ausgewählt werden.

## Verkehrssystem
### Pinout
| Atmega ports | Pro micro PIN | IO        |
| ------------ | ------------- | --------- |
| PB0          | 8             | HS grün   |
| PB1          | 9             | HS gelb   |
| PD4          | 4             | HS rot    |
| PD5          | 5             | NS grün   |
| PD6          | 6             | NS gelb   |
| PD7          | 7             | NS rot    |
| -            | -             | FG grün   |
| -            | -             | FG rot    |
| PD2 (INT0)   | 2             | FG taster |
| PD3 (INT1)   | 3             | NS taster |
| PB2          | 10            | SPI SS    |
| PB3          | 11            | SPI MOSI  |
| PB4          | 12            | SPI MISO  |
| PB5          | 13            | SPI CLK   |

### Zustände
![](assets/2022-01-02-17-10-10.png)

# Leitsystem
<!-- todo @Emergency1999 -->