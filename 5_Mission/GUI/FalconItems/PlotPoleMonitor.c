class PlotPoleMonitor extends UIScriptedMenu
{
	private TerritoryFlag totem;
	private ref TerritoryHelpers territoryHelpers;
	
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isOpened;
	
	private TextListboxWidget playersLIST;
	private TextWidget remainingDaysTEXT;
	private TextWidget ownersCountTEXT;
	private TextWidget objectsCountTEXT;
	private TextWidget maxObjectsCountTEXT;
	private TextWidget currentLevelTEXT;
	private TextWidget maxLevelTEXT;
	private ButtonWidget addSelfBUTTON;
	private ButtonWidget removePlayersBUTTON;
	private ButtonWidget removePlayerBUTTON;
	
	private ref Timer buttonsTimer = new Timer( CALL_CATEGORY_SYSTEM );
	
	//Constructor
	void PlotPoleMonitor() {	
		territoryHelpers = new ref TerritoryHelpers();
		
		GetRPCManager().AddRPC("FalconItems", "setPlotPoleDataC", this, SingeplayerExecutionType.Server );
	}
	
	//Deconstructor
	void ~PlotPoleMonitor() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		delete territoryHelpers;

        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconItems/GUI/Layouts/PlotPoleMonitor.layout");
			widgetRoot.Show(false);
			
			playersLIST = TextListboxWidget.Cast(widgetRoot.FindAnyWidget("PlayersLIST"));
			
			remainingDaysTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("RemainingDaysTEXT"));
			ownersCountTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("OwnersCountTEXT"));
			objectsCountTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("ObjectsCountTEXT"));
			maxObjectsCountTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("MaxObjectsCountTEXT"));
			currentLevelTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("CurrentLevelTEXT"));
			maxLevelTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("MaxLevelTEXT"));
			
			addSelfBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("AddSelfBUTTON"));
			removePlayersBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("RemovePlayersBUTTON"));
			removePlayerBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("RemoveSelectedBUTTON"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(addSelfBUTTON, this, "addSelf");
			WidgetEventHandler.GetInstance().RegisterOnClick(removePlayersBUTTON, this, "removePlayers");
			WidgetEventHandler.GetInstance().RegisterOnClick(removePlayerBUTTON, this, "removePlayer");
			
			isInitialized = true;
		}
		
		initWidgets();
		
		return widgetRoot;		
	}
	
	void initWidgets()
	{
		playersLIST.ClearItems();
		remainingDaysTEXT.SetText("");
		ownersCountTEXT.SetText("");
		
		territoryHelpers.setPlotPoleData(totem);
	}
	
	void setOwnersList(array<string> ownersNames)
	{
		for (int i = 0; i < ownersNames.Count(); i++)
		{
			playersLIST.AddItem(ownersNames[i], NULL, 0); 
		}
	}
	
	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu(0);

        unlockControls();
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu(0.5);
		
		lockControls();
    }
	
	bool isOpened() {
        return isOpened;
    }
	
	void setIsOpened(bool state) {
        isOpened = state;
		
        if (isOpened)
            PPEffects.SetBlurMenu(0.5);
        else
            PPEffects.SetBlurMenu(0);
    }
	
	void setTotem(TerritoryFlag totem)
	{
		this.totem = totem;
	}
	
	void startButtonsTimer()
	{
		buttonsTimer.Run(1, null, "");
	}
	
	void addSelf()
	{
		if (!buttonsTimer.IsRunning())
		{
			territoryHelpers.addPlotPoleOwner(totem);
			initWidgets();
			
			startButtonsTimer();
		}
	}
	
	void removePlayers()
	{
		if (!buttonsTimer.IsRunning())
		{
			territoryHelpers.clearOwners(totem);
			initWidgets();
			
			startButtonsTimer();
		}
	}
	
	void removePlayer()
	{
		if (!buttonsTimer.IsRunning())
		{
			int ind = playersLIST.GetSelectedRow();
		
			if (ind >= 0)
			{
				string playerName;
			
				playersLIST.GetItemText(ind, 0, playerName);
				
				territoryHelpers.removePlotPoleOwner(totem, playerName);
				
				initWidgets();
			}
			
			startButtonsTimer();
		}
	}
	
	private void setPlotPoleDataC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<PlotPoleDataPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) {
			
			PlotPoleDataPackage package = data.param1;

			if (package)
			{
				array<string> ownersNames = new array<string>();
				
				int refresherTimeRemaining = package.refresherTimeRemaining / 3600 / 24;
				int ownersCount = package.ownersCount;
				ownersNames = package.ownersNames;
				int maxObjectsCount = package.maxObjectsCount;
				int objectsCount = package.objectsCount;
				int maxLevel = package.maxLevel;
				int currentLevel = package.currentLevel;
				
				remainingDaysTEXT.SetText(refresherTimeRemaining.ToString());
				ownersCountTEXT.SetText(ownersCount.ToString());
				maxObjectsCountTEXT.SetText(maxObjectsCount.ToString());
				objectsCountTEXT.SetText(objectsCount.ToString());
				currentLevelTEXT.SetText(currentLevel.ToString());
				maxLevelTEXT.SetText(maxLevel.ToString());
				
				setOwnersList(ownersNames);
			}
        }
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