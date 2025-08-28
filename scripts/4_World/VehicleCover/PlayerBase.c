modded class PlayerBase
{
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        switch (rpc_type)
        {
            case VEHICLECOVERCONFIG:
            {
                Param1<VehicleCover_Config> configParams;
                if (!ctx.Read(configParams)) return;

                GetDayZGame().SetVehicleCover_Config(configParams.param1);
                break;
            }
        }
    }
};
