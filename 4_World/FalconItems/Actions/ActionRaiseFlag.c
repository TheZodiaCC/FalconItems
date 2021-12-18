modded class ActionRaiseFlag
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		TerritoryFlag totem = TerritoryFlag.Cast( action_data.m_Target.GetObject() );
		
		if (totem)
		{
			ItemBase token = TerritoryBuildingHelpers.getItemFromInventory(action_data.m_Player, "TerritoryToken");
			
			if (token)
			{
				token.Delete();
				super.OnFinishProgressServer(action_data);
			}
			
			else
			{
				GetRPCManager().SendRPC("FalconItems", "itemsMessagePlayerC", new Param1<string>(ItemsMessagesConstants.NO_PAYMENT_TOKEN), true,  action_data.m_Player.GetIdentity());
			}
		}
	}
}