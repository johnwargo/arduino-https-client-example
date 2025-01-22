# Arduino HTTPS Client Example

A simple Arduino sketch for the ESP32 (an Espressif device) that securely connects to a remote server using Wi-Fi and TLS (HTTPS). 

## Background

I'm working on an Adruino project that requires the ability to connect to a remote server to retrieve some data. In today's environment where security is paramount, the server I connected to (and likely any server you connected to) secures its connection using Transport Layer Security ([TLS](https://en.wikipedia.org/wiki/Transport_Layer_Security)). TLS is used in HTTPS requests to secure the connection.

## Target Server





## Configuring the Sketch



rename `constants.h.rename` to `constants.h`

Modify the renamed file, populating the two `#define` statements with the Wi-Fi network name (`ssid`) and password

```c
#define WIFI_SSID ""
#define WIFI_PSWD ""
```

When done, your file will look something like this:

```c
#define WIFI_SSID "myNetwork"
#define WIFI_PSWD "Some Complicated Wi-Fi Password"
```

with, of course,  your network name and password in there except for the ones I made up.



## Capturing the Certificate





## Runtime





```text
Connecting to MyNetwork:
..........
Wi-Fi connected
IP address: 192.168.86.82

[HTTPS] begin...
[HTTPS] GET...
[HTTPS] GET... code: 200
["Proident sint ullamco ham ut.  Venison capicola jerky beef short loin aliqua.  Beef ribs cupidatat magna, jerky voluptate bresaola occaecat ullamco shank proident minim fatback salami.  Occaecat spare ribs venison enim.  Ham tenderloin eu est sirloin."]

Waiting 30 seconds...
```






***

If this code helps you, please consider buying me a coffee.

<a href="https://www.buymeacoffee.com/johnwargo" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>