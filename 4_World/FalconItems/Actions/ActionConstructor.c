modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(ActionOpenSafe);
		actions.Insert(ActionCloseSafe);
		actions.Insert(ActionCrackSafe);
		actions.Insert(ActionInjectInstaDocTarget);
		actions.Insert(ActionInjectInstaDocSelf);
		actions.Insert(ActionInteractPlotPole);
		actions.Insert(ActionOpenCodeLock);
		actions.Insert(ActionCrackCodeLock);
		actions.Insert(ActionUpgradeTerritory);
	}
}