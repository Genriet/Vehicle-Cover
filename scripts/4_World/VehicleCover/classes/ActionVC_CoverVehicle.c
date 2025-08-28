class ActionVC_CoverVehicle : ActionInteractBase
{
	void ActionVC_CoverVehicle()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "#STR_VC_CoverVehicle";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}

	override bool HasProgress()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target)
		{
			return false;
		}

		if (!IsInReach(player, target, UAMaxDistances.DEFAULT))
		{
			return false;
		}
		
		if (target.GetObject())
		{
			EntityAI targetEnt = EntityAI.Cast(target.GetObject());

			CarScript car;
			if (Class.CastTo(car, targetEnt.GetHierarchyRoot()))
			{
				if (player.GetItemInHands())
					return (player.GetItemInHands().GetType() == "CamoNet" && !player.GetItemInHands().IsRuined() && car.VC_CanAttachCamonet());
			}
			BoatScript boat;
			if (Class.CastTo(boat, targetEnt.GetHierarchyRoot()))
			{
				return (player.GetItemInHands().GetType() == "CamoNet" && !player.GetItemInHands().IsRuined() && boat.VC_CanAttachCamonet());
			}
		}

		return false;
	}

	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		
		if (action_data.m_Target.GetObject())
		{
			EntityAI targetEnt = EntityAI.Cast(action_data.m_Target.GetObject());

			CarScript car;
			if (Class.CastTo(car, targetEnt.GetHierarchyRoot()))
			{
				car.VC_TakeCamonetAndSpawn(action_data.m_Player);
			}
			BoatScript boat;
			if (Class.CastTo(boat, targetEnt.GetHierarchyRoot()))
			{
				boat.VC_TakeCamonetAndSpawn(action_data.m_Player);
			}
		}
	}
};