#define FALCON_MISSIONS


class MapMonitor extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isMapOpen;
	
	private Widget MapMain;
	private MapWidget GPSWidget;
	
	private Widget InfoPanel;
	
	private TextWidget TextPlayerPosX;
	private TextWidget TextPlayerPosY;
	
	private TextWidget CursorX;
	private TextWidget CursorY;
	
	private TextWidget DistanceTEXT;
	private ButtonWidget DeleteMarkBUTTON;
	
	private MissionGameplay mission;
	
	private ref array<string> missionsIcons = {"FalconItems\\GUI\\textures\\missionEasy.paa", "FalconItems\\GUI\\textures\\missionMedium.paa", "FalconItems\\GUI\\textures\\missionHard.paa"};
	private string dotIcon = "FalconItems\\GUI\\textures\\dot.paa";
	private string kothMissionsIcon = "FalconItems\\GUI\\textures\\koth.paa";
	
	private string serversIconsRootDir = "FalconItems\\GUI\\serverMarkers\\";
	
	//Constructor
	void MapMonitor() 
	{	
		mission = MissionGameplay.Cast(GetGame().GetMission());
	}
	
	//Deconstructor
	void ~MapMonitor() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );

        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconItems/GUI/Layouts/MapMonitor.layout");
			widgetRoot.Show(false);
			
			MapMain = Widget.Cast(widgetRoot.FindAnyWidget("mapPanel"));
			GPSWidget = MapWidget.Cast(widgetRoot.FindAnyWidget("gpsWidget"));
			InfoPanel = Widget.Cast(widgetRoot.FindAnyWidget("infoPanel"));
			
			TextPlayerPosX = TextWidget.Cast(widgetRoot.FindAnyWidget("TextPlayerPosX"));
			TextPlayerPosY = TextWidget.Cast(widgetRoot.FindAnyWidget("TextPlayerPosY"));
						
			CursorX = TextWidget.Cast(widgetRoot.FindAnyWidget("CursorX"));
			CursorY = TextWidget.Cast(widgetRoot.FindAnyWidget("CursorY"));
			
			DistanceTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("DistanceTEXT"));
			
			DeleteMarkBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("DeleteMarkBUTTON"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(DeleteMarkBUTTON, this, "deleteTrack");

			isInitialized = true;
		}
		
		initWidgets();
		
		return widgetRoot;		
	}
	
	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu(0);

		GetGame().GetCallQueue( CALL_CATEGORY_GUI ).Remove( UpdateMapMarkers );
		
        unlockControls();
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu(0);
		
		UpdateMapMarkers();
		GetGame().GetCallQueue( CALL_CATEGORY_GUI ).CallLater( UpdateMapMarkers, 1000, true );
		lockControls();
    }
	
	void UpdateMapMarkers()
	{
		GPSWidget.ClearUserMarks();

		UpdatePlayerMarkers();
		updateMissionsMarkers();
		updateKOTHMarkers();
		
		updateServerMarkers();
	}
	
	void deleteTrack()
	{
		mission.setGPSTrackPoint(vector.Zero);
	}
	
	private void UpdatePlayerMarkers() 
	{
		vector playerPosition = GetGame().GetPlayer().GetPosition();
		vector trackerPosition = mission.getGPSTrackPoint();
		
		TextPlayerPosX.SetText(playerPosition[0].ToString());
		TextPlayerPosY.SetText(playerPosition[2].ToString());

		GPSWidget.AddUserMark(playerPosition, "You", ARGB(255, 255, 0, 0), dotIcon);
		
		if (trackerPosition != vector.Zero)
		{
			GPSWidget.AddUserMark(trackerPosition, "Your Tracker", ARGB(255, 255, 0, 0), dotIcon);
		}
	}
	
	private void updateMissionsMarkers()
	{
		#ifdef FALCON_MISSIONS
		
		mission.updateMissionsDetails();
		
		string missionName;
		
		if (mission.missionsPlaces)
		{
			for (int i = 0; i < mission.missionsPlaces.Count(); i++)
			{
				missionName = "[" + mission.missionsPlaces[i].missionType + "]" + " " + mission.missionsPlaces[i].name;
				
				if (mission.missionsPlaces[i].lvl == 1)
				{
					GPSWidget.AddUserMark(mission.missionsPlaces[i].position.ToVector(), missionName, ARGB(255, 84, 255, 0), missionsIcons[0]);
				}
				
				else if (mission.missionsPlaces[i].lvl == 2)
				{
					GPSWidget.AddUserMark(mission.missionsPlaces[i].position.ToVector(),missionName, ARGB(255, 255, 140, 24), missionsIcons[1]);
				}
				
				else if (mission.missionsPlaces[i].lvl == 3)
				{
					GPSWidget.AddUserMark(mission.missionsPlaces[i].position.ToVector(), missionName, ARGB(255, 255, 0, 0), missionsIcons[2]);
				}
				
				else
				{
					GPSWidget.AddUserMark(mission.missionsPlaces[i].position.ToVector(), missionName, ARGB(255, 230, 20, 20), missionsIcons[1]);
				}
			}
		}
		
		#endif
	}
	
	private void updateKOTHMarkers()
	{
		#ifdef FALCON_MISSIONS
		
		mission.updateKOTHDetails();
		
		string missionName;
		
		if (mission.kothPlaces)
		{
			for (int i = 0; i < mission.kothPlaces.Count(); i++)
			{
				missionName = "[" + mission.kothPlaces[i].captureProgress + "%]" + " " + mission.kothPlaces[i].name + " #" + mission.kothPlaces[i].missionID;
				
				GPSWidget.AddUserMark(mission.kothPlaces[i].position.ToVector(), missionName, ARGB(255, 0, 236, 247), kothMissionsIcon);
			}
		}
		
		#endif
	}
	
	private void updateServerMarkers()
	{
		if (mission.serverMarkers)
		{
			for (int i = 0; i < mission.serverMarkers.Count(); i++)
			{
				GPSWidget.AddUserMark(mission.serverMarkers[i].pos.ToVector(), mission.serverMarkers[i].name, ARGB(255, 0, 236, 247), serversIconsRootDir + mission.serverMarkers[i].iconName);
			}
		}
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) 
	{	
		if (w == GPSWidget)
		{	
			vector playerPosition = GetGame().GetPlayer().GetPosition();
			
			vector cursorPosition = GPSWidget.ScreenToMap(Vector(x, y, 0));
			vector pos = Vector(cursorPosition[0], GetGame().SurfaceY(cursorPosition[0], cursorPosition[2]), cursorPosition[2]);
			
			CursorX.SetText(pos[0].ToString());
			CursorY.SetText(pos[2].ToString());
			
			DistanceTEXT.SetText(getCursorDistance(pos, playerPosition).ToString());
			
			mission.setGPSTrackPoint(pos);
						
			return true;
		}
		
		return true;
	}
	
	private float getCursorDistance(vector cursorPosition, vector playerPosition)
	{
		float distance;
		
		playerPosition[1] = 0;
		cursorPosition[1] = 0;
		
		distance = vector.Distance(cursorPosition, playerPosition);
		
		return distance;
	}
	
	private void initWidgets() {		
		MapMain.Show(true);
	}
	
	bool isMapOpened() {
        return isMapOpen;
    }
	
	void setMapOpened(bool state) {
        isMapOpen = state;
        if (isMapOpen)
            PPEffects.SetBlurMenu(0);
        else
            PPEffects.SetBlurMenu(0);
    }
	
	private void lockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void unlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
}