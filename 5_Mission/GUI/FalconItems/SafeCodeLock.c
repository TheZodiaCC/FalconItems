class SafeCodeLock extends UIScriptedMenu
{
	private Safe safe;
	private ref SafeHelpers safeHelpers;
	private string mode;
	
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isOpened;
	
	private TextWidget codeLockModeTEXT;
	private EditBoxWidget passwordTEXT;
	private ButtonWidget applyBUTTON;
	private TextWidget messageTEXT;
	
	private ref Timer buttonsTimer = new Timer( CALL_CATEGORY_SYSTEM );
	
	//Constructor
	void SafeCodeLock() {	
		safeHelpers = new ref SafeHelpers();
	}
	
	//Deconstructor
	void ~SafeCodeLock() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		delete safeHelpers;

        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconItems/GUI/Layouts/SafeCodeLock.layout");
			widgetRoot.Show(false);
			
			codeLockModeTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("CodeLockModeTEXT"));
			
			passwordTEXT = EditBoxWidget.Cast(widgetRoot.FindAnyWidget("PasswordTEXT"));
			applyBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ApplyBUTTON"));
			
			messageTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("MessageTEXT"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(applyBUTTON, this, "applySafeCode");
			
			isInitialized = true;
		}
		
		initWidgets();
		
		return widgetRoot;		
	}
	
	private void initWidgets()
	{
		passwordTEXT.SetText("");
		messageTEXT.SetText("");
		codeLockModeTEXT.SetText("");
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
	
	void setMode()
	{
		if (safe.getPasswordSet())
		{
			mode = "open";
			codeLockModeTEXT.SetText("Open Safe");
		}
		else if (!safe.getPasswordSet())
		{
			mode = "set";
			codeLockModeTEXT.SetText("Set Code");
		}
	}
	
	void setSafe(Safe safe)
	{
		this.safe = safe;
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
	
	private void applySafeCode()
	{
		if (!buttonsTimer.IsRunning())
		{
			if (mode == "open")
			{
				openSafe();
			}
			else if (mode == "set")
			{
				setSafeCode();
			}
			
			startButtonsTimer();
		}
	}
	
	private void openSafe()
	{
		string code = passwordTEXT.GetText();
		
		if (safeHelpers.isCombinationCorrect(code))
		{
			SafeCombinationPackage package = new SafeCombinationPackage(safe, code);
		
			safeHelpers.openSafe(package);
			
			this.setIsOpened(false);
       	 	GetGame().GetUIManager().HideScriptedMenu(this);
		}
		else
		{
			messageTEXT.SetText("Incorrect Combination");
		}
	}
	
	private void setSafeCode()
	{
		string code = passwordTEXT.GetText();
		
		if (safeHelpers.isCombinationCorrect(code))
		{
			SafeCombinationPackage package = new SafeCombinationPackage(safe, code);
		
			safeHelpers.setCode(package);
			
			this.setIsOpened(false);
       	 	GetGame().GetUIManager().HideScriptedMenu(this);
		}
		else
		{
			messageTEXT.SetText("Incorrect Combination");
		}
	}
	
	void startButtonsTimer()
	{
		buttonsTimer.Run(1, null, "");
	}
}