/*
	3dspeed 1.0
	mrks.cf | github.com/markski1
	Thanks to:
		open.mp/docs contributors
		SACNR
*/

#if defined tdspeed_included
	#endinput
#endif

#define tdspeed_included

/*
	Configuration constants, include before this file.

	TDSPEED_MPH to say MPH instead of KMH
	TDSPEED_SPANISH to have spanish text.
	TDSPEED_HIDENAME to not show vehicle name.
*/

enum SpeedometerComponents {
	#if !defined TDSPEED_HIDENAME
	Name,
	#endif
	Status,
	Speed,
	Enabled
}

static gSpeedPlayer[MAX_PLAYERS][SpeedometerComponents];

static gTickCount[MAX_PLAYERS];

/* Vehicle names array */

#if !defined TDSPEED_HIDENAME

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

#endif

/* Functions */

stock Update3DSpeedometer(playerid, speed, fuel=-1) {
	if (!gSpeedPlayer[playerid][Enabled]) return 1;
	gTickCount[playerid]++;
	if (gTickCount[playerid] < 5) return 1;
	gTickCount[playerid] = 0;
	if (!IsPlayerInAnyVehicle(playerid)) {
		tdSpeedo_Toggle(playerid, 0);
		return 1;
	} else if (!IsPlayerNPC(playerid)) {
		new vehid = GetPlayerVehicleID(playerid);
		new Float:pvX, Float:pvY, Float:pvZ, Float:vhp;
		GetVehicleHealth(vehid, vhp);
		vhp = (((vhp - 250.0) / 750.0) * 100.0);
		new speedText[48];
		new statusText[48];
		if (fuel > -1) {
			#if !defined TDSPEED_SPANISH
				format(statusText, 48, "Fuel: %i%%, Health: %3.0f%%", fuel, vhp);
			#else
				format(statusText, 48, "Combustible: %i%%, Vida: %3.0f%%", fuel, vhp);
			#endif
		} else {
			#if !defined TDSPEED_SPANISH
				format(statusText, 48, "Health: %3.0f%%", vhp);
			#else
				format(statusText, 48, "Vida: %3.0f%%", vhp);
			#endif
		}
		#if !defined TDSPEED_MPH
			format(speedText, 48, "%i KMH", speed);
		#else
			format(speedText, 48, "%i MPH", speed);
		#endif
		#if !defined TDSPEED_HIDENAME
			new modelid = GetVehicleModel(vehid);
			SetDynamicObjectMaterialText(gSpeedPlayer[playerid][Name], 0, gVehicleNames[modelid-400], OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, true, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
		#endif
		SetDynamicObjectMaterialText(gSpeedPlayer[playerid][Status], 0, statusText, OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, false, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
		SetDynamicObjectMaterialText(gSpeedPlayer[playerid][Speed], 0, speedText, OBJECT_MATERIAL_SIZE_512x256, "Arial", 30, false, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_RIGHT);
	}
	return 1;
}

static tdSpeedo_Toggle(playerid, activate) {
	if (activate) {
		if (gSpeedPlayer[playerid][Enabled]) {
			return 1;
		}
		new vid = GetPlayerVehicleID(playerid);
		new vmod = GetVehicleModel(vid);
		#if !defined TDSPEED_HIDENAME
			gSpeedPlayer[playerid][Name] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
		#endif
		gSpeedPlayer[playerid][Status] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
		gSpeedPlayer[playerid][Speed] = CreateDynamicObject(19482, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, playerid, 200.0);
		new Float:vX,Float:vY,Float:vZ;
		GetVehicleModelInfo(vmod, VEHICLE_MODEL_INFO_SIZE, vX, vY, vZ);
		if (vX < 1.5) {
			vX = 1.5;
		}
		#if !defined TDSPEED_HIDENAME
			AttachDynamicObjectToVehicle(gSpeedPlayer[playerid][Name], vid, -vX-1.75, -1.0, 0.0, 0.0, 0.0, 290.0);
		#endif
		AttachDynamicObjectToVehicle(gSpeedPlayer[playerid][Status], vid, -vX-1.75, -1.0, -0.3, 0.0, 0.0, 290.0);
		AttachDynamicObjectToVehicle(gSpeedPlayer[playerid][Speed], vid, -vX-1.75, -1.0, -0.6, 0.0, 0.0, 290.0);
		Streamer_Update(playerid);
		gSpeedPlayer[playerid][Enabled] = 1;
	} else {
		if (gSpeedPlayer[playerid][Status] != INVALID_OBJECT_ID) {
			#if !defined TDSPEED_HIDENAME
				DestroyDynamicObject(gSpeedPlayer[playerid][Name]);
				gSpeedPlayer[playerid][Name] = INVALID_OBJECT_ID;
			#endif
			DestroyDynamicObject(gSpeedPlayer[playerid][Status]);
			gSpeedPlayer[playerid][Status] = INVALID_OBJECT_ID;
			DestroyDynamicObject(gSpeedPlayer[playerid][Speed]);
			gSpeedPlayer[playerid][Speed] = INVALID_OBJECT_ID;
		}
		gSpeedPlayer[playerid][Enabled] = 0;
	}
	return 1;
}


/*
   Hooks
*/

public OnPlayerConnect(playerid) {
	for (new i = 0; i < _:SpeedometerComponents-1; i++) {
		gSpeedPlayer[playerid][SpeedometerComponents:i] = INVALID_OBJECT_ID;
	}
	gSpeedPlayer[playerid][Enabled] = 0;
	gTickCount[playerid] = 0;

	#if defined tf_OnPlayerConnect
		return tds_OnPlayerConnect(playerid);
	#endif
}


public OnPlayerDisconnect(playerid, reason) {
	if(gSpeedPlayer[playerid][Status] != INVALID_OBJECT_ID) {
		#if !defined TDSPEED_HIDENAME
			DestroyDynamicObject(gSpeedPlayer[playerid][Name]);
		#endif
		DestroyDynamicObject(gSpeedPlayer[playerid][Status]);
		DestroyDynamicObject(gSpeedPlayer[playerid][Speed]);
	}

	#if defined tf_OnPlayerDisconnect
		return tds_OnPlayerDisconnect(playerid);
	#endif
}

public OnPlayerStateChange(playerid, newstate, oldstate) {
	if (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) {
		tdSpeedo_Toggle(playerid, 1);
	} else {
		tdSpeedo_Toggle(playerid, 0);
	}

	#if defined tf_OnPlayerStateChange
		return tds_OnPlayerStateChange(playerid);
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect tds_OnPlayerConnect

#if defined tds_OnPlayerConnect
	forward tds_OnPlayerConnect();
#endif

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect tds_OnPlayerDisconnect

#if defined tds_OnPlayerDisconnect
	forward tds_OnPlayerDisconnect();
#endif

#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif

#define OnPlayerStateChange tds_OnPlayerStateChange

#if defined tds_OnPlayerStateChange
	forward tds_OnPlayerStateChange();
#endif