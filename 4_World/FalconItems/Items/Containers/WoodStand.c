class WoodStand extends DeployableContainer_Base
{
	override bool CanPutInCargo(EntityAI parent)
	{
		WoodenLog logs = WoodenLog.Cast(FindAttachmentBySlotName("WoodenLogsStand"));
		WoodenPlank planks = WoodenPlank.Cast(FindAttachmentBySlotName("WoodenPlanksStand"));
		
		if (logs || planks)
		{
			return false;
		}
		else
		{
			return super.CanPutInCargo(parent);
		}
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		WoodenLog logs = WoodenLog.Cast(FindAttachmentBySlotName("WoodenLogsStand"));
		WoodenPlank planks = WoodenPlank.Cast(FindAttachmentBySlotName("WoodenPlanksStand"));
		
		if (logs || planks)
		{
			return false;
		}
		else
		{
			return super.CanPutIntoHands(parent);
		}
	}
}

