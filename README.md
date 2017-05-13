BlueLock

This is a project written in C for the Raspberry Pi.
The goal is to be able to have a keyless and automatic entry for my apartment.
When the Raspberry Pi detects my phone nearby via Bluetooth, it will automatically unlock the door to my apartment.
When the Raspberry Pi disconnects from my phone's Bluetooth, it will automatically lock the door.

sudo rfcomm connect 0 04:88;e2:7d:f5:47 1