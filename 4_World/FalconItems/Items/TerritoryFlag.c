modded class TerritoryFlag extends BaseBuildingBase
{
	ref array<string> ownersIDs = new array<string>();
	int territoryLevel = 1;
	
	
	void TerritoryFlag()
	{
		RegisterNetSyncVariableInt("territoryLevel");
		
		m_FlagRefresherMaxDuration = TerritoryConsts.TERRITORY_UPTIME;
		m_FlagRefresherFrequency = TerritoryConsts.TERRITORY_UPTIME_UPDATE;
	}
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		ctx.Write(ownersIDs);
		ctx.Write(territoryLevel);
		
		super.OnStoreSave( ctx );
	}
	
	override void SetRefresherActive(bool state)
	{
		if (m_RefresherActive != state)
		{
			m_RefresherActive = state;
			SetSynchDirty();
			
			//update on refresher activation / last update on refresher deactivation
			GetCEApi().RadiusLifetimeReset(GetPosition(), TerritoryConsts.PLOT_POLE_RADIUS);
		}
	}

	override void InitRefresherData()
	{
		/*int frequency = TerritoryConsts.TERRITORY_UPTIME_UPDATE;
		int max_duration = TerritoryConsts.TERRITORY_UPTIME;
		
		if ( frequency > 0)
		{
			m_FlagRefresherFrequency = frequency;
		}
		if ( max_duration > 0 )
		{
			m_FlagRefresherMaxDuration = max_duration;
		}*/
		
		m_RefresherInitialized = true;
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !ctx.Read(ownersIDs) )
		{
			ownersIDs = {};
			
			return false;
		}
		
		if ( !ctx.Read(territoryLevel) )
		{
			territoryLevel = 0;
			
			return false;
		}
		
		return super.OnStoreLoad(ctx, version);
	}
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInteractPlotPole);
	}
	
	int getRefresherTimeRemaining()
	{
		//Print(m_RefresherTimeRemaining);
		//Print(m_FlagRefresherMaxDuration);
		//Print(m_FlagRefresherFrequency);
		
		//Print(TerritoryConsts.TERRITORY_UPTIME);
		//Print(TerritoryConsts.TERRITORY_UPTIME);
		//Print(TerritoryConsts.PLOT_POLE_RADIUS);
		
		return m_RefresherTimeRemaining;
	}
	
	private bool checkIfIDAdded(string id)
	{
		for (int i = 0; i < ownersIDs.Count(); i++)
		{
			if (ownersIDs[i] == id)
			{
				return true;
			}
		}
		
		return false;
	}
	
	array<string> getOwnersIDs()
	{
		return ownersIDs;
	}
	
	void addOwnerID(string id)
	{
		if (!checkIfIDAdded(id))
		{
			ownersIDs.Insert(id);
		}
	}
	
	void removeOwnerID(string id)
	{
		ownersIDs.RemoveItem(id);
	}
	
	void clearOwners()
	{
		ownersIDs.Clear();
	}
	
	bool checkIfOwner(string playerID)
	{
		for (int i = 0; i < ownersIDs.Count(); i++)
		{
			if (playerID == ownersIDs[i])
			{
				return true;
			}		
		}
		
		return false;
	}
	
	void setTerritoryLevel(int value)
	{
		territoryLevel = value;
	}
	
	int getTerritoryLevel()
	{
		return territoryLevel;
	}
	
	bool canBeUpgraded()
	{
		bool cond = false;
		
		if (territoryLevel < TerritoryConsts.MAX_TERRITORY_LEVEL)
		{
			cond = true;
		}
		
		return cond;
	}
}