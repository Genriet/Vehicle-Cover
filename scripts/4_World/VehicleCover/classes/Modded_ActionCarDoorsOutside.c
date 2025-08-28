modded class ActionCarDoorsOutside
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (target.GetObject())
		{
			EntityAI targetEnt = EntityAI.Cast(target.GetObject());

			CarScript car;
			if (Class.CastTo(car, targetEnt.GetHierarchyRoot()))
			{
				if (car.VC_CamonetBlocksDoors() && car.VC_HasCamonet())
				{
					if (m_IsOpening)
						return false;
				}
			}
		}

		return super.ActionCondition(player, target, item);
	}
};
