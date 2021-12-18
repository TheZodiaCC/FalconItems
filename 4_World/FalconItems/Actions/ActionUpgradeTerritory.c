class ActionUpgradeTerritory extends ActionSingleUseBase
{
	void ActionUpgradeTerritory()
	{
	}

	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
		
	override string GetText()
	{
		return "Upgrade Territory";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		
		if (target_entity && item)
		{
			if (target_entity.GetType() == "TerritoryFlag")
			{
				TerritoryFlag totem = TerritoryFlag.Cast(target_entity);
				
				if (totem.canBeUpgraded() && totem.FindAttachmentBySlotName("Material_FPole_Flag"))
				{
					return true;
				}
			}
		}	
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;
		TerritoryFlag totem = TerritoryFlag.Cast(action_data.m_Target.GetObject());
		ItemBase token = action_data.m_MainItem;
		
		if (totem.checkIfOwner(player.GetIdentity().GetId()))
		{
			if (totem.canBeUpgraded() && totem.FindAttachmentBySlotName("Material_FPole_Flag"))
			{
				totem.setTerritoryLevel(totem.getTerritoryLevel() + 1);
				token.Delete();
			}
		}
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		;
	}
}