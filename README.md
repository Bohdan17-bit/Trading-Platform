# Trading-Platform
<p>
  <img src="https://img.shields.io/badge/Qt%20-5.15.2-brightgreen">
  <img src="https://img.shields.io/badge/C++-17-blue">
  <img src="https://img.shields.io/badge/MinGW-8.1.0-lightgrey">
  <img src="https://img.shields.io/badge/OpenSSL-1.1.1t-yellowgreen">
  <img src="https://img.shields.io/badge/SQLite-3.33.0-important">
  <img src="https://img.shields.io/badge/License-MIT-blueviolet">
</p>

## About
Desktop application that provides opportunities to work out trading strategies and analyze the situation on the cryptocurrency market in "online" mode using a demo account. 
All market data on available cryptocurrencies is received using the Poloniex API (Public Endpoints).

## Coming soon
Screenshots and gifs that represents of all functionality and features!

## How to develop the project further
1. Give this project a star.
2. Fork this repository.
3. Keep improving the project.


## OpenSSL
The OpenSSL library has been included to make and send API requests, various dlls have been added to the pro file:
<br>
~~~~~~~~~~pro
INCLUDEPATH += ../dlls/openssl_x32
INCLUDEPATH += ../dlls/openssl_x64
~~~~~~~~~~
How its looks like:
```
├── dlls
|   ├── openssl_x32
|     ├── libcrypto-1_1.dll
|     ├── libeay32.dll
|     ├── libgcc_s_dw2-1.dll
|     └── libssl-1_1.dll
|   ├── openssl_x64
|     ├── libcrypto-1_1-x64.dll
|     ├── libgcc_s_seh-1.dll
|     └── libssl-1_1-x64.dll
```
## Links
1. OpenSSL - https://www.openssl.org/source/
2. Poloniex API - https://docs.poloniex.com/
