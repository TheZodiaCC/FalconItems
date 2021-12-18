class SafeHelpers
{
	void SafeHelpers()
    {
        GetRPCManager().AddRPC( "FalconItems", "openSafeS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconItems", "setCodeS", this, SingeplayerExecutionType.Server );
    }
	
	private void openSafeS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<SafeCombinationPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			SafeCombinationPackage package = data.param1;
			
			if (package)
			{
				if (package.password && package.safe)
				{
					Safe safe = package.safe;
					string password = package.password;
					
					if (isCombinationCorrect(password))
					{
						if (safe.getPassword() == password)
						{
							safe.openServer();
						}
					}
				}
			}
        }
	}
	
	void openSafe(SafeCombinationPackage package)
	{
		GetRPCManager().SendRPC("FalconItems", "openSafeS", new Param1<SafeCombinationPackage>(package));
	}
	
	private void setCodeS(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<SafeCombinationPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			
			SafeCombinationPackage package = data.param1;
			
			if (package)
			{
				if (package.password && package.safe)
				{
					Safe safe = package.safe;
					
					if (!safe.getPasswordSet())
					{
						string password = package.password;
						
						if (isCombinationCorrect(password))
						{
							safe.setPassword(password);
							safe.setPasswordSet(true);
						}
					}
				}
			}
        }
	}
	
	void setCode(SafeCombinationPackage package)
	{
		GetRPCManager().SendRPC("FalconItems", "setCodeS", new Param1<SafeCombinationPackage>(package));
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