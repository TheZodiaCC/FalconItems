class CodeLockMenu extends UIScriptedMenu
{
	private CodeLock codeLock;
	private ref CodeLockHelpers codeLockHelpers;
	private string mode;
	
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isOpened;
	
	private TextWidget codeLockModeTEXT;
	private EditBoxWidget passwordTEXT;
	private ButtonWidget applyBUTTON;
	private ButtonWidget removeBUTTON;
	private TextWidget messageTEXT;
	
	private ref Timer buttonsTimer = new Timer( CALL_CATEGORY_SYSTEM );
	
	//Constructor
	void CodeLockMenu() {	
		codeLockHelpers = new ref CodeLockHelpers();
	}
	
	//Deconstructor
	void ~CodeLockMenu() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		delete codeLockHelpers;

        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconItems/GUI/Layouts/CodeLock.layout");
			widgetRoot.Show(false);
			
			codeLockModeTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("CodeLockModeTEXT"));
			
			passwordTEXT = EditBoxWidget.Cast(widgetRoot.FindAnyWidget("PasswordTEXT"));
			applyBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("ApplyBUTTON"));
			removeBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("RemoveBUTTON"));
			
			messageTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("MessageTEXT"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick(applyBUTTON, this, "applyCodeLockCode");
			WidgetEventHandler.GetInstance().RegisterOnClick(removeBUTTON, this, "removeCodeLock");
			
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
		if (codeLock.getPasswordSet())
		{
			mode = "open";
			codeLockModeTEXT.SetText("Open CodeLock");
		}
		else if (!codeLock.getPasswordSet())
		{
			mode = "set";
			codeLockModeTEXT.SetText("Set Code");
		}
	}
	
	void setCodeLock(CodeLock codeLock)
	{
		this.codeLock = codeLock;
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
	
	private void applyCodeLockCode()
	{
		if (!buttonsTimer.IsRunning())
		{
			if (mode == "open")
			{
				openCodeLock();
			}
			else if (mode == "set")
			{
				setCodeLockCode();
			}
			
			startButtonsTimer();
		}
	}
	
	private void openCodeLock()
	{
		string code = passwordTEXT.GetText();
		
		if (codeLockHelpers.isCombinationCorrect(code))
		{
			CodeLockCombinationPackage package = new CodeLockCombinationPackage(codeLock, code);
		
			codeLockHelpers.openCodeLock(package);
			
			this.setIsOpened(false);
       	 	GetGame().GetUIManager().HideScriptedMenu(this);
		}
		else
		{
			messageTEXT.SetText("Incorrect Combination");
		}
	}
	
	private void setCodeLockCode()
	{
		string code = passwordTEXT.GetText();
		
		if (codeLockHelpers.isCombinationCorrect(code))
		{
			CodeLockCombinationPackage package = new CodeLockCombinationPackage(codeLock, code);
		
			codeLockHelpers.setCodeLockLock(package);
			
			this.setIsOpened(false);
       	 	GetGame().GetUIManager().HideScriptedMenu(this);
		}
		else
		{
			messageTEXT.SetText("Incorrect Combination");
		}
	}
	
	private void removeCodeLock()
	{
		string code = passwordTEXT.GetText();
		
		if (codeLockHelpers.isCombinationCorrect(code))
		{
			CodeLockCombinationPackage package = new CodeLockCombinationPackage(codeLock, code);
		
			codeLockHelpers.removeCodeLock(package);
			
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