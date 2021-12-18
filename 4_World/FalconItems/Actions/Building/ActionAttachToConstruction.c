modded class ActionAttachToConstruction: ActionSingleUseBase
{
	override void OnExecuteServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;
		EntityAI building_object = action_data.m_MainItem;
		TerritoryFlag totem

		totem = TerritoryBuildingHelpers.getNearbyTotem(player, TerritoryConsts.PLOT_POLE_RADIUS);
	
		if (totem)
		{
			if (totem.checkIfOwner(player.GetIdentity().GetId()))
			{
				super.OnExecuteServer(action_data);
			}
			else
			{
				GetRPCManager().SendRPC("FalconItems", "itemsMessagePlayerC", new Param1<string>(ItemsMessagesConstants.BUILD_IN_NOT_OWNED_TERRITORY), true,  player.GetIdentity());
			}
		}
		else
		{
			super.OnExecuteServer(action_data);
		}
	}
}