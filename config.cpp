class CfgMods
{
	class VehicleCover
	{
		type = "mod";
		dependencies[] = { "Game", "World", "Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "VehicleCover\scripts\3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "VehicleCover\scripts\4_World" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "VehicleCover\scripts\5_Mission" };
			};
		};
	};
};

class CfgPatches
{
	class VehicleCover
	{
		requiredAddons[] = { "DZ_Scripts", "DZ_Data" };
	};
};

class CfgVehicles
{
	// Shape objects
	class HouseNoDestruct;
	class VehicleCover_Base : HouseNoDestruct
	{
		scope = 0;
		hiddenSelections[] = { "camo" };
		hiddenSelectionsTextures[] = { "dz\structures\military\improvised\data\camonet_east_co.paa" };
		hiddenSelectionsMaterials[] = { "dz\gear\camping\data\fence_camonet_east.rvmat" };
	};
	class VehicleCover_Boat_01 : VehicleCover_Base
	{
		scope = 1;
		model = "VehicleCover\models\Boat_01.p3d";
	};
	class VehicleCover_OffroadHatchback : VehicleCover_Base
	{
		scope = 1;
		model = "VehicleCover\models\OffroadHatchback.p3d";
	};
	class VehicleCover_CivilianSedan : VehicleCover_Base
	{
		scope = 1;
		model = "VehicleCover\models\CivilianSedan.p3d";
	};
	class VehicleCover_Hatchback_02 : VehicleCover_Base
	{
		scope = 1;
		model = "VehicleCover\models\Hatchback_02.p3d";
	};
	class VehicleCover_Sedan_02 : VehicleCover_Base
	{
		scope = 1;
		model = "VehicleCover\models\Sedan_02.p3d";
	};
	class VehicleCover_Truck_01 : VehicleCover_Base
	{
		scope = 1;
		model = "VehicleCover\models\Truck_01.p3d";
	};
	class VehicleCover_Offroad_02 : VehicleCover_Base
	{
		scope = 1;
		model = "VehicleCover\models\Offroad_02.p3d";
	};
};

class PreloadVehicles
{
	class VehicleCover_Boat_01
	{
		loadStyle = 2;
	};
	class VehicleCover_OffroadHatchback
	{
		loadStyle = 2;
	};
	class VehicleCover_CivilianSedan
	{
		loadStyle = 2;
	};
	class VehicleCover_Hatchback_02
	{
		loadStyle = 2;
	};
	class VehicleCover_Sedan_02
	{
		loadStyle = 2;
	};
	class VehicleCover_Truck_01
	{
		loadStyle = 2;
	};
	class VehicleCover_Offroad_02
	{
		loadStyle = 2;
	};
};