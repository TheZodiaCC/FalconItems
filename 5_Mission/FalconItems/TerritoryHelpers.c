class TerritoryHelpers
{
	void TerritoryHelpers()
    {
        GetRPCManager().AddRPC( "FalconItems", "setPlotPoleDataS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "addPlotPoleOwnerS", this, SingeplayerExecutionType.Server );		
		GetRPCManager().AddRPC( "FalconItems", "clearOwnersS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "removePlotPoleOwnerS", this, SingeplayerExecutionType.Server );
    }
	
	private array<string> getPlayersNamesByIDs(array<string> playersIDs)
	{
		array<Man> players = new array<Man>();
		array<string> playersNames = new array<string>();
		PlayerBase player;
		
		GetGame().GetPlayers(players);
		
		for (int i = 0; i < playersIDs.Count(); i++)
		{
			for (int j = 0; j < players.Count(); j++)
			{
				player = PlayerBase.Cast(players[j]);
				
				if (player.GetIdentity().GetId() == playersIDs[i])
				{
					playersNames.Insert(player.GetIdentity().GetName());
				}
			}
		}
		
		return playersNames;
	}
	
	private string getPlayerIDByName(string playerName)
	{
		array<Man> players = new array<Man>();
		PlayerBase player;
		string playerID;
		
		GetGame().GetPlayers(players);
		
		for (int i = 0; i < players.Count(); i++)
		{
			player = PlayerBase.Cast(players[i]);
			
			if (player.GetIdentity().GetName() == playerName)
			{
				playerID = player.GetIdentity().GetId();
			}
		}
		
		return playerID;
	}
	
	private void setPlotPoleDataS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<TerritoryFlag> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			TerritoryFlag totem = data.param1;
			
			if (totem)
			{
				array<string> ownersNames = new array<string>();
				
				ownersNames = getPlayersNamesByIDs(totem.getOwnersIDs());
				int currentLevel = totem.getTerritoryLevel();
				int refresherTimeRemaining = totem.getRefresherTimeRemaining();
				int ownersCount = totem.getOwnersIDs().Count();
				int maxObjectsCount = TerritoryConsts.MAX_OBJECTS_COUNT_PER_LEVEL * currentLevel;
				int objectsCount = TerritoryBuildingHelpers.getTerritoryObjectsCount(totem);
				int maxLevel = TerritoryConsts.MAX_TERRITORY_LEVEL;
				
				PlotPoleDataPackage package = new PlotPoleDataPackage(ownersNames, refresherTimeRemaining, ownersCount, maxObjectsCount, objectsCount, maxLevel, currentLevel);
				
				GetRPCManager().SendRPC("FalconItems", "setPlotPoleDataC", new Param1<PlotPoleDataPackage>(package), true, sender);
			}
        }
	}
	
	void setPlotPoleData(TerritoryFlag totem)
	{
		GetRPCManager().SendRPC("FalconItems", "setPlotPoleDataS", new Param1<TerritoryFlag>(totem));
	}
	
	private void addPlotPoleOwnerS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<TerritoryFlag> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			TerritoryFlag totem = data.param1;
			
			if (totem)
			{
				totem.addOwnerID(sender.GetId());
			}
        }
	}
	
	void addPlotPoleOwner(TerritoryFlag totem)
	{
		GetRPCManager().SendRPC("FalconItems", "addPlotPoleOwnerS", new Param1<TerritoryFlag>(totem));
	}
	
	private void clearOwnersS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<TerritoryFlag> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			TerritoryFlag totem = data.param1;
			
			if (totem)
			{
				totem.clearOwners();
			}
        }
	}
	
	void clearOwners(TerritoryFlag totem)
	{
		GetRPCManager().SendRPC("FalconItems", "clearOwnersS", new Param1<TerritoryFlag>(totem));
	}
	
	private void removePlotPoleOwnerS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<PlotPolePlayerDataPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			PlotPolePlayerDataPackage package = data.param1;
			
			if (package)
			{
				TerritoryFlag totem = package.totem;
				string playerName = package.playerName;
				
				if (totem && playerName)
				{
					string playerID = getPlayerIDByName(playerName);
					
					totem.removeOwnerID(playerID);
				}
			}
        }
	}
	
	void removePlotPoleOwner(TerritoryFlag totem, string playerName)
	{
		if (playerName)
		{
			PlotPolePlayerDataPackage package = new PlotPolePlayerDataPackage(totem, playerName);
			GetRPCManager().SendRPC("FalconItems", "removePlotPoleOwnerS", new Param1<PlotPolePlayerDataPackage>(package));
		}
	}
}