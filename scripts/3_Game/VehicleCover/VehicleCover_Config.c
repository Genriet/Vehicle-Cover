class VC_Data
{
    string VehicleClassname;
    string CamonetClassname;
	ref array<string> DoorSlotsToCheck;
	string CamonetShapeableSlot = "";
    string CamonetShapeableClassname = "";

    bool DropCamonet = true;
    float SpeedToDrop = 10;
	bool BlockGettingInWithCamonet = true;
    bool BlockDoorsWithCamonet = true;
	bool BlockAttachmentsWithCamonet = true;
	bool ShouldDoorsBeClosedToAttach = true;

    void VC_Data(string name, string camoname, array<string> slots)
    {
        VehicleClassname = name;
        CamonetClassname = camoname;
		DoorSlotsToCheck = slots;
    }
};

class VehicleCover_Config
{
	ref array<ref VC_Data> Vehicles = new array<ref VC_Data>();
};

modded class DayZGame
{
    protected ref VehicleCover_Config m_VehicleCover_Config;

    void SetVehicleCover_Config(VehicleCover_Config config)
    {
        m_VehicleCover_Config = config;
    }

    VehicleCover_Config GetVehicleCover_Config()
    {
        if (!m_VehicleCover_Config)
        {
            if (!FileExist("$profile:\\VehicleCover"))
            {
                MakeDirectory("$profile:\\VehicleCover");
            }
            if (!FileExist("$profile:\\VehicleCover\\VehicleCover.json"))
            {
                m_VehicleCover_Config = VC_CreateDefaultConfig();

                JsonFileLoader<ref VehicleCover_Config<ref VC_Data>>.JsonSaveFile("$profile:\\VehicleCover\\VehicleCover.json", m_VehicleCover_Config);
            }
            else
            {
                JsonFileLoader<ref VehicleCover_Config<ref VC_Data>>.JsonLoadFile("$profile:\\VehicleCover\\VehicleCover.json", m_VehicleCover_Config);

                if (!m_VehicleCover_Config)
                {
                    m_VehicleCover_Config = VC_CreateDefaultConfig();
                    ErrorEx("VEHICLE COVER JSON IS INVALID, USING DEFAULT ONE. REGENERATE JSON");
                }
            }
        }
        return m_VehicleCover_Config;
    }

    VehicleCover_Config VC_CreateDefaultConfig()
    {
        VehicleCover_Config l_VehicleCover_Config = new VehicleCover_Config();

        l_VehicleCover_Config.Vehicles.Insert(new VC_Data("CivilianSedan", "VehicleCover_CivilianSedan", { "CivSedanDriverDoors", "CivSedanCoDriverDoors", "CivSedanCargo1Doors", "CivSedanCargo2Doors", "CivSedanTrunk", "CivSedanHood" }));
        l_VehicleCover_Config.Vehicles.Insert(new VC_Data("OffroadHatchback", "VehicleCover_OffroadHatchback", { "NivaDriverDoors", "NivaCoDriverDoors", "NivaHood", "NivaTrunk" }));
        l_VehicleCover_Config.Vehicles.Insert(new VC_Data("Hatchback_02", "VehicleCover_Hatchback_02", { "Hatchback_02_Door_1_1", "Hatchback_02_Door_2_1", "Hatchback_02_Door_1_2", "Hatchback_02_Door_2_2", "Hatchback_02_Hood", "Hatchback_02_Trunk" }));
        l_VehicleCover_Config.Vehicles.Insert(new VC_Data("Sedan_02", "VehicleCover_Sedan_02", { "Sedan_02_Door_1_1", "Sedan_02_Door_2_1", "Sedan_02_Door_1_2", "Sedan_02_Door_2_2", "Sedan_02_Hood", "Sedan_02_Trunk" }));
        l_VehicleCover_Config.Vehicles.Insert(new VC_Data("Truck_01_Covered", "VehicleCover_Truck_01", { "Truck_01_Door_1_1", "Truck_01_Door_2_1", "Truck_01_Hood" }));
        l_VehicleCover_Config.Vehicles.Insert(new VC_Data("Offroad_02", "VehicleCover_Offroad_02", { "Offroad_02_Door_1_1", "Offroad_02_Door_2_1", "Offroad_02_Door_1_2", "Offroad_02_Door_2_2", "Offroad_02_Hood", "Offroad_02_Trunk" }));
        l_VehicleCover_Config.Vehicles.Insert(new VC_Data("Boat_01_ColorBase", "VehicleCover_Boat_01", {}));

        return l_VehicleCover_Config;
    }
};