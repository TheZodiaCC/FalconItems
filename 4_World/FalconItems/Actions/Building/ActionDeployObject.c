modded class ActionDeployObject: ActionDeployObject
{		
	override void OnStartServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;
		EntityAI building_object = action_data.m_MainItem;
		TerritoryFlag totem
		
		if (building_object.IsInherited(TerritoryFlagKit))
		{
			totem = TerritoryBuildingHelpers.getNearbyTotem(player, TerritoryConsts.PLOT_POLE_RADIUS_FROM_ANOTHER_PLOT_POLE);
		
			if (!totem)
			{
				super.OnStartServer(action_data);
			}
			else
			{
				GetRPCManager().SendRPC("FalconItems", "itemsMessagePlayerC", new Param1<string>(ItemsMessagesConstants.PLOT_POLE_STACKING), true,  player.GetIdentity());
			}
		}
		else
		{
			totem = TerritoryBuildingHelpers.getNearbyTotem(player, TerritoryConsts.PLOT_POLE_RADIUS);
		
			if (totem)
			{
				if (building_object.IsInherited(Explosive))
				{
					super.OnStartServer(action_data);
				}
				
				else
				{
					if (totem.checkIfOwner(player.GetIdentity().GetId()))
					{
						if (TerritoryBuildingHelpers.checkIfCanBuild(totem))
						{
							super.OnStartServer(action_data);
						}
						
						else
						{
							GetRPCManager().SendRPC("FalconItems", "itemsMessagePlayerC", new Param1<string>(ItemsMessagesConstants.TOO_MANY_OBJECTS), true,  player.GetIdentity());
						}
					}
					
					else
					{
						GetRPCManager().SendRPC("FalconItems", "itemsMessagePlayerC", new Param1<string>(ItemsMessagesConstants.BUILD_IN_NOT_OWNED_TERRITORY), true,  player.GetIdentity());
					}
				}
			}
			
			else
			{
				super.OnStartServer(action_data);
			}
		}
	}
	
	 override void SetupAnimation(ItemBase item)
    {
        if (item.IsInherited(Explosive))
        {
            m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DEPLOY_2HD;
            return;
        }

        super.SetupAnimation(item);
    }
}