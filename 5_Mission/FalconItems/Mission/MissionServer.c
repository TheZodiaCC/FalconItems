modded class MissionServer
{
	ref SafeHelpers safeHelpers;
	ref CodeLockHelpers codeLockHelpers;
	ref TerritoryHelpers territoryHelpers;
	
	ref array<ref ServerMarker> serverMarkers = new array<ref ServerMarker>();
	
	void MissionServer()
	{
		safeHelpers = new ref SafeHelpers();
		territoryHelpers = new ref TerritoryHelpers();
		codeLockHelpers = new ref CodeLockHelpers();
	}
	
	private void setServerMarkers(PlayerIdentity identity)
	{
		GetRPCManager().SendRPC( "FalconItems", "getServerMarkersC", new Param1<array<ref ServerMarker>>(serverMarkers), true, identity);
	}
		
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		
		setServerMarkers(identity);
		
		super.InvokeOnConnect(player, identity);
		
	}
	
	override void OnInit()
	{
		super.OnInit();
		
		serverMarkers = ServerMarkersUtils.loadServerMarkers();
	}
}


