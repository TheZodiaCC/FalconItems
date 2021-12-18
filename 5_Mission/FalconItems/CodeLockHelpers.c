class CodeLockHelpers
{
	void CodeLockHelpers()
    {
        GetRPCManager().AddRPC( "FalconItems", "openCodeLockS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "setCodeLockLockS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "removeCodeLockS", this, SingeplayerExecutionType.Server );
    }
	
	private void openCodeLockS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<CodeLockCombinationPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			CodeLockCombinationPackage package = data.param1;
			
			if (package)
			{
				if (package.password && package.codeLock)
				{
					CodeLock codeLock = package.codeLock;
					string password = package.password;
					
					if (isCombinationCorrect(password))
					{
						if (codeLock.getPassword() == password)
						{
							codeLock.unlockServer();
						}
					}
				}
			}
        }
	}
	
	void openCodeLock(CodeLockCombinationPackage package)
	{
		GetRPCManager().SendRPC("FalconItems", "openCodeLockS", new Param1<CodeLockCombinationPackage>(package));
	}
	
	private void setCodeLockLockS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<CodeLockCombinationPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			CodeLockCombinationPackage package = data.param1;
			
			if (package)
			{
				if (package.password && package.codeLock)
				{
					CodeLock codeLock = package.codeLock;
					
					if (!codeLock.getPasswordSet())
					{
						string password = package.password;
						
						if (isCombinationCorrect(password))
						{
							Fence fence = Fence.Cast(codeLock.GetHierarchyParent());
							
							codeLock.setPassword(password);
							codeLock.setPasswordSet(true);
							
							fence.CloseFence();
						}
					}
				}
			}
        }
	}
	
	void setCodeLockLock(CodeLockCombinationPackage package)
	{
		GetRPCManager().SendRPC("FalconItems", "setCodeLockLockS", new Param1<CodeLockCombinationPackage>(package));
	}
	
	private void removeCodeLockS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<CodeLockCombinationPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			CodeLockCombinationPackage package = data.param1;
			
			if (package)
			{
				if (package.password && package.codeLock)
				{
					CodeLock codeLock = package.codeLock;
					
					if (codeLock.getPasswordSet())
					{
						string password = package.password;
						
						if (isCombinationCorrect(password))
						{
							if (codeLock.getPassword() == password)
							{
								codeLock.setPasswordSet(false);
								codeLock.setPassword("");
							
								codeLock.removeLock();
							}
						}
					}
				}
			}
        }
	}
	
	void removeCodeLock(CodeLockCombinationPackage package)
	{
		GetRPCManager().SendRPC("FalconItems", "removeCodeLockS", new Param1<CodeLockCombinationPackage>(package));
	}
	
	private bool checkIfInArray(array<string> input, string combination)
	{
		for (int i = 0; i < input.Count(); i++)
		{
			for (int j = 0; j < combination.Length(); j++)
			{
				if (input[i] == combination[j])
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	bool isCombinationCorrect(string code)
	{
		array<string> allowedNumbers = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
		bool cond = true;
		
		if (code.Length() == 4)
		{
			for (int i = 0; i < code.Length(); i++)
			{
				if (!checkIfInArray(allowedNumbers, code[i]))
				{
					return false;
				}
			}
		}
		else 
		{
			cond = false;
		}
		
		return cond;
	}
}