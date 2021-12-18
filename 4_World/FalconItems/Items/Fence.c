modded class Fence extends BaseBuildingBase
{
	override bool CanOpenFence() 
	{
        if (GetCodeLock()) 
		{
            return false;
        }
		
        return super.CanOpenFence();
    }

	CodeLock GetCodeLock()
	{
		CodeLock codeLock = CodeLock.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_COMBINATION_LOCK ) );
		return codeLock;
	}
	
	override void CloseFence()
	{
		if (GetGame().IsServer())
		{
			CodeLock codeLock = GetCodeLock();
			
			if (codeLock && codeLock.getPasswordSet())
			{
				codeLock.lockServer();
			}

			super.CloseFence();
		}
	}
}