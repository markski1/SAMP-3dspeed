//
// 3D Speedometer 0.1 by Markski
// mrks.cf - Markski#7243 - immarkski@pm.me
//
// Installation
//
//    - If you have y_hooks, simply include this file and everything will work by itself.
//
//    - If you don't have y_hooks, then, besides from including the file you must:
//       - Call 'tdSpeedo_Connect(playerid)' at the beggining of OnPlayerConnect
//       - Call 'tdSpeedo_Disconnect(playerid)' at the beggining of OnPlayerDisconnect
//       - Call 'tdSpeedo_Update(playerid)' at the beggining of OnPlayerUpdate
//       - Call 'tdSpeedo_Toggle(playerid, 1)' at the beggining of OnPlayerStateChange if `(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)` is true.
//
//    TODO:
//       - Implement "Manual" mode of operation to let scripters implement their own speed measurements.
//       - Implement player-specific settable variables in order to let scripters offer their players a higher degree of customization.
//       - ???
//

// System constants, do not touch!

#define SPEED_KMH              0
#define SPEED_MPH              1

/* Configuration
   - Feel free to these values according to your preferences.
*/

// Color of the 3D Speedometer
#define SPEEDOMETER_COLOR      0xFFFFFFFF

// Speed unit to use, MPH or KMH
#define SPEEDOMETER_SPEED      SPEED_KMH

enum SpeedometerComponents {
   Name,
   Status,
   Speed,
   Enabled
}

static gSpeedPlayer[MAX_PLAYERS][SpeedometerComponents];

static gTickCount[MAX_PLAYERS];

static gVehicleNames[][] = {
   "Landstalker",
   "Bravura",
   "Buffalo",
   "Linerunner",
   "Perenniel",
   "Sentinel",
   "Dumper",
   "Firetruck",
   "Trashmaster",
   "Stretch",
   "Manana",
   "Infernus",
   "Voodoo",
   "Pony",
   "Mule",
   "Cheetah",
   "Ambulance",
   "Leviathan",
   "Moonbeam",
   "Esperanto",
   "Taxi",
   "Washington",
   "Bobcat",
   "Mr Whoopee",
   "BF Injection",
   "Hunter",
   "Premier",
   "Enforcer",
   "Securicar",
   "Banshee",
   "Predator",
   "Bus",
   "Rhino",
   "Barracks",
   "Hotknife",
   "Trailer",
   "Previon",
   "Coach",
   "Cabbie",
   "Stallion",
   "Rumpo",
   "RC Bandit",
   "Romero",
   "Packer",
   "Monster Truck",
   "Admiral",
   "Squalo",
   "Seasparrow",
   "Pizzaboy",
   "Tram",
   "Trailer",
   "Turismo",
   "Speeder",
   "Reefer",
   "Tropic",
   "Flatbed",
   "Yankee",
   "Caddy",
   "Solair",
   "Berkley's RC Van",
   "Skimmer",
   "PCJ-600",
   "Faggio",
   "Freeway",
   "RC Baron",
   "RC Raider",
   "Glendale",
   "Oceanic",
   "Sanchez",
   "Sparrow",
   "Patriot",
   "Quad",
   "Coastguard",
   "Dinghy",
   "Hermes",
   "Sabre",
   "Rustler",
   "ZR-350",
   "Walton",
   "Regina",
   "Comet",
   "BMX",
   "Burrito",
   "Camper",
   "Marquis",
   "Baggage",
   "Dozer",
   "Maverick",
   "News Chopper",
   "Rancher",
   "FBI Rancher",
   "Virgo",
   "Greenwood",
   "Jetmax",
   "Hotring",
   "Sandking",
   "Blista Compact",
   "Police Maverick",
   "Boxville",
   "Benson",
   "Mesa",
   "RC Goblin",
   "Hotring Racer",
   "Hotring Racer",
   "Bloodring Banger",
   "Rancher",
   "Super GT",
   "Elegant",
   "Journey",
   "Bike",
   "Mountain Bike",
   "Beagle",
   "Cropdust",
   "Stunt Plane",
   "Tanker",
   "RoadTrain",
   "Nebula",
   "Majestic",
   "Buccaneer",
   "Shamal",
   "Hydra",
   "FCR-900",
   "NRG-500",
   "HPV1000",
   "Cement Truck",
   "Tow Truck",
   "Fortune",
   "Cadrona",
   "FBI Truck",
   "Willard",
   "Forklift",
   "Tractor",
   "Combine",
   "Feltzer",
   "Remington",
   "Slamvan",
   "Blade",
   "Freight",
   "Streak",
   "Vortex",
   "Vincent",
   "Bullet",
   "Clover",
   "Sadler",
   "Firetruck",
   "Hustler",
   "Intruder",
   "Primo",
   "Cargobob",
   "Tampa",
   "Sunrise",
   "Merit",
   "Utility",
   "Nevada",
   "Yosemite",
   "Windsor",
   "Monster Truck",
   "Monster Truck",
   "Uranus",
   "Jester",
   "Sultan",
   "Stratum",
   "Elegy",
   "Raindance",
   "RC Tiger",
   "Flash",
   "Tahoma",
   "Savanna",
   "Bandito",
   "Freight",
   "Trailer",
   "Kart",
   "Mower",
   "Duneride",
   "Sweeper",
   "Broadway",
   "Tornado",
   "AT-400",
   "DFT-30",
   "Huntley",
   "Stafford",
   "BF-400",
   "Newsvan",
   "Tug",
   "Trailer",
   "Emperor",
   "Wayfarer",
   "Euros",
   "Hotdog",
   "Club",
   "Trailer",
   "Trailer",
   "Andromada",
   "Dodo",
   "RC Cam",
   "Launch",
   "Police Car (LSPD)",
   "Police Car (SFPD)",
   "Police Car (LVPD)",
   "Police Ranger",
   "Picador",
   "S.W.A.T. Van",
   "Alpha",
   "Phoenix",
   "Glendale",
   "Sadler",
   "Luggage Trailer",
   "Luggage Trailer",
   "Stair Trailer",
   "Boxville",
   "Farm Plow",
   "Utility Trailer"
};

/* Functions */

tdSpeedo_Connect(playerid) {
   for (new i = 0; i < _:SpeedometerComponents; i++) {
      gSpeedPlayer[playerid][SpeedometerComponents:i] = INVALID_OBJECT_ID;
   }
   gSpeedPlayer[playerid][Enabled] = 0;
   gTickCount[playerid] = 0;
}

tdSpeedo_Disconnect(playerid) {
   if(gSpeedPlayer[playerid][Name] != INVALID_OBJECT_ID) {
      DestroyDynamicObject(gSpeedPlayer[playerid][Name]);
      DestroyDynamicObject(gSpeedPlayer[playerid][Status]);
      DestroyDynamicObject(gSpeedPlayer[playerid][Speed]);
   }
}

tdSpeedo_Update(playerid) {
   if (!gSpeedPlayer[playerid][Enabled]) return 1;
   gTickCount[playerid]++
   if (gTickCount[playerid] < 5) return 1;
   gTickCount[playerid] = 0;
   if (!IsPlayerInAnyVehicle(playerid)) {
      tdSpeedo_Toggle(playerid, 0);
      return 1;
   } else if (!IsPlayerNPC(playerid)) {
      new vehid = GetPlayerVehicleID(playerid);
      new Float:pvX, Float:pvY, Float:pvZ, Float:vhp, Float:velocity;
      GetVehicleHealth(vehid, vhp);
      GetVehicleVelocity(vehid, pvX, pvY, pvZ);
      velocity = 120.0*(pvX*pvX+pvY*pvY);
      vhp = (((vhp - 250.0) / 750.0) * 100.0);
      new speedText[48];
      new statusText[48];
      format(statusText, 48, "Health: %3.0f%%", vhp);
      #if SPEEDOMETER_SPEED == SPEED_KMH
         format(speedText, 48, "%.0f KMH", velocity);
      #else
         format(speedText, 48, "%.0f MPH", velocity * 1.6);
      #endif
      new modelid = GetVehicleModel(vehid);
      SetDynamicObjectMaterialText(gSpeedPlayer[playerid][Name], 0, gVehicleNames[modelid-400], OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, true, SPEEDOMETER_COLOR, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
      SetDynamicObjectMaterialText(gSpeedPlayer[playerid][Status], 0, statusText, OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, false, SPEEDOMETER_COLOR, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
      SetDynamicObjectMaterialText(gSpeedPlayer[playerid][Speed], 0, speedText, OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, false, SPEEDOMETER_COLOR, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
   }
   return 1;
}

tdSpeedo_Toggle(playerid, activate) {
   if (activate) {
      if (gSpeedPlayer[playerid][Enabled]) {
         return 1;
      }
      new vid = GetPlayerVehicleID(playerid);
      new vmod = GetVehicleModel(vid);
      gSpeedPlayer[playerid][Name] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
      gSpeedPlayer[playerid][Status] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
      gSpeedPlayer[playerid][Speed] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
      new Float:vX,Float:vY,Float:vZ;
      GetVehicleModelInfo(vmod, VEHICLE_MODEL_INFO_SIZE, vX, vY, vZ);
      if (vX < 1.5) {
         vX = 1.5;
      }
      AttachDynamicObjectToVehicle(gSpeedPlayer[playerid][Name], vid, -vX-1.75, -1.0, 0.0, 0.0, 0.0, 290.0);
      AttachDynamicObjectToVehicle(gSpeedPlayer[playerid][Status], vid, -vX-1.75, -1.0, -0.3, 0.0, 0.0, 290.0);
      AttachDynamicObjectToVehicle(gSpeedPlayer[playerid][Speed], vid, -vX-1.75, -1.0, -0.6, 0.0, 0.0, 290.0);
      Streamer_Update(playerid);
      gSpeedPlayer[playerid][Enabled] = 1;
   } else {
      if (gSpeedPlayer[playerid][Name] != INVALID_OBJECT_ID) {
         DestroyDynamicObject(gSpeedPlayer[playerid][Name]);
         DestroyDynamicObject(gSpeedPlayer[playerid][Status]);
         DestroyDynamicObject(gSpeedPlayer[playerid][Speed]);
         gSpeedPlayer[playerid][Name] = INVALID_OBJECT_ID;
         gSpeedPlayer[playerid][Status] = INVALID_OBJECT_ID;
         gSpeedPlayer[playerid][Speed] = INVALID_OBJECT_ID;
      }
      gSpeedPlayer[playerid][Enabled] = 0;
   }
   return 1;
}


/* Hooks
   Automatically hook onto the gamemode, if applicable.

*/

#if defined _INC_y_hooks

hook OnPlayerConnect(playerid) {
   tdSpeedo_Connect(playerid);
   return 1;
}


hook OnPlayerDisconnect(playerid, reason) {
   tdSpeedo_Disconnect(playerid);
   return 1;
}

hook OnPlayerUpdate(playerid) {
   tdSpeedo_Update(playerid);
   return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
   if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
      tdSpeedo_Toggle(playerid, 1);
   } else {
      tdSpeedo_Toggle(playerid, 0);
   }
   return 1;
}

#endif

/* Vehicle names array */