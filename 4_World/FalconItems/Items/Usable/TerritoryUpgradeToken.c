class TerritoryUpgradeToken extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionUpgradeTerritory);
	}
}