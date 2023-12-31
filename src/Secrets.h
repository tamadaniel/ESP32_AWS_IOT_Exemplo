#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "Mqtt_exemplo"                         //change this
 
const char WIFI_SSID[] = "Tamashiro_2.4G";               //change this
const char WIFI_PASSWORD[] = "39362669net";           //change this
const char AWS_IOT_ENDPOINT[] = "ai6mojv4ox3x5-ats.iot.us-east-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVANOVZMxA5ocPJNf/dNgfyxNkZa0ZMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzEyMjcxNjQ4
MDdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC4v92gCXz1bvVTcIGt
pUA9XJmp87oKi5xXEDlzrAldgXEPH2kzWja+UebtFZycOc7txCvD5MesDi5vhQsc
YVDJzyDhw2cJdGtRZJenTPKlPRx5A6I0YB347kraBwNDX/ZKImYNpnJlrdrUALqT
m/GvS17qqHOryRbKMYCZHCyw+u74HxG2Umg2ZLuEGybQ9/WDDGzLytlUQZ2rNOQS
DnDHZDIMOJHUrHXFAvTUwjNByEiEZWTqW3X9yFYbKjx3p6qtp2A29s8EnxutuDNK
DSB2hnpuUGw50AkPSqvxhwW56YAIWgwUkQ/32KcbzqgBGjTTu96r5KUk0iMHb2JE
NpDZAgMBAAGjYDBeMB8GA1UdIwQYMBaAFFEB/micQ/DiSaCGeiqgTruNlU2tMB0G
A1UdDgQWBBTHjnW4NeGl05HBmPqZUNUiYpJhETAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAagW3z2iI9MFf+kVTugoAwhP0
+lG0nIIwbKvAjJi4BnG+tb4tgGZT8VZTXOplZv+WnE5hFs5RNmhHpgwYXATptVSN
Kg+xud9Pd+A5X/wc6QPfDjwwRYSMSQcBAhWpQKKqiaDninNOEiH2eVI9HKlWRhju
arjHMgaCYUol9Ewz7i40+jNJnlIP+3GSOIFhjBAjm24BL60MklHH6YSJrR8FATDv
L/oXIYnejVL+oEK+WxH+U+e+v7j5ZISZD6jx/knqhWygCoRHzsx1mNiWOELZcp6V
XL0rbfbnQ70F6irdsDQPZwE0z4mixqAGvNQdRPbxwkP0V8QKAKcdmfJ1b3g4yg==
-----END CERTIFICATE-----

 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAuL/doAl89W71U3CBraVAPVyZqfO6CoucVxA5c6wJXYFxDx9p
M1o2vlHm7RWcnDnO7cQrw+THrA4ub4ULHGFQyc8g4cNnCXRrUWSXp0zypT0ceQOi
NGAd+O5K2gcDQ1/2SiJmDaZyZa3a1AC6k5vxr0te6qhzq8kWyjGAmRwssPru+B8R
tlJoNmS7hBsm0Pf1gwxsy8rZVEGdqzTkEg5wx2QyDDiR1Kx1xQL01MIzQchIhGVk
6lt1/chWGyo8d6eqradgNvbPBJ8brbgzSg0gdoZ6blBsOdAJD0qr8YcFuemACFoM
FJEP99inG86oARo007veq+SlJNIjB29iRDaQ2QIDAQABAoIBAQC1iSpv0ALudAox
5BI4m3FlGjGQEwKSzB5iWnnplHlbXQ7IClhn8lRqbLYZ7quFwzP25FUQ1yPwh7rP
MA774w/sTVAFJul/G9s8DjkKVozzGvp4Wr6u8mdhLF12oX9uW8P5kpVvAkfUa6Hj
wZeT5Z71XX013TJT8XMoWL4BNPMhLrPXW//BawOeCjbpInZpZmope2YO1i2os0A8
+qRzpRp98hYEH+Vtt4wZHHijz0WquaT3GkMGa2eMOhgXvsuW2bhB4Y0ZXxQWccF8
ulpJgu/6ChEH5dsCgH5hhCvdPOytiV9bSd1PJ6yOjSLQcmaSvf+ZSSEILknNG3vJ
mC5KeYCVAoGBAPAZnxmf7JQ9zfiIU7y6g3cMuJYK+scX9RX6a3KaKFA1KHmYFfdH
+kIOrW0lE/eWZl3itq84lBNhpulYpLlejG+sIFyE6SVIgQMDg6UlYF6kPCDBpfQv
03L8tvEjGkteJ4Qe2ZVYx75sWyfqT+eyZmo6ieUlBut4DYlMgXaokWTTAoGBAMT7
5OkVONO3ZuYUlWcG+cv+YqEEfvjpwV2UMVdNMIyNnp1++/YRRA7Xoh2uxEEr3T+s
Tb0fJIobOkP2KWHbkR5osTVyfKolbMnaEKdlKXMeJMuDMQ3uiPGsHUyAPhbwNGgc
PPrivabtJUtldLipi2WIPtVr6n+FozdM6npoVhgjAoGAXcuEjbwd7aNfTVHkdHvg
U6eSjHrpkNFZGybixrhWO08o6qdxHVLu/tNBCLxNWpFUmCSy/Sx7HD8vt0S7xPac
oht54OrDMZ9rVsQOr3s0dIRwQNOlgwkT732t8fGmmf7ELSboFSHDli46RhOQ95CH
1cPcjrmyRFZ340UR5krf0aUCgYEAosa0ppdO2kUX1tDzlKuDCDsyLXSVqAMiMr4e
99FlaQAuLl+cvf4Oi2VNJdIhgulIbzFnG/z8KNPPFhH4qFDUXpiMt2nf8onyl+qH
EIzb77DdHv9OLgELUQm1PF5M8I+V/uI20etEZQhaZS91gJM6CbDIm3wNz0sTUMNS
j8xgOJkCgYEAy2VuEb5JEJy6YePwtX7w4SMM5oHNdpKVrwpWMHeUW7SVpbqF5B/B
auHj6GPnSx7b0b2W1udwHdaXJTezDEKWZj32ZidK0kd42x/tLkRf0sPI1B8QccFO
YEQdjh6QG3Uao6NhV8Uwisz4ytbZHDO10Hqt+gcFvFlbwXNL4TTaDW0=
-----END RSA PRIVATE KEY-----
 
 
)KEY";
