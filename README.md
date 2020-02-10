# MRKS 3D Speedometer
3D Speedometer for SA-MP with a drag-and-drop implementation.

## Installation

### If you have y_hooks
Simply include the .inc right after including streamer, and everything will work by itself as if by magic.

### If you don't have y_hooks
Include the file right after including Streamer, then do the following:
- Call 'tdSpeedo_Connect(playerid)' at the beggining of OnPlayerConnect
- Call 'tdSpeedo_Disconnect(playerid)' at the beggining of OnPlayerDisconnect
- Call 'tdSpeedo_Update(playerid)' at the beggining of OnPlayerUpdate
- Enter the following code at the beggining of OnPlayerStateChange:
```
if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
		tdSpeedo_Toggle(playerid, 1);
	} else {
		tdSpeedo_Toggle(playerid, 0);
	}
 ```

## Custom implementation

By default, once installed, MRKS 3D Speedometer will work out of the box without any further scripting required. However, if desired, it is possible to give the script your own speed measurements, and even an optional "Fuel" value. (visible in the bottom screenshot below)

In order to do a custom implementation, do the following:

- If you're using y_hooks, at the beggining of the file, change AUTOMATIC_MODE from 1 to 0. This will let the script self-install on compilation, but won't automatically update it's measurements.
- At the top of your OnPlayerUpdate callback function, enter the following:
`tdSpeedo_Update(playerid, Speed, Fuel);`
(Speed must be a float, Fuel must be an integer)
If you wish to only enter a Fuel value but let the include measure speed by itself, enter "-1.0" instead of Speed.
If you wish to only enter your speed measurement and no Fuel indicator, then don't enter any, just use `tdSpeedo_Update(playerid, Speed)`

## TODO

Things I'd like to do with this:
- Add a way for scripters to provide more player-specific customization to their users, such as colours and sizes.
- ???

## Known bugs
- Unusable in vehicles too wide such as airplanes
- ???

## How does it look?

![](https://i.imgur.com/x7Ak5d5.png)
![](https://i.imgur.com/3Nu9jjv.png)
![](https://i.imgur.com/2mM29sd.png)
![](https://i.imgur.com/vhqG1Ky.png)
![](https://i.imgur.com/THGrFdv.png)

## How to collaborate
Just open a Pull Request with your code m8
