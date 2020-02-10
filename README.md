# MRKS 3D Speedometer
3D Speedometer for SA-MP with a drag-and-drop implementation.

## Installation

If you have y_hooks, simply include the .inc and everything will work by itself as if by magic.

If you don't have y_hooks, then, besides from including the file you must:
- Call 'tdSpeedo_Connect(playerid)' at the beggining of OnPlayerConnect
- Call 'tdSpeedo_Disconnect(playerid)' at the beggining of OnPlayerDisconnect
- Call 'tdSpeedo_Update(playerid)' at the beggining of OnPlayerUpdate
- Call 'tdSpeedo_Toggle(playerid, 1)' at the beggining of OnPlayerStateChange if `(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)` is true.
- Call 'tdSpeedo_Toggle(playerid, 0)' at the beggining of OnPlayerStateChange as an "else" to the above statement.

## How does it look?

![](https://i.imgur.com/x7Ak5d5.png)
![](https://i.imgur.com/3Nu9jjv.png)
![](https://i.imgur.com/2mM29sd.png)
![](https://i.imgur.com/vhqG1Ky.png)

## How to collaborate
Just open a Pull Request with your code m8
