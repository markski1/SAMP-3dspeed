# SAMP-3dspeed
3dspeed es un tacometro en 3D para samp de muy simple implementación.

## Instalacion

Para instalar esta libreria, simplemente descarga [3dspeed.inc](3dspeed.inc) e incluyelo en tu gamemode

### Configuración
Las siguientes lineas se agregan arriba de la linea `#include`.
- `#define TDSPEED_SPANISH` si deseas que el tacometro este en español.
- `#define TDSPEED_MPH` si deseas que el tacometro diga MPH en lugar de KMH.
- `#define TDSPEED_HIDENAME` si deseas que el tacometro no incluya el nombre del vehiculo.

<br>

## Funciones

3dspeed solo implementa una funcion

#### Update3DSpeedometer(playerid, speed, fuel)

Llama a esta funcion cada vez que desees actualizar los valores en el tacometro.

`speed` debe ser un numero entero que contenga la velocidad del vehiculo.
`fuel` debe ser un numero entero que contenga el combustible de el vehiculo. Si pones -1 o no incluyes el parametro, esa linea no se mostrara.

## Callbacks

3dspeed no implementa callbacks.
