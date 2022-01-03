# it4-em-ampel
Umsetzungen der Projektanforderungen für ein Ampelsystem auf dem Atmega328p geschrieben in C unter Verwendung der AVR Libc und der AVR-gcc toolchain. Als Umgebung wird PlatformIO in Vscode verwendet.


## Projektstruktur
* Dieses Repo enthält drei Projekte:
    * verkehrssystem
    * leitsystem
    * pc-interface

## Verkehrssystem
### Pinout
| Atmega ports | Pro micro PIN | IO        | Farben  |
| ------------ | ------------- | --------- | ------- |
| PB0          | 8             | HS grün   |         |
| PB1          | 9             | HS gelb   |         |
| PD4          | 4             | HS rot    |         |
| PD5          | 5             | NS grün   |         |
| PD6          | 6             | NS gelb   |         |
| PD7          | 7             | NS rot    |         |
| -            | -             | FG grün   |         |
| -            | -             | FG rot    |         |
| PD2 (INT0)   | 2             | FG taster |         |
| PD3 (INT1)   | 3             | NS taster |         |
| PB2          | 10            | SPI SS    | lila    |
| PB3          | 11            | SPI MOSI  | grau    |
| PB4          | 12            | SPI MISO  | weiß    |
| PB5          | 13            | SPI CLK   | schwarz |

### Zustände
![](assets/2022-01-02-17-10-10.png)

# Leitsystem
### Pinout
| Atmega ports | Pro micro PIN | IO       | Farben  |
| ------------ | ------------- | -------- | ------- |
| PB2          | 10            | SPI SS   | lila    |
| PB3          | 11            | SPI MOSI | grau    |
| PB4          | 12            | SPI MISO | weiß    |
| PB5          | 13            | SPI CLK  | schwarz |
<!-- todo @Emergency1999 -->