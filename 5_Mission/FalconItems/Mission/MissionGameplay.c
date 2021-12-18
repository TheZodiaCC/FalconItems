modded class MissionGameplay 
{
	ref MapMonitor MapMonit;
	ref SafeCodeLock safeCodeLockMenu;
	ref PlotPoleMonitor plotPoleMonitor;
	ref CodeLockMenu codeLockMenu;
	ref GPSTrack gpsTrack;

	private PlayerBase player;
	
	private float itemsUpdateTick = 0.01;
	private float itemsCurrentTime;
	private float itemsNTime = 0;
	
	private vector gpsTrackPoint;
	
	ref array<ref ServerMarker> serverMarkers = new array<ref ServerMarker>();

	
	void MissionGameplay()
	{
		GetRPCManager().AddRPC( "FalconItems", "openSafePassC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "openCodeLockPassC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "openPlotPoleC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "itemsMessagePlayerC", this, SingeplayerExecutionType.Server );
		
		GetRPCManager().AddRPC( "FalconItems", "getServerMarkersC", this, SingeplayerExecutionType.Server );
		
		gpsTrack = new GPSTrack();
	}
	
	private void getServerMarkersC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<array<ref ServerMarker>> data;
        if ( !ctx.Read( data ) ) return;
        
        if (type == CallType.Client) 
		{
			if (data.param1)
			{
				serverMarkers = data.param1;
			}
        }
    }
	
	private void openSafePassC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<Safe> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) {
			if (data.param1)
			{
				Safe safe = data.param1;
				
				if (safe)
				{
					if (safeCodeLockMenu) 
					{						
						if (!safeCodeLockMenu.isOpened()) 
						{
		                    openSafeCodeLockMenu();
		               	}
		            } 
					else if (!safeCodeLockMenu) 
					{
						safeCodeLockMenu = SafeCodeLock.Cast(GetUIManager().EnterScriptedMenu(2138215, null));
						
		                openSafeCodeLockMenu();
	            	}
					
					safeCodeLockMenu.setSafe(safe);
					safeCodeLockMenu.setMode();
				}
			}
        }
	}
	
	private void openCodeLockPassC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<CodeLock> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) {
			if (data.param1)
			{
				CodeLock codeLock = data.param1;
				
				if (codeLock)
				{
					if (codeLockMenu) 
					{						
						if (!codeLockMenu.isOpened()) 
						{
		                    openCodeLockMenu();
		               	}
		            } 
					else if (!codeLockMenu) 
					{
						codeLockMenu = CodeLockMenu.Cast(GetUIManager().EnterScriptedMenu(1321258, null));
						
		                openCodeLockMenu();
	            	}
					
					codeLockMenu.setCodeLock(codeLock);
					codeLockMenu.setMode();
				}
			}
        }
	}
	
	private void openPlotPoleC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<TerritoryFlag> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) {
			if (data.param1)
			{
				TerritoryFlag totem = data.param1;
				
				if (totem)
				{
					if (plotPoleMonitor) 
					{						
						if (!plotPoleMonitor.isOpened()) 
						{
							plotPoleMonitor.setTotem(totem);
		                    openPlotPoleMenu();
		               	}
		            } 
					else if (!plotPoleMonitor) 
					{
						plotPoleMonitor = PlotPoleMonitor.Cast(GetUIManager().EnterScriptedMenu(2023215, null));
						
						plotPoleMonitor.setTotem(totem);	
		                openPlotPoleMenu();
	            	}
				}
			}
        }
	}
	
	private void itemsMessagePlayerC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				string message = "[FalconItems] " + data.param1;
				GetGame().Chat(message, "colorAction");
			}
		}
	}

	override void OnKeyPress(int key)
    {
		//Print("IT = " + key);
		super.OnKeyPress(key);
		
		if (key == KeyCode.KC_M || key == KeyCode.KC_ESCAPE) 
		{
			if (GetGame().GetUIManager().GetMenu() == null || GetGame().GetUIManager().GetMenu().Type().ToString() == "MapMonitor")
			{
				if (ItemsHelper.getItemFromInventory(PlayerBase.Cast(GetGame().GetPlayer()), "GPS"))
				{
					if (MapMonit) 
					{
		                if (MapMonit.isMapOpened()) 
						{
		                    closeMapMenu();
		                } 
						
						else if (!MapMonit.isMapOpened() && key == KeyCode.KC_M) 
						{
		                    openMapMenu();
		               	}
		            } 
					else if (!MapMonit && key == KeyCode.KC_M) 
					{
		                MapMonit = MapMonitor.Cast(GetUIManager().EnterScriptedMenu(2138333, null));
		                MapMonit.setMapOpened(true);
		            }
				}
			}
			
			else
			{
				if (key == KeyCode.KC_ESCAPE)
				{
					if (safeCodeLockMenu)
					{
						if (safeCodeLockMenu.isOpened())
						{
							closeSafeCodeLockMenu();
						}
					}
					
					if (plotPoleMonitor)
					{
						if (plotPoleMonitor.isOpened())
						{
							closePlotPoleMenu();
						}
					}
					
					if (codeLockMenu)
					{
						if (codeLockMenu.isOpened())
						{
							closeCodeLockMenu();
						}
					}
				}
			}
		}
	}
	
	override void TickScheduler(float timeslice)
	{	
		super.TickScheduler(timeslice);
		
		itemsCurrentTime = GetGame().GetTime() * 0.001;
		
		if (itemsCurrentTime >= itemsNTime + itemsUpdateTick)
		{
			if (ItemsHelper.getItemFromInventory(PlayerBase.Cast(GetGame().GetPlayer()), "GPS"))
			{
				if (this.gpsTrackPoint != vector.Zero)
				{
					gpsTrack.update(this.gpsTrackPoint);
				}
				
				else
				{
					gpsTrack.hideTrack();
				}
			}
			
			else
			{
				if (gpsTrack.getIsTrackOn())
				{
					gpsTrack.hideTrack();
					
					this.gpsTrackPoint = vector.Zero;
				}
			}
			
			itemsNTime = itemsCurrentTime;
		}
	}
	
	private void openMapMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(MapMonit, NULL);
        MapMonit.setMapOpened(true);
	}
	
	private void closeMapMenu()
	{
		MapMonit.setMapOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(MapMonit);
	}
	
	private void openSafeCodeLockMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(safeCodeLockMenu, NULL);
        safeCodeLockMenu.setIsOpened(true);
	}
	
	private void closeSafeCodeLockMenu()
	{
		safeCodeLockMenu.setIsOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(safeCodeLockMenu);
	}
	
	private void openPlotPoleMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(plotPoleMonitor, NULL);
        plotPoleMonitor.setIsOpened(true);
	}
	
	private void closePlotPoleMenu()
	{
		plotPoleMonitor.setIsOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(plotPoleMonitor);
	}
	
	private void openCodeLockMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(codeLockMenu, NULL);
        codeLockMenu.setIsOpened(true);
	}
	
	private void closeCodeLockMenu()
	{
		codeLockMenu.setIsOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(codeLockMenu);
	}
	
	vector getGPSTrackPoint()
	{
		return gpsTrackPoint;
	}
	
	void setGPSTrackPoint(vector vec)
	{
		gpsTrackPoint = vec;
	}
}