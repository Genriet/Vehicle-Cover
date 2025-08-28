modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(ActionVC_UncoverVehicle);
		actions.Insert(ActionVC_CoverVehicle);
	}
};