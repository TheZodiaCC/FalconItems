class Safe extends DeployableContainer_Base
{	
	private string password;
	private bool passwordSet;
	private bool isOpened;
	
	
	void Safe()
	{
		RegisterNetSyncVariableBool("isOpened");
		RegisterNetSyncVariableBool("passwordSet");
	}
	
	override void EEInit()
    {
        super.EEInit();
		
		SetAllowDamage(false);
		
		openServer();
    }
    
    override void SetActions()
    {
        super.SetActions();
		
		AddAction(ActionOpenSafe);
		AddAction(ActionCloseSafe);
    }
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		super.OnStoreSave(ctx);
		
		ctx.Write(password);
		ctx.Write(passwordSet);
		ctx.Write(isOpened);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;
		
		if (!ctx.Read(password))
		{
			openServer();
			
			return false;
		}
		
		if (!ctx.Read(passwordSet))
		{
			openServer();
			
			return false;
		}
		
		if (!ctx.Read(isOpened))
		{
			openServer();
			
			return false;
		}
		
		return true;
	}
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if (passwordSet)
		{
			closeServer();
		}
		
		else
		{
			openServer();
		}
		
		SetSynchDirty();
	}
	
	override bool CanPutInCargo(EntityAI parent)
	{
		if (getIsOpened())
		{
			return super.CanPutInCargo(parent);
		}
		
		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		if (getIsOpened())
		{
			return super.CanPutIntoHands(parent);
		}
		
		return false;
	}
	
	bool getIsOpened()
	{
		return isOpened;
	}
	
	string getPassword()
	{
		return password;
	}
	
	void setPassword(string password)
	{
		this.password = password;
	}
	
	void setIsOpened(bool value)
	{
		isOpened = value;
	}
	
	void setPasswordSet(bool value)
	{
		passwordSet = value;
	}
	
	bool getPasswordSet()
	{
		return passwordSet;
	}
	
	//private string generatePassword()
	//{
	//	string password = "0000";
	//	string comb;
	//	
	//	comb = Math.RandomInt(1, 9999).ToString();
	//	
	//	for (int i = 0; i < 4 - comb.Length(); i++)
	//	{
	//		comb = "0" + comb;
	//	}
	//	
	//	password = comb;
	//	
	//	return password;
	//}
	
	void closeServer()
	{
		if (GetGame().IsServer())
		{
			
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
			setIsOpened(false);
		
			SetSynchDirty();
		}
	}
	
	void openServer()
	{
		if (GetGame().IsServer())
		{
			GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
			setIsOpened(true);
		
			SetSynchDirty();
		}
	}
}