modded class MissionServer
{
    void MissionServer()
    {
        VehicleCover_Config config;
        config = GetDayZGame().GetVehicleCover_Config();
    }
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        auto configParams = new Param1<VehicleCover_Config>(GetDayZGame().GetVehicleCover_Config());
        GetGame().RPCSingleParam(player, VEHICLECOVERCONFIG, configParams, true, identity);
    }
};