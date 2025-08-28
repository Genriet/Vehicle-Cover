modded class ActionGetInTransport
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		EntityAI targetEnt = EntityAI.Cast(target.GetObject());
		
		CarScript car;
		if (Class.CastTo(car, targetEnt.GetHierarchyRoot()))
		{
			if (car.VC_CamonetBlocksGettingIn() && car.VC_HasCamonet())
			{
					return false;
			}
		}
		
		BoatScript boat;
		if (Class.CastTo(boat, targetEnt.GetHierarchyRoot()))
		{
			if (boat.VC_CamonetBlocksGettingIn() && boat.VC_HasCamonet())
			{
					return false;
			}
		}
		
		return super.ActionCondition(player, target, item);
	}
}
