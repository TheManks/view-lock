# Compilation

Compilation:
```
mkdir bin
make compile
```
Upload:
```
make upload
```

# Dependencies
Arduino libraries:
- Stepper
- WiFiNINA

# Secrets

In order to connect to your network add a file, `secrets.h` that is as follows:
```
#pragma once

#define LOCK_SSID "MY-SSID"
#define LOCK_PASS "MY-PASS"
#define LOCK_PORT 9999
```
