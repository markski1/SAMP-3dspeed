# SAMP-3dspeed
3dspeed is a 3d speedometer for samp of simple implementation.

## Instalation

To install, simply download [3dspeed.inc](3dspeed.inc) and include it in the gamemode.

The speedometer will automatically appear and disappear as players enter and exit vehicles.

### Configuration
The following lines must be placed above the `#include <3dspeed>` line.
- `#define TDSPEED_SPANISH` if you wish the speedometer to show spanish text.
- `#define TDSPEED_MPH` if you wish the speedometer to say MPH instead of KMH.
- `#define TDSPEED_HIDENAME` if yoou wish the speedometer to not include the vehicle's name.

<br>

## Functions

3dspeed only implements one function

#### Update3DSpeedometer(playerid, speed, fuel)

Call this function when you wish to update it's contents

`speed` must be an integer containing the vehicle's speed.
`fuel`can be an integer containing the vehicle's fuel count. Use -1 or completely skip the parameter to hide that line.

## Callbacks

3dspeed implements no callbacks.
